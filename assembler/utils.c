#include "utils.h"

char *normalisation(char *line){
    int i=0;
    if (line[0]=='#'){  //test pour les commentaires
        *line='\0';
    }
    while (line[i]!='\0'){
        if (line[i]==','){
            line[i]=' ';
        }
        i++;
    }
    return line;
}

char *identification(char *line){
    int i=0;
    char cons = '';
    while (line[i]!=' '){
        cons[i] = line[i]; 
    }
    case(cons){
        case "add": e_addi(line);
    }

}
