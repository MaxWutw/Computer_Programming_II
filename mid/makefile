CC = gcc

all:
	-gcc mid01.c -o mid01
	-gcc mid02.c -o mid02
	-gcc mid03.c -o mid03
	-gcc mid04.c -o mid04
	-gcc -c bmp_template.c bmp_func.c
	-gcc bmp_template.o bmp_func.o -o bmp_template

clean:
	rm -f mid0{1..4} *.o bmp_template