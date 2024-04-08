#include <stdio.h>
#include <string.h>
#include <errno.h>
#define CUSTOMERROR 134 /*cutomize error message*/
int main() {
	errno = CUSTOMERROR;
    perror("Error");

	return 0;
}