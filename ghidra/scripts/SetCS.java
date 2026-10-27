// preScript for raw overlay imports: set CS=1CA8 context over the whole image so near calls resolve.
import java.math.BigInteger;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.lang.Register;
public class SetCS extends GhidraScript {
  public void run() throws Exception {
    Register cs = currentProgram.getRegister("CS");
    currentProgram.getProgramContext().setValue(cs, currentProgram.getMinAddress(), currentProgram.getMaxAddress(), BigInteger.valueOf(Integer.parseInt(getScriptArgs().length > 0 ? getScriptArgs()[0] : "1ca8", 16)));
    println("CS context set");
  }
}
