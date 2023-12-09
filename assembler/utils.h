/* déclaration de librairies*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct{
    int format ;
    uint32_t opcode  ;
    uint32_t registres[4] ;
    uint32_t decalages[4];
} Instruction ;

/* déclaration de fonctions */
char *normalisation(char *line);// permet d'enlever les virgules
char *rcp_instr(char *line, char *cons); // récupération de l'instruction
uint32_t identification(char *line); // identification de l'instruction
void recup_arg(int a, char *line,char tab[2][10]);// récupère trois arguments
void concatener(char *line, const char *st1, const char *st2);
int find_index_char(char *tab, char instr, int index);
int find_index_string(char tab[32][5], char *instr) ;
int normalisation_rgstr(char *tab);
uint32_t assemble(Instruction a);