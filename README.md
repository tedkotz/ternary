# Ternary Computing

This is a storage point for work and research in to computing using balanced ternary.

I've been thinking about ternary computing for a long time. Looking into what the base gates would be. Figuring out how to implement those with transitor circuits. Determining how best to do arithematic and control.

More recently I decided I should juststart implementing something. So I decided to build an emulator for a 30-Trit balanced ternary  computer. For which I will then write some basic test software and then try to port forth to. This basic operating environment will then be used for further research and project creation. The goal being to create a set of software that could be run on an implementation of the base instruction set architecture.

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
