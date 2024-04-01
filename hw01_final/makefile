CC = gcc

all:
	-gcc -c mystring.c hw0101.c
	-gcc hw0101.o mystring.o -o hw0101
	-gcc -g -c hw0102.c mycal.c
	-gcc hw0102.o mycal.o -o  hw0102
	-gcc -g -c hw0103.c mychain.c
	-gcc hw0103.o mychain.o -o hw0103
	-gcc -g -c hw0104.c mymaze.c 
	-gcc hw0104.o mymaze.o -o hw0104 
	-gcc -g hw0105.c -o hw0105

clean:
	rm -f hw010{1..5} hw010{1..5}.o *.o
