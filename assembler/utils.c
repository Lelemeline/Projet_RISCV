#include "utils.h"

char instruction[13][4] = {"add","sub","addi","ld","sd ","beq","bne","blt","bge","jal"} ;
char registre[32][5] = {"zero","ra","sp","gp","tp","t0","t1","t2","s0","s1","a0","a1","a2","a3","a4","a5","a6","a7","s2","s3","s4","s5","s6","s7","s8","s9","s10","s11","t3","t4","t5","t6"} ;
char type_instr[5] = {'R','I','S','B','J'};
int decalage[5][4] = {{7,15,20},{7,15,20},{7,15,20,25},{7,15,20,25},{7,12}};
uint32_t opcode[5] = {51,3,3,99,111};


char *normalisation(char *line){
    int i=0;
    if (line[0]=='#' || line[0]=='\n'){ // on détecte les commentaire et les lignes vides : on les dégage
        line[0]='\0'; // ligne vide
        return line;
    }
    while (line[i]!='\0'){ // tant qu'une ligne de code n'est pas vide
        if (line[i]==','){
            line[i]=' ';
         if (line[i]>='A' && line[i]<='Z')
            line[i]-='A'-'a';
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

int find_index_char(char *tab, char instr, int index) {
    if (*tab == instr) return index;
    if (*tab == '\0') return -1;
    return find_index_char(tab + 1, instr, index + 1);
}

int find_index_string(char tab[32][5], char *instr) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(tab[i], instr) == 0) {
            return i;
        }
    }
    return -1;
}

int conversion(char *tab){
    int i=0;
    int nombre;
    while(tab[i]!='\0'){
        nombre+=tab[i]*10**i;
    }
    return nombre;
}

int find_type(int x){
     if(0<=x && x<2) return 0 ;
     if (2<=x && x<4) return 1;
     if (x==4) return 2;
     if (5<=x && x<9) return 3;
     if (x==9) return 4;
     return -1;
}
int normalisation_rgstr(char *tab) {
    if (tab[0] == 'x') return atoi(tab+1);
    else return find_index_string(registre, tab);
}

void affichage_instr( Instruction a){
    printf("----------------------\n");
    printf("opcode :%i\n",a.opcode);
    for (int i=0;i<3;i++){
        printf("registre %i : %i\n",i,a.registres[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        printf("décalage %i : %i\n",i,a.decalages[i]);
    }
    printf("----------------------\n");

}

// void recup_1_arg(char *line, char *rd, char *imm){
//      while(*(line++)!=' '){}
//      *line ++;
//      while(*(line++)= *(rd++)!=' '){}
//      *line ++;
//      while(*(line ++) = *(imm ++)!= ' '){}
// }


// void recup_2_arg(char *line, char *rd, char *imm){
//      while(*(line++)!=' '){}
//      *line ++;
//      while(*(line++)= *(rd++)!=' '){}
//      *line ++;
//      while(*(line ++) = *(imm ++)!= ' '){}
// }


// void recup_3_arg(char *line,char tab[3][10]) {
//      while(*line++ !=' '){}
//      for(int i = 0; i<3 ;i++){
//           char *registre = malloc(strlen(line));
//           while(*line++!=' '){}
//           while(*line++!=' '){
//                line = registre ;
//           }
//           *registre ++ =  '\0' ;
//           strcpy(tab[i],registre);
//           printf("%s",registre);
//           free(registre);
//      }
// }
void recup_3_arg(char *line,char tab[2][10]) {
    while (*line != ' ') {
        line++;
    }
    line++;
    for (int i = 0; i < 3; i++) {
        char *registre = malloc(10);
        int j = 0;
        while (*line != ' ' && *line != '\0' && *line!= '\n') {
            registre[j++] = *line++;
        }
        registre[j] = '\0';
        printf("%s\n",registre);
        strcpy(tab[i],registre);
        free(registre);
        if (*line == ' ') {
            line+=2;
        }
    }
}

uint32_t assemble(Instruction a){
     uint32_t code = a.opcode;
     for(int i =0; i<3 ; i++){
          code += (a.registres[i]<<a.decalages[i]);
     }
     return code;
}

uint32_t identification(char *line){
     char *cons = malloc(strlen (line)+1); // allocation de mémoire dynamique
     rcp_instr(line,cons);
     int format = find_type(find_index_string(instruction,cons));
     uint32_t code_assemble;
     if(format == 0){
               Instruction R ;
               memcpy(R.decalages, decalage[find_index_char(type_instr, type_instr[format], 0)], sizeof(R.decalages));
               R.opcode=opcode[find_index_char(type_instr, type_instr[format], 0)];
               if(strcmp(cons,"sub")==0) R.opcode += (32<<25);
               char registre[2][10];
               recup_3_arg(line,registre);
               for (int i= 0; i<3 ; i++){
                    R.registres[i] = normalisation_rgstr(registre[i]);
               }
               code_assemble = assemble(R);
               printf("assembler : %i\n",assemble(R));
     }
     else if (format == 1) {
               Instruction I ;
               memcpy(I.decalages, decalage[find_index_char(type_instr, type_instr[format], 0)], sizeof(I.decalages));
               I.opcode=opcode[find_index_char(type_instr, type_instr[format], 0)];
               if(strcmp(cons,"addi")==0) I.opcode += 16;
               else I.opcode = (3<<12);
               char registre[2][10];
               recup_3_arg(line,registre);
               for (int i= 0; i<2 ; i++){
                    I.registres[i] = normalisation_rgstr(registre[i]);
               }
               affichage_instr(I);
               code_assemble = assemble(I);
               printf("assembler : %i\n",assemble(I));

     }
     else if (format == 2) {}
     else if (format == 3) {}
     else if (format == 4) {}



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
        /*pour l'instant traite les lignes vides*/
        return 0;
    }
    free(cons); // libération de mémoire
    return code_assemble;
}



 // Instruction Add ;
          // memcpy(Add.decalages, decalage[find_index_char(type_instr, 'R', 0)], sizeof(Add.decalages));
          // Add.opcode=opcode[find_index_char(type_instr, 'R', 0)];
          // printf("opcode = %i\n",Add.opcode);
          // printf("normalisation registre = %i\n",normalisation_rgstr("a2"));


          // printf("registre 1 = %d ",Add.registres[0]);
          // printf("registre 2 = %d ",Add.registres[1]);
          // printf("registre 3 = %d\n",Add.registres[2]);
