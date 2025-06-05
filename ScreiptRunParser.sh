bison -d -v -t -o parser.tab.c parser.y
flex -d -o scanner.yy.c lexer.l
gcc -o c- scanner.yy.c parser.tab.c -lfl
export YYDEBUG=1
./c- error.txt 2> log.txt
