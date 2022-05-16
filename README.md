# iCE40RomGen

romgen. Convert ordinary binary file into 8bit ROM in Verilog case statement used to infer BRAM as ROM by Lattice Synthesis Engine (LSE).

compile  
```
gcc romgen.c -o romgen
```

Usage : Linux  
```
./romgen [binary rom image name] [binary rom image size] [bit width for addressing] [output file name]
```
# Explaination

For some weird reason. To infer iCE40 Block RAM as ROM with Lattice Synthesis Engine (LSE). The case statement is required to make LSE infer BRAM as ROM. User needs to manually type in each case for each address. This is fine if we have only 10 or 20 bytes. But some ROM (character bitmap rom as example) can have 100 or 1000 plus bytes. It's pracically impossible to manually type each byte of each address for case statement. So I decided to write some simple silly C code that will read binary file and automagically write it out in Verilog syntax case statement.

# TODO

1. (unsigned int)(log2(binary_size)) + 1 to automatically calculate address bit width.
2. custom data bit width.
3. custom name (module, register, etc...).