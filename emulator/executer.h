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
// char registre[32][5] = {"zero","ra","sp","gp","tp","t0","t1","t2","s0","s1","a0","a1","a2","a3","a4","a5","a6","a7","s2","s3","s4","s5","s6","s7","s8","s9","s10","s11","t3","t4","t5","t6"} ;
uint32_t reg[33]; // 32 registres + PC
uint32_t memoire[16*1024];
void lecture(uint32_t *memoire);
void ecriture_registre(uint32_t *reg,FILE *file);
int find_opcode(uint32_t line);
void decode(uint32_t line);