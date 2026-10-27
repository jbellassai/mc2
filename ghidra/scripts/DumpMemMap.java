import ghidra.app.script.GhidraScript;
import ghidra.program.model.mem.MemoryBlock;
public class DumpMemMap extends GhidraScript {
  public void run() throws Exception {
    println("IMAGEBASE " + currentProgram.getImageBase());
    for (MemoryBlock b : currentProgram.getMemory().getBlocks())
      println("BLOCK " + b.getName() + " " + b.getStart() + "-" + b.getEnd() + " size=" + b.getSize());
    println("FUNCS " + currentProgram.getFunctionManager().getFunctionCount());
  }
}
