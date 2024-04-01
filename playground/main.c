#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
void func2(){
	printf("the static number is: %d", num);
}

void func(static int32_t num, int32_t b){
	func();
}
int main() {
    func(50, 100);

	return 0;
}
