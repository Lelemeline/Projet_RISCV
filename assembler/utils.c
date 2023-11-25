#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

char *normalisation(char *line){
    int i=0;
    if (line[0]=='#' || line[0]=='\n'){ // on détecte les commentaire et les lignes vides : on les dégage
        line[0]='\0'; // ligne vide
        return line;
    }
    while (line[i]!='\0'){ // tant qu'une ligne de code n'est pas vide
        if (line[i]==','){
            line[i]=' ';
        }
        i++;
    }
    return line;
}

char *rcp_instr(char *line, char *cons) {
    char *original_dest = cons;
    while (*line != ' ') {
        *cons++ = *line++;
    }
    *cons = '\0';
    return original_dest;
}


char *identification(char *line){
    char *cons = malloc(strlen (line));
    rcp_instr(line,cons);
    if(strcmp(cons,"addi")==0) {
        /* procédure appropriée*/
        e_addi(line);
    }
    else if (strcmp(cons,"sub")==0){
         /* procédure appropriée*/
    }
    else if (strcmp(cons,"add")==0) {
         /* procédure appropriée*/
    }
    else if (strcmp(cons,"ld")==0){
         /* procédure appropriée*/
    }
    else if (strcmp(cons,"sd")==0){
         /* procédure appropriée*/
    }
    else if (strcmp(cons,"beq")==0){
         /* procédure appropriée*/
    }
    else if (strcmp(cons,"bne")==0){
         /* procédure appropriée*/
    }
    else if (strcmp(cons,"blt")==0){
         /* procédure appropriée*/
    }
    else if (strcmp(cons,"bge")==0){
         /* procédure appropriée*/
    }
    else if (strcmp(cons,"jal")==0){
         /* procédure appropriée*/
    }
    else if (strcmp(cons,"j")==0){
         /* procédure appropriée*/
    }
    else if (strcmp(cons,"li")==0){
         /* procédure appropriée*/
    }
    else if (strcmp(cons,"mv")==0){
         /* procédure appropriée*/
    }
    else {
        /*renvoi d'erreur*/
    }
    free(cons);
    return line ;
}