Notes
=====


Interesting gates
-----------------

### Single Input Gates

Ternary has more 1 input gates than binary and many more are useful. The are 3^3^1=9 single input ternary gates vs 2^2^1=4.


#### NEG/NOT Gate
Balanced ternary gates have a tighter relationship between logical and mathmatical negation. The are the same bitwise operator. It is its own complement.

### INC and DEC Gate
These gates provide the two different possible mappings that result in every possible input being mapped to a different value. These gates are also complementary and can arithmetically be thought of as single trit Increment or decrement.

#### Information destroying gates
These gates have less possible output states that input states. and thus lose information.  They cannot be reversed in all cases thus do not have a complementary action. 
1. Absolute Value (-1->1, 0->0, 1->1)
2. Flatten Strict (-1->0, 0->0, 1->1)
3. Flatten Lax    (-1->0, 0->1, 1->1)

### Multiple Input Gates

#### AND/MIN Gate

#### OR/MAX Gate



#### Full Adder
The balanced ternary full adder has the same two outputs(carry and sum) as a binary adder, but can have upto 4 inputs as the 2 trit output will not overflow. This means the ternary adder can add up to 3 numbers plus carry simultaneously. We will refer to the lesser adders as 1/3(2 input) and 2/3(3 input) adders.




Mathematical Properties
-----------------------


Logic Properties
----------------
In Ternary Logic the extra value is used to indicate uncertainty.  The Logic Values are:

| Trit | Logic Meaning | Aliases                            |
|------|---------------|------------------------------------| 
| 1    | True          | +,Y,T,100%                         |
| 0    | Other         | Maybe, Don't Care, Unknown, 50%, X |
| -1   | False         | -,N,F,0%                           |


