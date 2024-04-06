#include <stdio.h>
#include <stdint.h>
int main(){
    fprintf(stdout, "Advice:   EERIE");
    FILE *pFile;
    if((pFile = fopen("en_US.dic", "r")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading and writing\n");
        return 0;
    }
    while(!feof(pFile)){
        fgets()

        char feedback[10];
        fprintf(stdout, "Feedback: ");
        fscanf(stdin, "%s", feedback);
    }

    return 0;
}