#include "executer.h"
uint32_t opcode[5] = {51,3,12323,99,111};
char type_instr[5] = {'R','I','S','B','J'};
char instruction[11][5] = {"add","sub","addi","ld","sd","beq","bne","blt","bge","jal"} ;

void lecture(uint32_t *memoire){
    int i = 0 ;
    while(memoire[i]!=0){
        printf("%08x\n",memoire[i]);
        i++;
    }
}

void ecriture_registre(uint32_t *reg,FILE *file){
    int i=0;
    while(i!=32){
        fprintf(file,"x%d : %d\n",i,reg[i]);
        i++;
    }
}
int find_opcode(uint32_t line){
    for(int i=0;i<5;i++){
        if(opcode[i]==(127&line)) return i;
    }
    if(3==(3&line)) return 1; // le type I est un peu embêtant
    return -1;
}

int find_index_string(char tab[32][5], char *instr) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(tab[i], instr) == 0) {
            return i;
        }
    }
    return -2;
}

void afficher_instr(Instruction D){
    printf("---------------\n");
    printf("instr : %s\n",D.instr);
    printf("rd : %i\n",D.rd);
    printf("rs1 : %i\n",D.rs1);
    printf("rs2 : %i\n",D.rs2);
    printf("imm: %i\n",D.imm);

}
void decode(uint32_t line, Instruction *D){
    int index = find_opcode(line);
    switch(index){
        //R-type
        case 0 :if ((32<<25)==((127<<25)&line)) strcpy(D->instr,"sub") ;
                else {strcpy(D->instr,"add");}
                D->rd  = ((31<<7)&line)>>7;
                D->rs1 = ((31<<15)&line)>>15 ;
                D->rs2 = ((31<<20)&line)>>20;
                //printf("%s x%i x%i x%i \n",D->instr,D->rd,D->rs1,D->rs2);
                break ;
        //I-type
        case 1 :if ((3<<12)==((7<<12)&line)) strcpy(D->instr,"ld") ;
                else { strcpy(D->instr,"addi") ;}
                D->rd  =  ((31<<7)&line)>>7;
                D->rs1 =  ((31<<15)&line)>>15 ;
                D->imm = (((4095<<20)&line)>>20); if((2048&D->imm)==2048) D->imm*=-1;
                //printf("%s x%i x%i %i \n",D->instr,D->rd,D->rs1,D->imm);
                break ;
        //S-type
        case 2 : strcpy(D->instr,"sd" );
                D->imm = (((31<<7)&line)>>7) + (((255<<20)&line)>>20); if((2048&D->imm)==2048) D->imm*=-1;
                D->rs1 = ((31<<15)&line)>>15 ;
                D->rs2 = ((31<<20)&line)>>20 ;
                //printf("%s x%i x%i %i \n",D->instr,D->rd,D->rs1,D->imm);
                break ;
        //B-type
        case 3 :if((1<<12)==((7<<12)&line)) strcpy(D->instr,"bne")                                                         ;
                else if((4<<12)==((7<<12)&line)) D->instr = "blt" ;
                else if((5<<12)==((7<<12)&line)) D->instr = "bge";
                else {D->instr = "beq";}
                D->imm = (((1<<7)&line)<<4) + (((31<<8)&line)>>7) + (((1<<31)&line)>>19) + (((127<<25)&line)>>20);
                if((4096&D->imm)==4096) D->imm*=-1;
                D->rs1 = ((31<<15)&line)>>15;
                D->rs2 = ((31<<20)&line)>>20;
                //printf("%s x%i x%i %i \n",D->instr,D->rs1,D->rs2,D->imm);
                break ;
        //J-type
        case 4 :D->instr = "jal" ;
                D->rd  = ((31<<7)&line)>>7;
                D->imm = (((1<<31)&line)>>11) + (((1023<<21)&line)>>20) + (((1<<20)&line)>>9) + ((255<<11)&line);
                if((1048576&D->imm)==1048576) D->imm*=-1;
                //printf("%s x%i %i \n",D->instr,D->rd,D->imm);
        break ;
    }

}

void executer(Instruction D, uint32_t reg[33]){
    int instr = find_index_string(instruction,D.instr);
    switch(instr){
        case 0 : reg[D.rd] = reg[D.rs1] + reg[D.rs2] ; reg[32]+=1; break ; //add
        case 1 : reg[D.rd] = reg[D.rs1] - reg[D.rs2] ; reg[32]+=1; break ; // sub
        case 2 : reg[D.rd] = reg[D.rs1] + D.imm ; reg[32]+=1;break ; //addi
        case 3 : reg[D.rd] = reg[D.imm+reg[D.rs1]]; reg[32]+=1; break;
        case 4 : reg[D.imm+reg[D.rs1]] = reg[D.rs2] ; reg[32]+=1; break;
        case 5 : if(reg[D.rs1]==reg[D.rs2]) reg[32] += D.imm ;break;
        case 6 : if(reg[D.rs1]!=reg[D.rs2]) reg[32] += D.imm ;break;
        case 7 : if(reg[D.rs1]<reg[D.rs2])  reg[32] += D.imm  ;break;
        case 8 : if(reg[D.rs1]>=reg[D.rs2]) reg[32] += D.imm ;break;
        case 9 : reg[D.rd] = reg[32]+4; reg[32]+= D.imm; break;
    }
}