# HACK SOM Assembler

A [HACK](https://github.com/aalhour/Assembler.hack#:~:text=hack%20is%20a%2016%2Dbit,the%20name%20of%20the%20computer.) assembler written in [SOM](http://som-st.github.io/) (a small dialect of Smalltalk).

Rather than implementing a parser and creating an external DSL for the assembler, this assembler
uses native SOM syntax to create an internal DSL. This has a number of advantages:

1. No parser needed to be written.
2. Full language features. Language features like ignoring whitespace, comments, variables, conditionals, sub-routines, inheritance, libraries, loops, etc. are all added to the assembler without any additional effort.
3. Extensible. Rather than just being a simple literal assembler, powerful macros can be written in SOM to incrementally make the assembler into a higher-level language.
