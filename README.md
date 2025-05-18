This project implements a compiler for a C-like language using **Flex** (for lexical analysis) and **Yacc** (for parsing). It includes semantic checks and builds an abstract syntax tree (AST).

Ensure you have the following tools installed:

- `flex` – lexical analyzer generator
-`yacc` – parser generator
- `gcc` – C compiler

for building the compiler:
1. yacc -d -v parser.y
2. flex lexer.l
3. gcc  lex.yy.c  y.tab.c  -o myc  -lm


To run the compiler on a source file:
1. make sure you have a file name: file.txt
2. run on the terminal: ./myc < file.txt