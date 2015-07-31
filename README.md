# B.F.I.T. - BrainFuck Interpreter Terminal

Um interpretador de Brainfuck com um terminal interativo que facilita o uso e entendimento da liguagem.

## Motivação

Me foder com C e aprender BrainFuck... Está sendo divertido.

## Limitações

O programa está muito usual, mas existem casos em que ele não interpreta como deveria e executa alguns loops de forma errada.

## Dependências

A principio o software possui uma única dependência, uma lib chamada readline.

## Help Page

>"B.F.I.T. = BrainFuck Interpreter Terminal
>    WARNING: When you use brainfuck operators, this terminal discard all characters non BF symbols
>    Terminal commands:    print: switch print mode to int or char
>        debug: turn debug mode ON/OFF
>        help: show those informations
>    BrainFuck Operators:
>        '>' = increment the data pointer (to point to the next cell to the right).
>        '<' = decrement the data pointer (to point to the next cell to the left).
>        '+' = increment (increase by one) the byte at the data pointer.
>        '-' = decrement (decrease by one) the byte at the data pointer.
>        '.' = output the byte at the data pointer.
>        ',' = accept one byte of input, storing its value in the byte at the data pointer.
>        '[' = if the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.
>        ']' = if the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command.
>
>    BFIT was created by: Amatsukan

## License
    /** ----------------------------------------------------------------------------
    * \"THE BEER-WARE LICENSE\" (Revision 42):
    * <phk@FreeBSD.ORG> wrote this file. As long as you retain this notice you
    * can do whatever you want with this stuff. If we meet some day, and you think
    * this stuff is worth it, you can buy me a beer in return Luiz Carlos{Amatsukan}
    * ----------------------------------------------------------------------------*/"