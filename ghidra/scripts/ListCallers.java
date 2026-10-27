// Print callers of the named functions. Args: name1 name2 ...
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
public class ListCallers extends GhidraScript {
  public void run() throws Exception {
    for (String n : getScriptArgs())
      for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
        if (!f.getName().equals(n)) continue;
        StringBuilder sb = new StringBuilder("CALLERS " + n + ":");
        for (Reference r : currentProgram.getReferenceManager().getReferencesTo(f.getEntryPoint())) {
          Function c = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
          sb.append(' ').append(c == null ? "?" + r.getFromAddress() : c.getName() + "@" + r.getFromAddress());
        }
        println(sb.toString());
      }
  }
}
