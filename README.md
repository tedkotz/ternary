# Ternary Computing

This is a storage point for work and research in to computing using balanced ternary.

I've been thinking about ternary computing for a long time. Looking into what the base gates would be. Figuring out how to implement those with transitor circuits. Determining how best to do arithematic and control.

More recently I decided I should juststart implementing something. So I decided to build an emulator for a 30-Trit (later changed to 27) balanced ternary  computer. For which I will then write some basic test software and then try to port forth to. This basic operating environment will then be used for further research and project creation. The goal being to create a set of software that could be run on an implementation of the base instruction set architecture.

When/If implementation starts the emulator will be adjusted to reflect those changes. In fact thinking about implementation concerns This system may be m

## emu
My emulator for the ternary computer.
Currently a hodge-podge of ternary support funtions

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


### Truth Tables
In binary, there are only 4 single input operations (SET, CLEAR, COPY, NOT). There
are only two posible input permutations and thus 2^2 possible output state
permutations. For 2 inputs the number of input permutations goes up to 4 (2^2),
which gives only 16 (2^4), different possible 2 input functions, most of which
are not terribly interesting.

In ternary this number of possible operations explodes much more quickly. There
are already 27 (3^3) single input operations. And that shoots up to 19683 (3^9)
different 2 input operations. Because of this there is a lot more overlap in
functions in binary. AND covers conjuction(Weak and strong), Minimum, Multiply,
and Masking. In ternary the question of what is an AND or OR gate becomes more
complicated, though there are still a number of useful gates in the similar area
or single digit addition, multiplication, conjucation and disjunction. The math
can get involved, but it may help to think about it more in terms of logic where
your states are True(+1), Unknown(0), False(-1). Then you can see how ANDing a
False with an Unknown is going to be False, because if anything is ANDed with a
False state the combination is False.

| A | B | AND[MIN] | A * B | OR[MAX] | A + B | Major  | A -> B | A <-> B | A <!> B |
|---|---|----------|-------|---------|-------|--------|--------|---------|---------|
| - | - | -        | +     | -       | +     | -      | +      | +       | -       |
| - | 0 | -        | 0     | 0       | -     | 0      | +      | 0       | 0       |
| - | + | -        | -     | +       | 0     | 0      | +      | -       | +       |
| 0 | - | -        | 0     | 0       | -     | 0      | 0      | 0       | 0       |
| 0 | 0 | 0        | 0     | 0       | 0     | 0      | +      | +       | -       |
| 0 | + | 0        | 0     | +       | +     | 0      | +      | 0       | 0       |
| + | - | -        | -     | +       | 0     | 0      | -      | -       | +       |
| + | 0 | 0        | 0     | +       | +     | 0      | 0      | 0       | 0       |
| + | + | +        | +     | +       | -     | +      | +      | +       | -       |

If we take the above table and cut out the rows with 0 inputs you'll see some
familiar operations:

| A | B | AND[MIN] | A * B | OR[MAX] | A + B | Major  | A -> B | A <-> B | A <!> B |
|---|---|----------|-------|---------|-------|--------|--------|---------|---------|
| - | - | -        | +     | -       | +     | -      | +      | +       | -       |
| - | + | -        | -     | +       | 0     | 0      | +      | -       | +       |
| + | - | -        | -     | +       | 0     | 0      | -      | -       | +       |
| + | + | +        | +     | +       | -     | +      | +      | +       | -       |

The other operations need to cut out the - inputs instead to show up:

| A | B | AND[MIN] | A * B | OR[MAX] | A + B | Major  | A -> B | A <-> B | A <!> B |
|---|---|----------|-------|---------|-------|--------|--------|---------|---------|
| 0 | 0 | 0        | 0     | 0       | 0     | 0      | +      | +       | -       |
| 0 | + | 0        | 0     | +       | +     | 0      | +      | 0       | 0       |
| + | 0 | 0        | 0     | +       | +     | 0      | 0      | 0       | 0       |
| + | + | +        | +     | +       | -     | +      | +      | +       | -       |


## sw
Software written for the emulator and initial hand assembled machine code files in a format the emulator can load

## docs
Documents, notes, and musings on balanced ternary

## hw
Schematics, hdl, and other content for actual implementation.

## TODO
#### Arbitrary length word encoding.
- an all zero symbol cannot occur inside a non-zero number
- an all zero symbol is the only legal way to represent 0
- Only the high trit in the first symbol should be needed to deterime if the number
  is extendeed or not.

#### Floating point number encoding
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
