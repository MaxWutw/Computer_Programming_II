CC = gcc

all:
	-gcc hw0301.c -o hw0301
	-gcc -c hw0302.c utility.c
	-gcc hw0302.o utility.o -o hw0302
	-gcc -c hw0303.c bmp_func.c
	-gcc -g hw0303.o bmp_func.o -o hw0303
	# -gcc -g hw0304.c -o hw0304 -lm
	-gcc -g hw0305.c -o hw0305

clean:
	rm -f hw030{1..5} hw030{1..5}.o *.o