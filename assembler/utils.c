#include "utils.h"

char *normalisation(char *line){
    int i=0;
    while (line[i]!='\0'){
        if (line[i]==','){
            line[i]=' ';
        }
        i++;
    }
    return line;
}
