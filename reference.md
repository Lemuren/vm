Language Reference
==================
A program is a series of instructions and labels that operate a stack machine.
In addition to the stack, you also have six registers: A, B, C, D, E, and F.
All arithmetic is done with integers, both negative and positive.

The following example program will print `15`.

```
SET A 10    ; Set the A register to 10.
PUSH A      ; Push the value contained in A onto the stack.
            ; The stack is now [ 10 ].
SET A 5     ; Set the A register to 5.
PUSH A      ; Push the value contained in A onto the stack.
            ; The stack is now [ 5, 10 ].
ADD         ; Add the top two values of the stack together, and push the result on top of the stack.
            ; The stack is now [ 15 ].
POP         ; Pop the top of the stack onto the screen.
            ; The stack is now [ ], i.e. empty.
HLT         ; Halt the program.
```

Using labels and jumps you can branch and conditionally execute code.
Here's a simple implementation of a loop, printing `1` to `10`.

```
; We'll loop 10 times in total and start at 1.
PUSH 11
PUSH 1

loop:
  ; We print the current value onto the screen, making sure we still
  ; have it on top of the stack afterwards.
  POP A
  PUSH A
  PUSH A
  POP

  ; Increment loop variable.
  PUSH 1
  ADD

  JB loop

HLT
```


Instructions
------------
Here you will find a complete instruction reference.

| Instruction | Operand(s)       | Description                                                                            |
|-------------|------------------|----------------------------------------------------------------------------------------|
| HLT         | -                | Halt program execution.                                                                |
| SET         | REGISTER NUMBER  | Set the value of a register.                                                           |
| PUSH        | REGISTER/NUMBER  | Push a register or immediate number onto the stack.                                    |
| POP         | [REGISTER]       | Pop the top of the stack. Without a register, the value will be printed to the screen. |
| PEEK        | REGISTER         | Set register to the value at the top of the stack.                                     |
| ADD         | -                | Add the top two values of the stack together and push it.                              |
| SUB         | -                | Subtract the top two values of the stack and push it.                                  |
| MUL         | -                | Multiply the top two values of the stack and push it.                                  |
| DIV         | -                | Divide the top two values of the stack and push it.                                    |
| MOD         | -                | Modulo the top two values of the stack and push it.                                    |
| JMP         | LABEL            | Jump to a label.                                                                       |
| JE          | LABEL            | Jump to a label (if top two values of stack are equal).                                |
| JNE         | LABEL            | Jump to a label (if top two values of stack are not equal).                            |
| JA          | LABEL            | Jump to a label (if top of stack is greater than second top of stack).                 |
| JB          | LABEL            | Jump to a label (if top of stack is lesser than second top of stack).                  |
| PRINT       | -                | Print a C-style (null-terminated) string from the top of the stack.                    |
| SCAN        | -                | Scans input, storing it either as an integer or a C-style string on the stack.         |


Grammar
-------
The complete syntax in EBNF is described below.

```
program     = { line } ;

line        = [ statement ] [ comment ] newline
              | [ statement ] [ comment ] EOF ;

statement   = label [ instruction ] | instruction ;

comment     ";" TEXT ;

label       = IDENTIFIER ":" ;

op          = NUMBER | register ;

instruction = HLT
            | PUSH op
            | POP [register]
            | PEEK register
            | SET register NUMBER
            | ADD
            | SUB
            | MUL
            | DIV
            | JMP IDENTIFIER
            | JE IDENTIFIER
            | JNE IDENTIFIER
            | JA IDENTIFIER
            | JB IDENTIFIER
            | PRINT
            | SCAN ;

register = "A" | "B" | "C" | "D" | "E" | "F" ;
```

