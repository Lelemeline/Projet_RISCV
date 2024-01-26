#include "executer.h"
uint32_t opcode[5] = {51,3,35,99,111};
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
    int j =-1 ;
    for(int i=0;i<5;i++){
        if(opcode[i]==(127&line)) j =i;
    }
     if(3==(3&line) && j==-1) return j= 1; // le type I est un peu embêtant
     return j ;
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
int puissance(int  n){
    int N = n;
    int y = 1;
    int z = 2;
    while(N!=0){
        if(N%2==0){
            N/=2;
            z *= z;
            }
        else {
            N/=2;
            y *= z;
            z*=z;
        }
    }
    return(y);
}

void init_struct(Instruction *D){
    D->rd = 0;
    D->rs1 = 0;
    D->rs2 = 0;
    D->imm = 0;
}
int conversion_signes(int signe,int x){
    int y = puissance(x) - 1;
    signe =  ~(y & signe);
    signe =((y & signe) + 1)*-1 ;
    return signe ;
}
void decode(uint32_t line, Instruction *D){
    int index = find_opcode(line);
    //printf("index : %i\n",index);
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
                D->rd  = ((31<<7)&line)>>7;
                D->rs1 = ((31<<15)&line)>>15 ;
                D->imm = (((4095<<20)&line)>>20); if((2048&D->imm)==2048) D->imm = conversion_signes(D->imm,12) ;//conversion_signes(D->imm);
                if((4096&D->imm)==4096) D->imm = conversion_signes(D->imm,11);
                //printf("%s x%i x%i %i \n",D->instr,D->rd,D->rs1,D->imm);
                break ;
        //S-type
        case 2 :strcpy(D->instr,"sd");
                D->imm = (((31<<7)&line)>>7) + (((255<<20)&line)>>20); if((2048&D->imm)==2048) D->imm*=-1;
                D->rs1 = ((31<<15)&line)>>15 ;
                D->rs2 = ((31<<20)&line)>>20 ;
                if((4096&D->imm)==4096) D->imm = conversion_signes(D->imm,11);
                //printf("%s x%i x%i %i \n",D->instr,D->rd,D->rs1,D->imm);
                break ;
        //B-type
        case 3 :if((1<<12)==((7<<12)&line)) strcpy(D->instr,"bne")                                                         ;
                else if((4<<12)==((7<<12)&line)) D->instr = "blt" ;
                else if((5<<12)==((7<<12)&line)) D->instr = "bge";
                else {D->instr = "beq";}
                D->imm = (((1<<7)&line)<<4) + (((0xF<<8)&line)>>7) + (((1<<31)&line)>>19) + (((127<<25)&line)>>20);
                if((8192&D->imm)==8192) D->imm = conversion_signes(D->imm,11)>>2;
                else D->imm/=4;
                D->rs1 = ((31<<15)&line)>>15;
                D->rs2 = ((31<<20)&line)>>20;
                //printf("%s x%i x%i %i \n",D->instr,D->rs1,D->rs2,D->imm);
                break ;
        //J-type
        case 4 :D->instr = "jal" ;
                D->rd  = ((31<<7)&line)>>7;
                D->imm = (((1<<31)&line)>>11) + (((1023<<21)&line)>>20) + (((1<<20)&line)>>9) + ((255<<11)&line);
                if((1048576&D->imm)==1048576) D->imm= conversion_signes(D->imm,19)>>2;
                else D->imm/=4;
                //printf("%s x%i %i \n",D->instr,D->rd,D->imm);
        break ;
    }
    afficher_instr(*D);
    //printf("%s\n",D->instr);
}

void executer(Instruction D, uint32_t reg[33]){
    int instr = find_index_string(instruction,D.instr);
    switch(instr){
        case 0 : reg[D.rd] = reg[D.rs1] + reg[D.rs2] ; reg[32]+=1; break ; //add
        case 1 : reg[D.rd] = reg[D.rs1] - reg[D.rs2] ; reg[32]+=1;break ; // sub
        case 2 : reg[D.rd] = reg[D.rs1] + D.imm      ; reg[32]+=1;break ; //addi
        case 3 : reg[D.rd] = reg[(D.imm/4)&reg[D.rs1]]; reg[32]+=1;break;  //ld
        case 4 : reg[D.imm+reg[D.rs1]] = reg[D.rs2] ; reg[32]+=1;break ; //sd
        case 5 : if(reg[D.rs1]==reg[D.rs2]) {reg[32] += D.imm ;} else reg[32]+=1; break; //beq
        case 6 : if(reg[D.rs1]!=reg[D.rs2]) {reg[32] += D.imm ;} else reg[32]+=1;break; //bne
        case 7 : if(reg[D.rs1]<reg[D.rs2])  {reg[32] += D.imm ;} else reg[32]+=1;break; //blt
        case 8 : if(reg[D.rs1]>=reg[D.rs2]) {reg[32] += D.imm ;} else reg[32]+=1;break; //bge
        case 9 : if(D.rd!=0) {reg[D.rd] = reg[32]+1;} reg[32]+=  D.imm; break ; //jal
    }
    //printf("fin execution\n");
}