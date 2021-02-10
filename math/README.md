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



| 0 | (+) |  ~   |
|---|-----|------|
| - | OR  | Neg  |
| 0 | Add | N2   |

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
|AND       |Strong conjunction -(-A|-B)                                       |
|A*B       |Arithmetic Multiply                                               |
|MAX       |Arithmetic Maximum, weak disjunction                              |
|OR        |Strong Disjunction                                                |
|A+B       |Arithmetic modulo addition                                        |
|UNAM      |Unamimous                                                         |
|A->B      |Implies                                                           |
|A<-->B    |Equivalence                                                       |
|A<-!->B   |Not equivalence                                                   |


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
familiar operations:

| A | B | MIN | AND | A * B | MAX | OR | A + B | Major  | A -> B | A <-> B | A <!> B |
|---|---|-----|-----|-------|-----|----|-------|--------|--------|---------|---------|
| - | - | -   | -   | +     | -   | -  | +     | -      | +      | +       | -       |
| - | + | -   | -   | -     | +   | +  | 0     | 0      | +      | -       | +       |
| + | - | -   | -   | -     | +   | +  | 0     | 0      | -      | -       | +       |
| + | + | +   | +   | +     | +   | +  | -     | +      | +      | +       | -       |

The other operations need to cut out the - inputs instead to show up:

| A | B | MIN | AND | A * B | MAX | OR | A + B | Major  | A -> B | A <-> B | A <!> B |
|---|---|-----|-----|-------|-----|----|-------|--------|--------|---------|---------|
| 0 | 0 | 0   | -   | 0     | 0   | +  | 0     | 0      | +      | +       | -       |
| 0 | + | 0   | 0   | 0     | +   | +  | +     | 0      | +      | 0       | 0       |
| + | 0 | 0   | 0   | 0     | +   | +  | +     | 0      | 0      | 0       | 0       |
| + | + | +   | +   | +     | +   | +  | -     | +      | +      | +       | -       |





### Single Input Gates

Ternary has more 1 input gates than binary and many more are useful. The are 3^3^1=27 single input ternary gates vs 2^2^1=4 for binary.

| + | 0 | - | Number | Name  | Notes                                           |
|---|---|---|--------|-------|-------------------------------------------------|
| - | - | - |  -13   | False |                                                 |
| - | - | 0 |  -12   |       | Neg(Lax)                                        |
| - | - | + |  -11   |       | Neg(Ceil), F-test                               |
| - | 0 | - |  -10   | Abn   | Neg(Abs)                                        |
| - | 0 | 0 |  -9    |       | Neg(Flat)                                       |
| - | 0 | + |  -8    | Neg   |                                                 |
| - | + | - |  -7    | isZ   | Z-test                                          |
| - | + | 0 |  -6    | Inc   |                                                 |
| - | + | + |  -5    |       | Neg(Floor)                                      |
| 0 | - | - |  -4    |       | Saturated Dec                                   |
| 0 | - | 0 |  -3    |       | Dec(Abs)??                                      |
| 0 | - | + |  -2    | Dec   |                                                 |
| 0 | 0 | - |  -1    |       | F-filter                                        |
| 0 | 0 | 0 |  0     | Clear | Z-filter                                        |
| 0 | 0 | + |  1     |       | Flat(Neg), F-select                             |
| 0 | + | - |  2     |       | Inc(Neg) or Neg(Dec)                            |
| 0 | + | 0 |  3     |       | Inc(Abn)??, Z-select                            |
| 0 | + | + |  4     |       | Lax(Neg)                                        |
| + | - | - |  5     | Floor | T-test                                          |
| + | - | 0 |  6     |       | Dec(Neg) or Neg(Inc)                            |
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
    INC(NEG(A)) = NEG(DEC(A) = Gate 2
    DEC(NEG(A)) = NEG(INC(A) = Gate 6
Each gate is its own complement. which can be illustrated by combining the two descriptions of gate2 as an example.
    INC(NEG(NEG(DEC(A)))) = INC(DEC(A)) = A


#### Information destroying gates
These gates have less possible output states that input states. and thus lose information.  They cannot be reversed thus do not have a complementary action. Once an information destroying gate is brought into the sequence the entire sequence become information destroying and can't be reversed, thus the sequence wil map to single one of these 21 information destroying gates.
1. Absolute Value (-1->1, 0->0, 1->1)
2. Flatten Strict (-1->0, 0->0, 1->1)
3. Flatten Lax    (-1->0, 0->1, 1->1)

##### True, False and Clear
The most extreeme form of information losing gates, these completely disreguard the input. Thus in a chain of operations anything applied before them is meaningless, much like multipling by 0, and the final output of the sequence will always be fixed meanign the whole sequence map to one of these 3 gates.

### Multiple Input Gates
When you get to 2 input gate ternary logic explodes to 3^(3^2)=19683 while binary stays
with a more reasonable 2^2^2=16. This makes an exhaustive analysis of 2-input ternary
logic functions.

#### AND/MIN Gate

#### OR/MAX Gate

#### Addition

#### Full Adder
The balanced ternary full adder has the same two outputs(carry and sum) as a binary adder, but can have upto 4 inputs as the 2 trit output will not overflow. This means the ternary adder can add up to 3 numbers plus carry simultaneously. We will refer to the lesser adders as 1/3(2 input) and 2/3(3 input) adders.


### Functional Completeness

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

The gates that ignore there input only one is needed to as whatever gates we keep above can do the transformation. For now let's keep False as it can easily be turned int othe other two with INC and NEG.
```
FALSE(A) = NEG(TRUE(A))
CLEAR(A) = DEC(TRUE(A))
```

The remaining 18 gates. will need something to get reach them. I think any one of them should be able to be turned into all of them using the above transitions.
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

We start with stating that workign in discrete values any N-input function can
be defined in terms of a condition and an N-1 input function
```
                      / x[n] = -, F(x0,x1,...,x[n-1],-)
F(x0,x1,...,x[n]) =  {  x[n] = 0, F(x0,x1,...,x[n-1],0)
                      \ x[n] = +, F(x0,x1,...,x[n-1],+)
```



Links
-----

<https://en.wikipedia.org/wiki/Balanced_ternary>
<https://en.wikipedia.org/wiki/Ternary_numeral_system>
<https://en.wikipedia.org/wiki/Many-valued_logic>
<https://en.wikipedia.org/wiki/Three-valued_logic>
<https://en.wikipedia.org/wiki/BL_(logic)>
<https://en.wikipedia.org/wiki/MV-algebra>
<https://en.wikipedia.org/wiki/%C5%81ukasiewicz_logic>

