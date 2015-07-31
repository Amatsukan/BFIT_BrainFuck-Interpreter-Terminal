# B.F.I.T. - BrainFuck Interpreter Terminal

Um interpretador de Brainfuck com um terminal interativo que facilita o uso e entendimento da liguagem.

## Motivação

Me foder com C e aprender BrainFuck... Está sendo divertido.

## Limitações

O programa está muito usual, mas existem casos em que ele não interpreta como deveria e executa alguns loops de forma errada.

## Dependências

A principio o software possui uma única dependência, uma lib chamada readline.

## Help Page

>"B.F.I.T. = BrainFuck Interpreter Terminal<br/>
>&nbsp;&nbsp;&nbsp;&nbsp;   WARNING: When you use brainfuck operators, this terminal discard all characters non BF symbols<br/>
>&nbsp;&nbsp;&nbsp;&nbsp;   Terminal commands:    <br/>
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; print: switch print mode to int or char<br/>
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; debug: turn debug mode ON/OFF<br/>
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; help: show those informations<br/>
>&nbsp;&nbsp;&nbsp;&nbsp;BrainFuck Operators:<br/>
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'>' = increment the data pointer (to point to the next cell to the right).<br/>
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'<' = decrement the data pointer (to point to the next cell to the left).<br/>
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'+' = increment (increase by one) the byte at the data pointer.<br/>
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'-' = decrement (decrease by one) the byte at the data pointer.<br/>
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'.' = output the byte at the data pointer.<br/>
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;',' = accept one byte of input, storing its value in the byte at the data pointer.<br/>
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'[' = if the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.<br/>
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;']' = if the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command.<br/>
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br/>
>&nbsp;&nbsp;&nbsp;&nbsp;   BFIT was created by: Amatsukan<br/>

## License
    /** ----------------------------------------------------------------------------
    * \"THE BEER-WARE LICENSE\" (Revision 42):
    * <luiz.cfj@apilab.ufsc.br> wrote this file. As long as you retain this notice you
    * can do whatever you want with this stuff. If we meet some day, and you think
    * this stuff is worth it, you can buy me a beer in return Luiz Carlos{Amatsukan}
    * ----------------------------------------------------------------------------*/"
