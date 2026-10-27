// Decompile every function in the program to a file. Args: outFile
import java.io.*;
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
public class DecompileAll extends GhidraScript {
  public void run() throws Exception {
    DecompInterface di = new DecompInterface(); di.openProgram(currentProgram);
    try (PrintWriter w = new PrintWriter(new FileWriter(getScriptArgs()[0]))) {
      for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
        DecompileResults r = di.decompileFunction(f, 60, monitor);
        w.println("// ===== " + f.getName() + " @ " + f.getEntryPoint());
        w.println(r.getDecompiledFunction() != null ? r.getDecompiledFunction().getC() : "// FAILED " + r.getErrorMessage());
      }
    }
    di.dispose(); println("DONE");
  }
}
