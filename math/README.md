Notes
=====


Interesting gates
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




### Single Input Gates

Ternary has more 1 input gates than binary and many more are useful. The are 3^3^1=9 single input ternary gates vs 2^2^1=4.


#### NEG/NOT Gate
Balanced ternary gates have a tighter relationship between logical and mathmatical negation. The are the same bitwise operator. It is its own complement.

#### INC and DEC Gate
These gates provide the two different possible mappings that result in every possible input being mapped to a different value. These gates are also complementary and can arithmetically be thought of as single trit Increment or decrement.

#### Information destroying gates
These gates have less possible output states that input states. and thus lose information.  They cannot be reversed in all cases thus do not have a complementary action.
1. Absolute Value (-1->1, 0->0, 1->1)
2. Flatten Strict (-1->0, 0->0, 1->1)
3. Flatten Lax    (-1->0, 0->1, 1->1)


### Multiple Input Gates

#### AND/MIN Gate

#### OR/MAX Gate

#### Addition




#### Full Adder
The balanced ternary full adder has the same two outputs(carry and sum) as a binary adder, but can have upto 4 inputs as the 2 trit output will not overflow. This means the ternary adder can add up to 3 numbers plus carry simultaneously. We will refer to the lesser adders as 1/3(2 input) and 2/3(3 input) adders.




Mathematical Properties
-----------------------


Logic Properties
----------------
In Ternary Logic the extra value is used to indicate uncertainty.  The Logic Values are:

| Trit | Logic Meaning | Aliases                            |
|------|---------------|------------------------------------|
| 1    | True          | +,Y,P,T,100%                       |
| 0    | Other         | Maybe, Unknown, 50%, X             |
| -1   | False         | -,N,F,0%                           |


