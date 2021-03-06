Assembly
========

## Files
| Files      | Description                                                    |
-------------|----------------------------------------------------------------|
|yamp.py     | Yet Another Macro Preprocessor used to provide macros          |
|aliases.ymp | Standard set of macros for use with assembler                  |


## Code

The assemby code is formated to work well with an extended C-style preprocessor.
This allows pseudo instruction aliases to be easily introduced and seemlessly
integrated.


Instructions fall into one of 3 forms, matching the bit ordering options.
```
    INST1( R1, immediate );
    INST2( R1, R2+MOD, immediate );
    INST3( R1, R2+MOD, R3+MOD );
```
Multiple instructions can be placed on a single line using the semicolons as
seperators.

C-style comments are supported. being stripped out by the preprocessor.
The preprocessor supports a bunch of #directives and defines.


| Directive        | Description                                              |
|------------------|----------------------------------------------------------|
| `#include`       | Used to include other files contents                     |
| `#define`        | Defines a macro substitution object-like or function-like|
| `#undef`         | Removes a macro definition                               |
| `#if`            | Allows conditional inclusion of parts of file            |
| `#ifdef`         |                                                          |
| `#ifndef`        |                                                          |
| `#elif`          |                                                          |
| `#else`          |                                                          |
| `#endif`         |                                                          |
| `#pragma`        |                                                          |
| `#line`          | Sets line number for debugging / analysis purposes       |
| `#error`         | Emits an error and terminates if processed               |
| `#warning`       | Emits a warning and carries on if processed              |
| `#assert`        | Emits an error and terminates if clause is false         |
| `#for in`        | Allows repititive inclusion of parts of file             |
| `#endfor`        |                                                          |
| `#enum`          | Allows C-style enum to be treated as macros              |
| `#`              |                                                          |
| `##`             | Concatenate tokens                                       |
| `...`            | Variadic arguments to macro                              |
| `__FILE__`       |                                                          |
| `__LINE__`       |                                                          |
| `__DATE__`       |                                                          |
| `__TIME__`       |                                                          |
| `__TIMESTAMP__`  |                                                          |
| `SPLIT()`        | Splits token into multiple single character tokens       |
| `MERGE()`        | Merges list of tokens into 1 token                       |
| `defined()`      | true, false if is defined preprocessor symbol            |
| `//`             | Comment to end of line                                   |
| `/*`             | Begin block comment                                      |
| `*/`             | End block comment                                        |

| CLI              | Description                                              |
|------------------|----------------------------------------------------------|
| `-D`             | Add define at command line                               |
| `-I`             | Add include path at command line                         |
| `--include`      | Add include file at command line                         |
