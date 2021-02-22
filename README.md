# Ternary Computing

This is a storage point for work and research in to computing using balanced ternary.

I've been thinking about ternary computing for a long time. Looking into what the base gates would be. Figuring out how to implement those with transitor circuits. Determining how best to do arithematic and control.

More recently I decided I should juststart implementing something. So I decided to build an emulator for a 30-Trit (later changed to 27) balanced ternary  computer. For which I will then write some basic test software and then try to port forth to. This basic operating environment will then be used for further research and project creation. The goal being to create a set of software that could be run on an implementation of the base instruction set architecture.

When/If implementation starts the emulator will be adjusted to reflect those changes. In fact thinking about implementation concerns This system may be m


## Theory

Notes on the math and logic theory behind this design can be found in the
[math Readme](math/README.md)

## The Emulator
My emulator for the ternary computer.
Currently a hodge-podge of ternary support functions

For reference each trit is stored in two bits.

| Trit | Bit Representation | Notes             |
|------|--------------------|-------------------|
| +1   | 01                 |                   |
| 0    | 00                 |                   |
| -1   | 11                 | N in the code     |
|Undef | 10                 | Undefined Error   |

The emulated CPU will have RAM, and a number of simulated memory mapped devices including a converting uart for character stream I/O. A more advanced trinary unicode encoding may eventually be done, but for now it is just (ascii value - 0x1F) with null(0) and Unit Seperator(1F) swapped so null stays at 0 and most of the control characters go negative. This fits an ascii character into 5 trits. A Unicode 32-bit code point could fit into a 21 trit number without any offset. Which is modivation to go down to a 9 or 27 trit machine.


### Trits, Trytes and Triwords
Trits, Trytes and Triwords correspond to bits, bytes and words, respectively in
a binary computer. As this is balanced ternary there is no differntiation of
signed and unsigned. Everything is signed. This means our address space will
contain negative addresses, but it is all part of the fun.

A single Trit can have one of 3 values +1, 0, -1. Through out
this design several different symbols may be used for the values based on context.
The most common for +1 are 1, P and +. For -1 it will be -, _ or N. and 0 will
usually be 0, but may be marked Z. Similarly to C style 0x for hex and 0b for
binary, 0t will be used as a prefix to indicate trinary numbers.

A Tryte (sometimes written trite) contains 9 (0t100) Trits, and can store values
from -9841 (0t---------) to +9481 (0t111111111). Text will be encoded as unicode
code points stored in postive trites if less than 9482. Larger values can be
encoded be setting the high trit to -1 in the tryte. The details will be in the
arbitrary length word encoding that is in development.

A Triword contains 27 trits or 3 trytes. It can store values from -3812798742493
to +3812798742493. This is the width of the processing unit in this emulated
CPU.

As the math library is designed to make use of the binary computer it runs on it
will support 32 Trit operations.

### The ISA
This has had many revisions as I've look at different architectures over the
years I've been thinking about it. I always knew I wanted something more on the
RISC side as I don't want to spend a ton of time implementing instructions. This
design has pulled many ideas from x86, 68000, 6502, ARM, most recently RISC-V,
and others. This was then distilled down to a minimal subset that provided the
functionality that seemed most useful, but still offered a nice symmetry. One
peculiarity some may notice is the inclusion of a Multiply instruction, but not
divide. This is something for experience with fixed point DSPs. In practice,
multiplies are needed to be fast al the time, accessing a multidimentional array
or an array of structures. Division can often be sufficiently approximated with
a multiply and shift or implemented in software and avoided. Multiply accumulate
instructions to speed up matrix operations are probably higher priority.

An ISA specification is in the works for now the emulator [cpu.h](emu/cpu.h) has
a lot of the opcodes and instruction format information.

## Software
An [emulator](emu/) which contains an library for performing ternary operations
is the first piece of software written on this project. It is needed to to test
the design and anything  written for it.

A cross-assembler will be probably be second as it will make writing tests for
the emulator easier.

At some point a simple forth like environment based on a port of
[JONESFORTH](https://rwmj.wordpress.com/2010/08/07/jonesforth-git-repository/) .
This environment will be tweaked to better align with the underlying ternary
architecture. Particularly any binary operation such as shifts would change
along with the values for True(-1 -> 1) and False(0 -> -1).

Then maybe some software bit and bobs.
- Hello World
- A text game.
- A video game, once I add a framebuffer to the emulator.
- Bootloader that allows a program to be loaded and executed
  over the "serial" interface.
- Assembler that actually runs on target. Maybe more of a debugger.


## Hardware
Schematics, hdl, and other content for actual implementation. These will be a
little more involved. as there is currently no language for describing ternary
logic circuits, and no programable logic devices would support them. so the best
we could get there would be version of the ternary on binary emulator that ran
on such adevice. what this is more likely to look at is using existing electical
components to build the elemental gates used in the design and showing how those
gates could be combined to build a functional system.

In my wildest dreams of this system, I can't imagine getting a large memory ever
built so an interface or RAM emulator would probably be needed even if I
wire-wrapped a bunch of custom transitior gates. Maybe a ternary to binary level
buffer/splitter circuit might end up here. So some ternary state machines could
interface with SRAM, EEPROM, or just an arduino doing the storage.

## History
Though I didn't know it when I first started working on this problem. There
actually was a ternary computer that ran a forth like operating system built
by the Soviets in the 1950s called [Setun](https://en.wikipedia.org/wiki/Setun) .
I actually don't know a lot about it, but as you could imagine I found it
interesting that someone else was thinking about a ternary computer with an
RPN interface, when I heard about it. I didn't look at the details, so I doubt
there will be much similarity. Based on the era it is probably a much simpler
system, so maybe I'll look at writing an emulator for it when I'm done with this
project. Though one probably already exists.

If anyone was curious for the history of this. My inspiration was just the
simple elegance of balanced number systems, 3 being the smallest postive integer
base that works. Also that 3 is closer to the base of the natural log e than 2
is. This means by some reconings that it should be more optimized for the
storage of information digits needs by symbol differentiation.

## TODO
- [ ] Arbitrary length word encoding.
    - an all zero symbol cannot occur inside a non-zero number
    - an all zero symbol is the only legal way to represent 0
    - Only the high trit in the first symbol should be needed to deterime if the number
      is extended or not.
    - Proposal: High trit is 0 means single tryte, 1 means mor eto follow, -1 means last tryte of multi tryte word

- [ ] Floating point number encoding
    - Sign Trit is also high Trit in mantissa
    - ??Exponent should be 1/3 of value
    - Maybe 1 sign: 9 exponent : 17 remaining mantissa
    - or 1 sign: 3 exponent : 5 remaining mantissa
    - or 1 sign: 27 exponent : 53 remaining mantissa
    - Efficient use of Sign is 0
    - Negative 0?
    - Positive infinity
    - Negative infinity
    - NaN

- [x] Trinary Print should support different fixed widths
- [x] Add disassembler to emulator monitor
- [x] Load RAM from File
- [ ] Assembler
- [x] Expand math operations to cover a full 32 Trits
- [ ] Trinary I/O should be more generic
    - [ ] Work with strings
    - [ ] Work with balanced base 27 input
- [ ] expand Register PreModifier to cover all 27 possible single input functions
- [ ] Look into 5 trit for Reg Mod pre op bits (all 27 functions + shift by +/- 18, 9, 3, 1, 0)
- [ ] Look into a 9 trit instruction word size
    - less registers 9 is still a good number, if we drop some of the specialty regs like flags
    - No Pre Op Register mods
    - variable length opcode based on register count
    - immediate values are additional 1,2,3 trytes
    - maybe drop register size to 9 trits? is even that realistically implementable
- [ ] Arithmetic Min/Max operations.
- [ ] Division optimized conditional add/sub  operation

