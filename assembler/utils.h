/* déclaration de librairies*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

// structure d'instruction de base
typedef struct{
    int format ;
    uint32_t opcode  ;
    uint32_t registres[4] ;
    uint32_t decalages[4];
} Instruction ;

/* déclaration de fonctions */
char *normalisation(char *line);
void rcp_instr(char *line, char *cons);
void recup_arg(int a, char *line,char tab[2][10]);
void concatener(char *line, const char *st1, const char *st2);
int find_index_char(char *tab, char instr, int index);
int find_index_string(char tab[32][5], char *instr) ;
int normalisation_rgstr(char *tab);
uint32_t assemble(Instruction a);
uint32_t identification(char *line);