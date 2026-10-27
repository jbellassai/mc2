// For a raw overlay program: make functions at the leading jmp-table targets, summarise outgoing calls, decompile entries.
import java.io.*;
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.app.cmd.function.CreateFunctionCmd;
import java.util.*;

public class DumpOverlay extends GhidraScript {
  public void run() throws Exception {
    String[] a = getScriptArgs();
    PrintWriter w = new PrintWriter(new FileWriter(a[0]));
    Listing L = currentProgram.getListing();
    Address base = currentProgram.getMinAddress();
    // jmp table: consecutive 3-byte near jmps at start
    List<Address> entries = new ArrayList<>();
    Address p = base;
    for (int i = 0; i < 64; i++) {
      Instruction in = L.getInstructionAt(p);
      if (in == null) { disassemble(p); in = L.getInstructionAt(p); }
      if (in == null || !in.getMnemonicString().equals("JMP") || in.getLength() != 3) break;
      Address t = in.getFlows().length > 0 ? in.getFlows()[0] : null;
      if (t == null) break;
      entries.add(t); p = p.add(3);
    }
    w.println("ENTRIES " + entries.size() + ": " + entries);
    for (Address t : entries) if (L.getFunctionAt(t) == null) new CreateFunctionCmd(t).applyTo(currentProgram);
    // iterative discovery: any CALL target inside memory without a function becomes one
    boolean grew = true;
    while (grew) {
      grew = false;
      for (Instruction in : L.getInstructions(true)) {
        if (!in.getMnemonicString().startsWith("CALL")) continue;
        for (Address t : in.getFlows())
          if (currentProgram.getMemory().contains(t) && L.getFunctionContaining(t) == null) {
            if (L.getInstructionAt(t) == null) disassemble(t);
            if (new CreateFunctionCmd(t).applyTo(currentProgram)) grew = true;
          }
      }
    }
    w.println("FUNCTIONS " + currentProgram.getFunctionManager().getFunctionCount());
    // outgoing call summary
    Map<String,Integer> ext = new TreeMap<>();
    for (Instruction in : L.getInstructions(true)) {
      String m = in.getMnemonicString();
      if (!m.startsWith("CALL") && !m.equals("JMP")) continue;
      for (Reference r : in.getReferencesFrom()) {
        Address t = r.getToAddress();
        if (!currentProgram.getMemory().contains(t)) ext.merge("direct->" + t, 1, Integer::sum);
      }
      if (in.getFlows().length == 0) ext.merge("indirect: " + in.toString(), 1, Integer::sum);
    }
    for (Map.Entry<String,Integer> e : ext.entrySet()) w.println("CALL " + e.getValue() + "x " + e.getKey());
    DecompInterface di = new DecompInterface(); di.openProgram(currentProgram);
    int n = 0;
    for (Address t : entries) {
      Function f = L.getFunctionAt(t); if (f == null || n++ >= Integer.parseInt(a[1])) continue;
      DecompileResults r = di.decompileFunction(f, 60, monitor);
      w.println("// ===== entry " + f.getName() + " @ " + t);
      w.println(r.getDecompiledFunction() != null ? r.getDecompiledFunction().getC() : "// FAILED");
    }
    di.dispose(); w.close(); println("DONE");
  }
}
