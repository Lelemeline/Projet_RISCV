#include "utils.h"
char instruction[13][5] = {"add","sub","addi","ld","sd ","beq","bne","blt","bge","jal"} ;
char registre[32][5] = {"zero","ra","sp","gp","tp","t0","t1","t2","s0","s1","a0","a1","a2","a3","a4","a5","a6","a7","s2","s3","s4","s5","s6","s7","s8","s9","s10","s11","t3","t4","t5","t6"} ;
char type_instr[5] = {'R','I','S','B','J'};
int  decalage[5][4] = {{7,15,20},{7,15,20},{7,15,20,25},{7,15,20,25},{7,12}};
int  nbre_rgstr[5] = {3,3,4,4,2};
uint32_t opcode[5] = {51,3,12323,99,111};


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
    *cons++ = '\0';
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
    return -2;
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
void recup_arg(int a, char *line,char tab[2][10]) {
    while (*line != ' ') {
        line++;
    }
    line++;
    for (int i = 0; i < a; i++) {
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
void concatener(char *line, const char *st1, const char *st2) {
    while ((*st1 != '\0')) {*line++ = *st1++;}
    *line++ = ' ';
    while ((*st2 != '\0')) {*line++ = *st2++;}
    *line = '\0';
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
    uint32_t code_assemble;
    if (strcmp(cons,"j")==0){
        char *offset ;
        recup_arg(1,line,offset);
        char *ist = malloc(sizeof(line));
        concatener(ist,"jal x0, ","offset");
        return identification(ist);
    }
    else if (strcmp(cons,"li")==0){
       char *rgst[2][5];
       recup_arg(2,line,rgst);
       char *ist = malloc(sizeof(line));
       concatener(ist,"addi",rgst[0]);
       concatener(ist,ist,", zero, ");
       concatener(ist,ist,rgst[1]);
       printf("%s\n",ist);
       return identification(ist);
    }
    else if (strcmp(cons,"mv")==0){
        char *rgst[2][5];
        recup_arg(2,line,rgst);
        printf("%s\n",rgst[1]);
        char *ist = malloc(sizeof(line));
        concatener(ist,"addi",rgst[0]);
        concatener(ist,ist,", ");
        printf("%s\n",rgst[1]);
        concatener(ist,ist,rgst[1]);
        concatener(ist,ist,", 0");
        printf("%s\n",ist);
        return identification(ist);
    }
    else{
        int format = find_type(find_index_string(instruction,cons));
        Instruction L ;
        memcpy(L.decalages, decalage[find_index_char(type_instr, type_instr[format], 0)], sizeof(L.decalages));
        L.opcode=opcode[find_index_char(type_instr, type_instr[format], 0)];
        int nbr_rgstr = nbre_rgstr[format];
        char registre[nbr_rgstr][10];
        recup_arg(nbr_rgstr ,line,registre);
        switch (format)
        {
            case 0:
                if(strcmp(cons,"sub")==0) L.opcode += (32<<25);
                for(int i = 0;i<3;i++){L.registres[i]= normalisation_rgstr(registre[i]);} break;
            case 1:
                if(strcmp(cons,"addi")==0) L.opcode += 16;
                else L.opcode +=(3<<12);
                for(int i = 0;i<2;i++){L.registres[i]= normalisation_rgstr(registre[i]);}
                L.registres[2] = atol(registre[2]);
                break;
            case 2:
                L.registres[0] = atol(registre[0]);
                L.registres[1] = normalisation_rgstr(registre[1]) ;
                L.registres[2] = normalisation_rgstr(registre[2]) ;
                L.registres[3] = atol(registre[3]);
                break;
            case 3:
                if(strcmp(cons,"bne")==0) L.opcode += (1<<12);
                else if (strcmp(cons,"blt")==0) L.opcode+=(4<<12);
                else if (strcmp(cons,"bge")==0) L.opcode+=(5<<12);
                L.registres[1] = normalisation_rgstr(registre[1]) ;
                L.registres[2] = normalisation_rgstr(registre[2]) ;
                // rajouter les immédiats de ses morts
                break;
            case 4:  // pareil
            break;
            default: printf("ERROR\n");break;
        }
        code_assemble = assemble(L);
    }
    free(cons); // libération de mémoire
    return code_assemble;
}
