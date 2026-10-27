// Decompile named functions to a file. Args: outFile name1 name2 ...
import java.io.*;
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;

public class DecompileFuncs extends GhidraScript {
  public void run() throws Exception {
    String[] a = getScriptArgs();
    DecompInterface di = new DecompInterface();
    di.openProgram(currentProgram);
    try (PrintWriter w = new PrintWriter(new FileWriter(a[0]))) {
      for (int i = 1; i < a.length; i++) {
        boolean found = false;
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
          if (!f.getName().equals(a[i])) continue;
          found = true;
          DecompileResults r = di.decompileFunction(f, 60, monitor);
          w.println("// ===== " + f.getName() + " @ " + f.getEntryPoint());
          w.println(r.getDecompiledFunction() != null ? r.getDecompiledFunction().getC() : "// FAILED: " + r.getErrorMessage());
        }
        if (!found) w.println("// NOT FOUND: " + a[i]);
      }
    }
    di.dispose();
    println("DONE");
  }
}
