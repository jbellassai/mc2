// Print disassembly for address ranges. Args: outFile start1 end1 [start2 end2 ...] (hex seg:off)
import java.io.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
public class Disasm extends GhidraScript {
  public void run() throws Exception {
    String[] a = getScriptArgs();
    try (PrintWriter w = new PrintWriter(new FileWriter(a[0]))) {
      for (int i = 1; i + 1 < a.length; i += 2) {
        Address s = toAddr(a[i]), e = toAddr(a[i+1]);
        disassemble(s);
        w.println("---- " + s + " .. " + e);
        for (Instruction in = getInstructionAt(s); in != null && in.getAddress().compareTo(e) <= 0; in = in.getNext())
          w.println(in.getAddress() + "  " + in.toString());
      }
    }
    println("DONE");
  }
}
