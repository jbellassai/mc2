// Apply Borland TDInfo symbols exported by tools/tdinfo_export.py (ghidra/symbols.tsv) to the program.
// TSV: kind \t seg(hex, TDInfo-relative) \t off(hex) \t name.  Ghidra segment = seg + image base segment.
import java.io.*;
import java.nio.file.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.app.cmd.function.CreateFunctionCmd;

public class ApplyTdinfo extends GhidraScript {
  public void run() throws Exception {
    String[] args = getScriptArgs();
    Path tsv = Paths.get(args.length > 0 ? args[0] : "ghidra/symbols.tsv");
    int baseSeg = 0x1000;
    AddressSpace sp = currentProgram.getAddressFactory().getDefaultAddressSpace();
    SymbolTable st = currentProgram.getSymbolTable();
    FunctionManager fm = currentProgram.getFunctionManager();
    int funcs = 0, labels = 0, skipped = 0;
    for (String line : Files.readAllLines(tsv)) {
      String[] f = line.split("\t");
      if (f.length < 4) continue;
      int seg = Integer.parseInt(f[1], 16) + baseSeg, off = Integer.parseInt(f[2], 16);
      Address a = ((SegmentedAddressSpace) sp).getAddress(seg, off);
      if (!currentProgram.getMemory().contains(a)) { skipped++; continue; }
      String name = f[3].replaceAll("[^A-Za-z0-9_@$?]", "_");
      if (f[0].equals("func")) {
        Function fn = fm.getFunctionAt(a);
        if (fn == null) {
          Function containing = fm.getFunctionContaining(a);
          if (containing == null) { new CreateFunctionCmd(a).applyTo(currentProgram); fn = fm.getFunctionAt(a); }
        }
        if (fn != null) { fn.setName(name, SourceType.IMPORTED); funcs++; continue; }
      }
      st.createLabel(a, name, SourceType.IMPORTED).setPrimary();
      labels++;
    }
    println("APPLIED funcs=" + funcs + " labels=" + labels + " skipped=" + skipped);
  }
}
