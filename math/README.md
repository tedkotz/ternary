Mathematical Properties
=======================


Logic Properties
----------------
In Ternary Logic the extra value can used to indicate uncertainty.  The Logic Values are:

| Trit | Logic Meaning | Aliases                            |
|------|---------------|------------------------------------|
| 1    | True          | +,Y,P,T,100%                       |
| 0    | Clear         | Maybe, Unknown, 50%, X             |
| -1   | False         | -,N,F,0%                           |


Interesting Gates
-----------------

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

|Op        |Description                                                       |
|----------|------------------------------------------------------------------|
|MIN       |Arithmetic Minimum, weak conjunction                              |
|AND       |Strong Conjunction -(-A OR -B)                                    |
|A*B       |Arithmetic Multiply                                               |
|MAX       |Arithmetic Maximum, weak disjunction                              |
|OR        |Strong Disjunction                                                |
|A+B       |Arithmetic modulo addition                                        |
|UNAM      |Unamimous                                                         |
|A->B      |Implies                                                           |
|A<-->B    |Equivalence                                                       |
|A<-!->B   |Not equivalence, XOR                                              |


| A | B | MIN | AND | A*B | MAX | OR | A+B | UNAM  | A->B | A<->B | A<-!->B |
|---|---|-----|-----|-----|-----|----|-----|-------|------|-------|---------|
| - | - | -   | -   | +   | -   | -  | +   | -     | +    | +     | -       |
| - | 0 | -   | -   | 0   | 0   | 0  | -   | 0     | +    | 0     | 0       |
| - | + | -   | -   | -   | +   | +  | 0   | 0     | +    | -     | +       |
| 0 | - | -   | -   | 0   | 0   | 0  | -   | 0     | 0    | 0     | 0       |
| 0 | 0 | 0   | -   | 0   | 0   | +  | 0   | 0     | +    | +     | -       |
| 0 | + | 0   | 0   | 0   | +   | +  | +   | 0     | +    | 0     | 0       |
| + | - | -   | -   | -   | +   | +  | 0   | 0     | -    | -     | +       |
| + | 0 | 0   | 0   | 0   | +   | +  | +   | 0     | 0    | 0     | 0       |
| + | + | +   | +   | +   | +   | +  | -   | +     | +    | +     | -       |

If we take the above table and cut out the rows with 0 inputs you'll see some
familiar boolean operations:

| A | B | MIN | AND | A*B | MAX | OR | A+B | UNAM  | A->B | A<->B | A<-!->B |
|---|---|-----|-----|-----|-----|----|-----|-------|------|-------|---------|
| - | - | -   | -   | +   | -   | -  | +   | -     | +    | +     | -       |
| - | + | -   | -   | -   | +   | +  | 0   | 0     | +    | -     | +       |
| + | - | -   | -   | -   | +   | +  | 0   | 0     | -    | -     | +       |
| + | + | +   | +   | +   | +   | +  | -   | +     | +    | +     | -       |

The other operations need to cut out the - inputs instead to show up:

| A | B | MIN | AND | A*B | MAX | OR | A+B | UNAM  | A->B | A<->B | A<-!->B |
|---|---|-----|-----|-----|-----|----|-----|-------|------|-------|---------|
| 0 | 0 | 0   | -   | 0   | 0   | +  | 0   | 0     | +    | +     | -       |
| 0 | + | 0   | 0   | 0   | +   | +  | +   | 0     | +    | 0     | 0       |
| + | 0 | 0   | 0   | 0   | +   | +  | +   | 0     | 0    | 0     | 0       |
| + | + | +   | +   | +   | +   | +  | -   | +     | +    | +     | -       |


### Single Input Gates

Ternary has more 1 input gates than binary and many more are useful. The are 3^3^1=27 single input ternary gates vs 2^2^1=4 for binary.

| + | 0 | - | Number | Name  | Notes                                           |
|---|---|---|--------|-------|-------------------------------------------------|
| - | - | - |  -13   | False |                                                 |
| - | - | 0 |  -12   |       | Neg(Lax)                                        |
| - | - | + |  -11   |       | Neg(Ceil), F-test                               |
| - | 0 | - |  -10   | Abn   | Neg(Abs)                                        |
| - | 0 | 0 |  -9    |       | Neg(Flat)                                       |
| - | 0 | + |  -8    | Neg   | TF-swap                                         |
| - | + | - |  -7    | isZ   | Z-test                                          |
| - | + | 0 |  -6    | Inc   |                                                 |
| - | + | + |  -5    |       | Neg(Floor)                                      |
| 0 | - | - |  -4    |       | Saturated Dec                                   |
| 0 | - | 0 |  -3    |       | Dec(Abs)??                                      |
| 0 | - | + |  -2    | Dec   |                                                 |
| 0 | 0 | - |  -1    |       | F-filter                                        |
| 0 | 0 | 0 |  0     | Clear | Z-filter                                        |
| 0 | 0 | + |  1     |       | Flat(Neg), F-select                             |
| 0 | + | - |  2     |       | Inc(Neg) or Neg(Dec), TZ-swap                   |
| 0 | + | 0 |  3     |       | Inc(Abn)??, Z-select                            |
| 0 | + | + |  4     |       | Lax(Neg)                                        |
| + | - | - |  5     | Floor | T-test                                          |
| + | - | 0 |  6     |       | Dec(Neg) or Neg(Inc), FZ-swap                   |
| + | - | + |  7     |       | Neg(isZ)                                        |
| + | 0 | - |  8     | NOP   |                                                 |
| + | 0 | 0 |  9     | Flat  | Lax(Floor), T-filter, T-select                  |
| + | 0 | + |  10    | Abs   |                                                 |
| + | + | - |  11    | Ceil  |                                                 |
| + | + | 0 |  12    | Lax   | Flat(Ceil), Saturated Inc                       |
| + | + | + |  13    | True  |                                                 |

#### Information transforming gates
These gates map each input to a unique output because of this they can be reversed and have a complimentary sometimes itself. As any combination of these 6 gates would have to have the ssame information preserving property that combination could be reduced to just one of these 6 gates.

##### NOP Do Nothing
The most dull gate (number 8) this does not change the input. It is its own complement. Applying it any number of times get you back to your intial value.

##### NEG/NOT Gate
Balanced ternary gates have a tighter relationship between logical and mathmatical negation. The are the same bitwise operator. It is its own complement. Applying it multiple time every even application brings back the intial value.

##### INC and DEC Gate
These gates can arithmetically be thought of as single trit increment or decrement without carry, but with roll over. These gates are also complementary . Every 3 applications of either one of these gates in a row bring back the intial value.

##### Gate 2 & 6
The these gates are most intuitively expressed as combinations of NEG, INC and DEC.
```
    INC(NEG(A)) = NEG(DEC(A) = Gate 2
    DEC(NEG(A)) = NEG(INC(A) = Gate 6
```
Each gate is its own complement. which can be illustrated by combining the two descriptions of gate2 as an example.
```
    INC(NEG(NEG(DEC(A)))) = INC(DEC(A)) = A
```
Looking more closely at what these gates actually do reveals their symmetry with
the NEG Gate. They can all be seen as pivots about one of the three values. In
NEG + and - rotate around an unchanging 0. Gate 2 has + and 0 rotating around
an unchanging -. Finally gate 6 completes the set by having 0 and - rotate
around +.


#### Information destroying gates
These gates have less possible output states that input states. and thus lose information.  They cannot be reversed thus do not have a complementary action. Once an information destroying gate is brought into the sequence the entire sequence becomes information destroying and can't be reversed, thus the sequence will map to single one of these 21 information destroying gates.
1. Absolute Value (-1->1, 0->0, 1->1)
2. Flatten Strict (-1->0, 0->0, 1->1)
3. Flatten Lax    (-1->0, 0->1, 1->1)

##### True, False and Clear
The most extreme form of information losing gates, these completely disreguard the input. Thus in a chain of operations anything applied before them is meaningless, much like multipling by 0, and the final output of the sequence will always be fixed meaning the whole sequence maps to one of these 3 gates.

### Multiple Input Gates
When you get to 2 input gate ternary logic explodes to 3^(3^2)=19683 while binary stays
with a more reasonable 2^2^2=16. This makes an exhaustive analysis of 2-input ternary
logic functions while possible unrealistic. We can instead investigate some of
the more interesting operations and how the interconnect.

#### AND/MIN Gate

#### OR/MAX Gate

#### Addition

#### Full Adder
The balanced ternary full adder has the same two outputs(carry and sum) as a binary adder, but can have upto 4 inputs as the 2 trit output will not overflow. This means the ternary adder can add up to 3 numbers plus carry simultaneously. We will refer to the lesser adders as 1/3(2 input) and 2/3(3 input) adders.


### Functional Completeness

If the goal is to implement this system, it can be nice to know what is the minimum set of operations needed to create any arbitrarily complicated function.

#### Single Input Completeness

The goal here is determining what subset of the single input gates do we need to create any single input gate.

The information destroying gates cannot be used to create the information transforming gates. So let's start there. NOP can be produced for any gate with an inverse or that eventually cycles which they all do. INC and DEC can be made from each other. Gate 2 & 6 are defined in terms of DEC and NEG. So it looks like
these only need DEC and NEG to make all the transforming gates.

```
NOP(A) = NEG(NEG(A))
INC(A) = DEC(DEC(A))
G2(A)  = NEG(DEC(A))
G6(A)  = DEC(NEG(A))
```

The gates that ignore their input only one is needed to as whatever gates we keep above can do the transformation. For now let's keep TRUE as it can easily be turned into the other two with DEC and NEG.
```
FALSE(A) = NEG(TRUE(A))
CLEAR(A) = DEC(TRUE(A))
```

The remaining 18 gates. will need something to get to reach them. I think any one of them should be able to be turned into all of them using the above transitions.
I'm going to select LAX, or Saturated Addition, because I like that it has a simple definition for TRUE so we can cut that out as well.
```
TRUE(A) = LAX(LAX(A))
```
So then here is the table of all 27 possible function defined in terms of DEC, NEG and LAX

| + | 0 | - | Number | Name  | Definitions                                     |
|---|---|---|--------|-------|-------------------------------------------------|
| - | - | - |  -13   | False | NEG(LAX(LAX))                                   |
| - | - | 0 |  -12   |       | NEG(LAX)                                        |
| - | - | + |  -11   |       | DEC(DEC(LAX))                                   |
| - | 0 | - |  -10   | Abn   | NEG(LAX(DEC))                                   |
| - | 0 | 0 |  -9    |       | DEC(LAX(NEG))                                   |
| - | 0 | + |  -8    | Neg   | NEG                                             |
| - | + | - |  -7    | isZ   | DEC(DEC(LAX(DEC)))                              |
| - | + | 0 |  -6    | Inc   | DEC(DEC)                                        |
| - | + | + |  -5    |       | DEC(NEG(LAX(NEG)))                              |
| 0 | - | - |  -4    |       | NEG(LAX(NEG))                                   |
| 0 | - | 0 |  -3    |       | DEC(LAX(DEC))                                   |
| 0 | - | + |  -2    | Dec   | DEC                                             |
| 0 | 0 | - |  -1    |       | DEC(LAX)                                        |
| 0 | 0 | 0 |  0     | Clear | DEC(LAX(LAX))                                   |
| 0 | 0 | + |  1     |       | NEG(DEC(LAX))                                   |
| 0 | + | - |  2     |       | NEG(DEC)                                        |
| 0 | + | 0 |  3     |       | NEG(DEC(LAX(DEC)))                              |
| 0 | + | + |  4     |       | LAX(NEG)                                        |
| + | - | - |  5     | Floor | DEC(DEC(LAX(NEG)))                              |
| + | - | 0 |  6     |       | DEC(NEG)                                        |
| + | - | + |  7     |       | DEC(NEG(LAX(DEC)))                              |
| + | 0 | - |  8     | NOP   | NEG(NEG)                                        |
| + | 0 | 0 |  9     | Flat  | NEG(DEC(LAX(NEG)))                              |
| + | 0 | + |  10    | Abs   | LAX(DEC)                                        |
| + | + | - |  11    | Ceil  | DEC(NEG(LAX))                                   |
| + | + | 0 |  12    | Lax   | LAX                                             |
| + | + | + |  13    | True  | LAX(LAX)                                        |


This shows that for single input functions the set of operations decrement,
negate and saturated addition are functionally complete. There are many other
3 operation combinations that are funtionally complete, particularly choosing 2
different, but complete information preserving operations and 1 of the other 18
information destroying gates that do not completely ignore their inputs. They may
be more complex in covering all the gates.

#### General Completeness

We start with stating that working in discrete values any N-input function can
be defined in terms of a condition and an N-1 input function
```
For any F(x0,x1,...,x[n])
Fn(x0,x1,...,x[n-1]) = F(x0,x1,...,x[n-1], -)
Fz(x0,x1,...,x[n-1]) = F(x0,x1,...,x[n-1], 0)
Fp(x0,x1,...,x[n-1]) = F(x0,x1,...,x[n-1], +)
                      / x[n] = +, Fp(x0,x1,...,x[n-1])
F(x0,x1,...,x[n]) =  {  x[n] = 0, Fz(x0,x1,...,x[n-1])
                      \ x[n] = -, Fn(x0,x1,...,x[n-1])
```
This requires a way to do the three way conditional. There are several ways that
come to mind to do that. Fundamentally you need a test function, masking and
summation operations. This could be done with isF, isZ, isT, Max and Min. Or
the Flat versions of the test ops(F-Select, Z-Select & T-Select), MUL and ADD.
```
switch(A,B,C,D) = Max( Min( isT(A), B ), Min( isZ(A), C ), Min( isF(A), D ) )
switch(A,B,C,D) = isT(A) & B | isZ(A) & C | isF(A) & D
switch(A,B,C,D) = Tsel(A) * B + Zsel(A) * C + Fsel(A) * D
```
Which then combines with the above to give us a general path, though not
necessarily most efficient one, to reduce any N input function to collection of arbitarily
smaller order function, and the combination of functions needed to define the switch
above.
```
F(x0,x1,...,x[n]) = switch(x[n], Fp(x0,x1,...,x[n-1]), Fz(x0,x1,...,x[n-1]), Fn(x0,x1,...,x[n-1]))
```
This shows that we could reduce everything to the switch and single input functions.
As we showed above we only need 3 single input functions to cover all single
input functions. which means we can stop iterating this down when we get to
single input functions. switch still needs its component parts, but the test
functions are already single input function so we have those covered. This leaves
the masking and summation two input functions. This gets us down to 5 operations,
but these 5 gates may have some overlap depending on selection.
```
DEC(A) = ADD(A, -)
NEG(A) = MUL(A, -) = ADD( A, A)
LAX(A) = MUL(ADD(A, +), ADD(A, +))

MIN(A, B) = NEG(MAX(NEG(A),NEG(B)))
LAX(A) =  MAX(DEC(DEC(A)),DEC(NEG((A))))

MAX(A, B) = NEG(MIN(NEG(A),NEG(B)))
LAX(A) =  NEG(MIN(DEC(DEC(A)),DEC(NEG((A)))))

AND(A, B) = NEG(OR(NEG(A),NEG(B)))
LAX(A) = DEC(NEG(OR( A, A)))

OR (A, B) = NEG(AND(NEG(A),NEG(B)))
LAX(A) = DEC(AND( NEG(A), NEG(A)))
```
This shows 5 different minimal functionally complete operation sets with 3 ops.
1. ADD, MUL, -1
2. MAX, NEG, DEC
3. MIN, NEG, DEC
4. AND, NEG, DEC
5. OR,  NEG, DEC

As the MAX or the MIN of anything with itself is unchanged, it provides the easy
opportunity to merge the negative to them to get the number of operations down
by one more to NMIN or NMAX plus DEC. So if hardware were produced that could
implement those 2 operations and interconnect, it could be used to construct any
ternary operation.

Modulation Techniques
---------------------

Just as there are symmetries with binary gates ane logic so too are there
symmetries with binary coding methods. The additional value means that receivers
need to be more discriminating, however also one trit per symbol is more
information than 1 bit. One trit is approximately 1.6 (lg(3)/lg(2)) bits of data.

### Amplitude Modulation
Just as a binary system could have a symbol amplitude for mark and space
indicating "0" and "1", or 4 levels to send 2 bits per symbol, three amplitude
levels could be used to send a trit. This could be seen as being more directly
compatible with a ternary serial signal, but is not very interesting.

### Frequency Modulation
This is very similar to the amplitude in which each symbol could instead have one
of 3 orthogonal frequency shifts selected. This does increase the bandwidth
required. The trade between spectral efficiency and error reduction due to
frequency diversity could be an interesting thing to look at.

### Phase Shift Keying
Splitting up the phase space between different symbol values starts to be more
interesting.

##### 3-PSK
| Trit | Phase                |
|------|----------------------|
|  0   |    0 degrees         |
|  1   |  120 degrees         |
| -1   | -120 or 270 degrees  |


3 is the largest number of phase states that can rotate around the circle with
no needs to pass thru another valid phase state to get to its destination. The
phase can always either stay the same, move clockwise straight to the next
symbol or move counterclockwise directly to the next symbol.

##### 3-DPSK
| Trit | Phase differential   |
|------|----------------------|
|  0   |    0 degrees         |
|  1   |  120 degrees         |
| -1   | -120 degrees         |

If it is desired to not have to synchronize carrier phase between the
transmitter and receiver, the signal can be differentially encoded following a
similar diagram to the 3PSK. Just instead a 0 causes no change in phase. While
a 1 or -1 cause a 120 degree phase rotation, counterclockwise or clockwise
respectively.

##### 9-PSK
8-PSK is used, but not considered overly reliable, but is consider usable. 9-PSK
would be even more sensitive to phase noise, but only slightly with a phase angle
of 40 degrees instead of 45 degrees. Interestingly, an odd number of points on
the phase diagram circle means that the direct path between the points never has
to transition though the origin.

#### Ternary QAM
Ternary gets very interesting when looking at Amplitude phase encoding. While
binary readily maps to symbols at the center points of tessellated squares in the
IQ space, ternary more readily maps to tessellated hexagons. As hexagons are the
most efficient way to pack a 2 dimensional space this has potential benefits.
Also as hexagonally stacked rings are closer in magnitude, it should allow a
ternary design to make better use of a narrower linear region of amplifiers.

##### QAM-3
Putting the origin on the vertex between three hexes makes QAM-3 have an
identical constellation to 3PSK. This is similar to the way that QPSK could
be seen as QAM-4 in binary encodings.

##### QAM-27
If you extend QAM-3 with 2 more rings of hexagons, the 3 rings will contain
27 hexagons. That is enough for 3 trits of data.

##### QAM-[3^(2k-1)]
Stacking hexagons in this fashion allows any odd power of three to be
used for constellation definition. So it could easily generate QAM-243, QAM-2187
or the next one with a number of trits divisible by 3 QAM-19683. Which would
require very high SNR?


Links
-----
- <https://en.wikipedia.org/wiki/Radix_economy>
- <https://en.wikipedia.org/wiki/Balanced_ternary>
- <https://en.wikipedia.org/wiki/Ternary_numeral_system>
- <https://en.wikipedia.org/wiki/Many-valued_logic>
- <https://en.wikipedia.org/wiki/Three-valued_logic>
- <https://en.wikipedia.org/wiki/BL_(logic)>
- <https://en.wikipedia.org/wiki/MV-algebra>
- <https://en.wikipedia.org/wiki/%C5%81ukasiewicz_logic>
- <https://en.wikipedia.org/wiki/Fuzzy_logic>
- <https://en.wikipedia.org/wiki/T-norm_fuzzy_logics>


