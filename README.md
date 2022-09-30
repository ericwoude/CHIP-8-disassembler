[![Main Status](https://img.shields.io/github/workflow/status/ericwoude/CHIP-8-disassembler/main?style=social)](https://github.com/ericwoude/CHIP-8-disassembler/actions/workflows/main.yml)
[![Latest Release](https://img.shields.io/github/v/release/ericwoude/CHIP-8-disassembler?style=social)](https://github.com/ericwoude/CHIP-8-disassembler/releases)
[![License](https://img.shields.io/github/license/ericwoude/CHIP-8-disassembler?style=social)](https://github.com/ericwoude/CHIP-8-disassembler/blob/main/LICENSE)

# CHIP-8 disassembler
> This tool aims to disassemble CHIP-8 programs into pseudo-assembly. It can be useful for debugging when writing a CHIP-8 emulator or for exploring CHIP-8 programs.

## Setup
- To install, simply clone this project and run `make`. This will output the program called _disassembler_
- You can find a list of CHIP-8 programs at [Zophar's domain](https://www.zophar.net/pdroms/chip8.html)


## Usage
You can use this tool using the following command: `./disassembler file`, where file is the path to your CHIP-8 program. It might be a good idea to use this program in conjunction with _less_ or _grep_.
### Example
```
./disassembler programs/HIDDEN
0200 12 1D   JP   21D
0202 48 49   SNE  V8  #49
0204 44 44   SNE  V4  #44
0206 45 4E   SNE  V5  #4E
0208 21 20   CALL 120
020A 31 2E   SE   V1  #2E
020C 30 20   SE   V0  #20
020E 42 79   SNE  V2  #79
0210 20 44   CALL 044
0212 61 76   LD   V1  #76
.
.
.
0550 01 FF   SYS  1FF
```

## Status
The project is _finished_. I have no further plans to implement instructions for the Super Chip-48.

## Inspiration
This tool is highly inspired by the following sources
- [CHIP-8 Emulator](http://emulator101.com/) by [realemulator101](https://twitter.com/realemulator101)
- [Cowgod's CHIP-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)