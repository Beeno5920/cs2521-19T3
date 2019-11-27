test: testTextbuffer.o textbuffer.o
	gcc -Wall -Werror -std=c11 -g -lm -o test testTextbuffer.o textbuffer.o

testTextbuffer.o: testTextbuffer.c textbuffer.h
	gcc -Wall -Werror -c testTextbuffer.c

textbuffer.o: textbuffer.c
	gcc -Wall -Werror -c textbuffer.c
