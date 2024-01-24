#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *instr ;
    uint32_t rd ;
    uint32_t rs1;
    uint32_t rs2;
    uint32_t imm ;
} Instruction ;
uint32_t memoire[16*1024];
void lecture(uint32_t *memoire);
void ecriture_registre(uint32_t *reg,FILE *file);
int find_opcode(uint32_t line);
void afficher_instr(Instruction D);
int find_index_string(char tab[32][5], char *instr);
void decode(uint32_t line,Instruction *D);
void executer(Instruction D,uint32_t reg[33]);
int puissance (int  n);
int conversion_signes(int signe,int x);
void init_struct(Instruction *D);