#!/bin/sh
# Import every P*.MCO overlay into the Ghidra project at 1CA8:0000, decompile all functions, post-process.
set -e
HL=$(brew --prefix ghidra)/libexec/support/analyzeHeadless
mkdir -p out/decomp
for f in original/P*.MCO; do
  n=$(basename "$f" .MCO)
  "$HL" ghidra MC2 -import "$f" -processor "x86:LE:16:Real Mode" -loader BinaryLoader -loader-baseAddr 1ca8:0000 -overwrite -preScript SetCS.java \
     -scriptPath ghidra/scripts -postScript DumpOverlay.java "out/decomp/${n}_entries.txt" 0 -postScript DecompileAll.java "out/decomp/${n}_all.c" 2>&1 | grep -E 'ERROR|Exception' || true
  echo "$n: $(head -1 out/decomp/${n}_entries.txt)"
done
