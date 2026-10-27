// Decompile every function that references the named symbol(s). Args: outFile name1 name2...
import java.io.*; import java.util.*;
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
public class DecompileCallers extends GhidraScript {
  public void run() throws Exception {
    DecompInterface di = new DecompInterface(); di.openProgram(currentProgram);
    String[] a = getScriptArgs();
    Set<Function> done = new HashSet<>();
    try (PrintWriter w = new PrintWriter(new FileWriter(a[0]))) {
      for (int i = 1; i < a.length; i++)
        for (Symbol s : currentProgram.getSymbolTable().getSymbols(a[i]))
          for (Reference r : currentProgram.getReferenceManager().getReferencesTo(s.getAddress())) {
            Function f = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
            if (f == null || !done.add(f)) continue;
            DecompileResults d = di.decompileFunction(f, 60, monitor);
            w.println("// ===== " + f.getName() + " @ " + f.getEntryPoint() + " (refs " + a[i] + ")");
            w.println(d.getDecompiledFunction() != null ? d.getDecompiledFunction().getC() : "// FAILED");
          }
    }
    di.dispose(); println("DONE");
  }
}
