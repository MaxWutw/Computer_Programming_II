CC = gcc

all:
	-gcc -c mystring.c hw0101.c
	-gcc hw0101.o mystring.o -o hw0101
	-gcc -g -c hw0102.c mycal.c
	-gcc hw0102.o mycal.o -o  hw0102
	-gcc -g -fsanitize=address -c hw0103.c mychain.c
	-gcc -fsanitize=address hw0103.o mychain.o -o hw0103 -lasan -lubsan 
	-gcc -g -fsanitize=address -c hw0104.c mymaze.c 
	-gcc hw0104.o mymaze.o -o hw0104 -lasan -lubsan 
	-gcc -g hw0105.c -o hw0105

clean:
	rm -f hw010{1..4} hw010{1..4}.o *.o