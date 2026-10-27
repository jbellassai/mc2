// Create+name functions from a file of "seg:off name" lines. Args: namesFile
import java.nio.file.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.app.cmd.function.CreateFunctionCmd;
public class ApplyNames extends GhidraScript {
  public void run() throws Exception {
    int n = 0;
    for (String line : Files.readAllLines(Paths.get(getScriptArgs()[0]))) {
      String[] f = line.trim().split("\\s+"); if (f.length < 2) continue;
      Address a = toAddr(f[0]);
      if (getInstructionAt(a) == null) disassemble(a);
      Function fn = getFunctionAt(a);
      if (fn == null) { new CreateFunctionCmd(a).applyTo(currentProgram); fn = getFunctionAt(a); }
      if (fn != null) { fn.setName(f[1], SourceType.IMPORTED); n++; }
      else createLabel(a, f[1], true);
    }
    println("NAMED " + n);
  }
}
