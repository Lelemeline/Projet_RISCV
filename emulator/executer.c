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
        fprintf(file,"x%d = %d\n",i,reg[i]);
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


void decode(uint32_t line){
    Instruction D ;
    D.instr = malloc(5*sizeof(char));
    int index = find_opcode(line);
    switch(index){
        case 0 :if ((32<<25)==((127<<25)&line)) strcpy(D.instr,"sub") ;
                else {strcpy(D.instr,"add");}
                D.rd  = ((31<<7)&line)>>7;
                D.rs1 = ((31<<15)&line)>>15 ;
                D.rs2 = ((31<<20)&line)>>20;
                //printf("%s x%i x%i x%i \n",D.instr,D.rd,D.rs1,D.rs2);
                break ;
        case 1 :if ((3<<12)==((7<<12)&line)) strcpy(D.instr,"ld") ;
                else { strcpy(D.instr,"addi") ;}
                D.rd  =  ((31<<7)&line)>>7;
                D.rs1 =  ((31<<15)&line)>>15 ;
                D.imm =  ((4095<<20)&line)>>20;
                //printf("%s x%i x%i %i \n",D.instr,D.rd,D.rs1,D.imm);
                break ;
        case 2 : strcpy(D.instr,"sd" );
                D.imm = (((31<<7)&line)>>7) + (((4064<<25)&line)>>25);
                D.rs1 = ((31<<15)&line)>>15 ;
                D.rs2 = ((31<<20)&line)>>20 ;
                //printf("%s x%i x%i %i \n",D.instr,D.rd,D.rs1,D.imm);
                break ;
        case 3 :if((1<<12)==((7<<12)&line)) strcpy(D.instr,"bne")                                                         ;
                else if((4<<12)==((7<<12)&line)) D.instr = "blt" ;
                else if((5<<12)==((7<<12)&line)) D.instr = "bge";
                else {D.instr = "beq";}
                D.imm = (((1<<7)&line)<<4) + (((30<<8)&line)>>7) + (((1<<31)&line)>>19) + (((2015<<25)&line)>>20);
                D.rs1 = ((31<<15)&line)>>15;
                D.rs2 = ((31<<20)&line)>>20;
                //printf("%s x%i x%i %i \n",D.instr,D.rs1,D.rs2,D.imm);
                break ;
        case 4 : D.instr = "jal" ;
                D.rd  = ((31<<7)&line)>>7;
                D.imm = (((1<<31)&line)>>11) + (((1023<<21)&line)>>20) + (((1<<20)&line)>>9) + ((255<<11)&line);
                //printf("%s x%i %i \n",D.instr,D.rd,D.imm);
        break ;
    }

}

void executer(Instruction D){
    // procédure
}