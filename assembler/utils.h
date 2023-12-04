/* déclaration de librairies*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct{
    uint32_t opcode  ;
    uint32_t registres[3] ;
    uint32_t decalages[4];
} Instruction ;

/* déclaration de fonctions */
char *normalisation(char *line);// permet d'enlever les virgules
char *rcp_instr(char *line, char *cons); // récupération de l'instruction
uint32_t identification(char *line); // identification de l'instruction
void recup_2_arg(char *line, char *rd, char *imm); // recupere deux arguments
void recup_3_arg(char *line,char tab[2][10]);// récupère trois arguments
void ecriture(char nomFichier[], char *donnee) ;
int find_index_char(char *tab, char instr, int index);
int find_index_string(char tab[32][5], char *instr) ;
int normalisation_rgstr(char *tab);
uint32_t assemble(Instruction a);