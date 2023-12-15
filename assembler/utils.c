#include "utils.h"

// déclaration des variables globales
char instruction[13][5] = {"add","sub","addi","ld","sd","beq","bne","blt","bge","jal"} ;
char registre[32][5] = {"zero","ra","sp","gp","tp","t0","t1","t2","s0","s1","a0","a1","a2","a3","a4","a5","a6","a7","s2","s3","s4","s5","s6","s7","s8","s9","s10","s11","t3","t4","t5","t6"} ;
char type_instr[5] = {'R','I','S','B','J'};
int  decalage[5][4] = {{7,15,20},{7,15,20},{7,15,20,25},{7,15,20,25},{7,12}};
int  nbre_rgstr[5] = {3,3,4,4,2};
uint32_t opcode[5] = {51,3,12323,99,111};

/// @brief remplace virgule par espace; les lignes vides et commentaires; change toutes les maj en min
/// @param line la ligne d'instruction complète
/// @return line - la ligne d'instruction normalisée
char *normalisation(char *line){
    int i=0;
    if (line[0]=='#' || line[0]=='\n'){ // ici on détecte que le premier char de la ligne est un # ou '\0' (<=> ligne vide)
        line[0]='\0'; // on remplace alors par une ligne vide
        return line;
    }
    while (line[i]!='\0'){ //
        if (line[i]==',') line[i]=' ';
        if(isalpha(line[i]) && isupper(line[i])) line[i] += 32;
        if(line[i]=='#') line[i] = '\0';
        i++;
    }
    return line;
}
//-----------------------------------------------//
// dans les fonctions suivantes, on considère que la ligne est conforme, à savoir pas de virgules ni de majuscules..//


/// @brief l'instruction est contenue du premier caractère de la ligne à l'espace suivant : c'est cette séquence de caractères qui est copiée dans le pointeur vers char cons.
/// @param line
/// @param cons
void rcp_instr(char *line, char *cons) {
    while(*line == ' '){
        line++;
    }
    while (*line != ' ') { //
        *cons++ = *line++;
    }
    *cons++ = '\0';
}
/// @brief concatène deux chaînes de caractères st1 et st2 dans la chaîne de caractère line
/// @param line
/// @param st1
/// @param st2
void concatener(char *line, const char *st1, const char *st2) {
    while ((*st1 != '\0')) {*line++ = *st1++;}
    while ((*st2 != '\0')) {*line++ = *st2++;}
    *line = '\0';
}

/// @brief retourne l'index de instr dans le tableau tab (fonction récursive)
/// @param tab
/// @param instr
/// @param index
/// @return
int find_index_char(char *tab, char instr, int index) {
    if (*tab == instr) return index;
    if (*tab == '\0') return -1;
    return find_index_char(tab + 1, instr, index + 1);
}
/// @brief retourne l'index du pointeur vers char instr dans le tableau de string tab
/// @param tab
/// @param instr
/// @return
int find_index_string(char tab[32][5], char *instr) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(tab[i], instr) == 0) {
            return i;
        }
    }
    return -2;
}
/// @brief est utilisé pour déterminer le format de l'instruction : prend l'indice de l'instruction dans le tableau instruction et renvoie le format correspondant (l'index correspondant dans la var global type-instr)
/// @param x
/// @return int
int find_type(int x){
     if(0<=x && x<2) return 0 ;
     if (2<=x && x<4) return 1;
     if (x==4) return 2;
     if (5<=x && x<9) return 3;
     if (x==9) return 4;
     return -1;
}
/// @brief Il existe deux types de registre : xX (dans ce cas, on récupère X-un int) et ceux avec des noms. Rangés dans un tableau "registre" à la place correspondant à l'index du registre.
/// @param tab
/// @return
int normalisation_rgstr(char *tab) {
    if (tab[0] == 'x') return atoi(tab+1);
    else return find_index_string(registre, tab);
}
/// @brief on prend la ligne d'instruction complète, on passe l'instruction ("mv","addi"...) et un espace, puis on récupère les arguments nécessaires (jamais plus de 3), qu'on copie dans le tableau tab.
/// @param a
/// @param line
/// @param tab
void recup_arg(int a, char *line,char tab[2][10]) {
    while(*line==' '){ // évite la casse (si la ligne commence par un espace par exemple)
        line++;
    }
    while (*line != ' ') { // on passe le char cons (l'instruction)
        line++;
    }
    while(*line==' '){ // on évite la casse, on ne sait pas combien l'utilisateur a rajouté d'espaces
        line++;
    }
    for (int i = 0; i < a; i++) {
        char *registre = malloc(10);
        int j = 0;
        while (*line != ' ' && *line != '\0' && *line!= '\n'&& *line !='(' && *line!=')') {
            registre[j++] = *line++;
        }
        registre[j] = '\0';
        strcpy(tab[i],registre);
        free(registre);
        while (*line == ' ') {
            line++;
        }
        if(*line == '('){
            line++;
        }
    }
}

/// @brief ajoute à l'a.opcode chacun des a.registres décalé de a.décalages
/// @param a
/// @return uint32_t le code assemblé
uint32_t assemble(Instruction a){
     uint32_t code = a.opcode;
     int j = nbre_rgstr[a.format];
     for(int i =0; i<j ; i++){
          code += (a.registres[i]<<a.decalages[i]);
     }
     return code;
}
/// @brief fonction d'affichage de la structure : utilisée pour le déboggage
/// @param a
void affichage_instr( Instruction a){
    printf("----------------------\n");
    printf("Format: %i\n",a.format);
    printf("opcode :%i\n",a.opcode);
    for (int i=0;i<nbre_rgstr[a.format];i++){
        printf("registre %i : %i\n",i,a.registres[i]);
    }
    for (int i = 0; i <4; i++)
    {
        printf("décalage %i : %i\n",i,a.decalages[i]);
    }
    printf("----------------------\n");

}
/// @brief identifie l'instruction puis disjonction de cas : si c'est une pseudo instruction, on la reconnaît ainsi que ses registres,
/// et on renvoie l'identification de l'instruction de base correspondante (déjà normalisée donc).
/// dans le cas où c'est une des dix instructions de base, on identifie le format et on "remplit" la structure qui correspond.
/// Une fois que la structure est complète, on assemble l'instruction.
/// @param line
/// @return
uint32_t identification(char *line){
    char *cons = malloc(strlen (line)+1); // allocation de mémoire dynamique
    rcp_instr(line,cons);
    uint32_t code_assemble;
    if (strcmp(cons,"j")==0){
        char offset[1][10] ;
        recup_arg(1,line,offset);
        char *ist = malloc(sizeof(line));
        concatener(ist,"jal x0 ",offset[0]);
        return identification(ist);
    }
    else if (strcmp(cons,"li")==0){
        char  rgst[2][10];
        recup_arg(2,line,rgst);
        char *ist = malloc(2*sizeof(line));
        concatener(ist,"addi ",rgst[0]);
        concatener(ist,ist," zero ");
        concatener(ist,ist,rgst[1]);
        return identification(ist);
    }
    else if (strcmp(cons,"mv")==0){
        char rgst[2][10];
        recup_arg(2,line,rgst);
        char *ist = malloc(sizeof(line));
        concatener(ist,"addi ",rgst[0]);
        concatener(ist,ist,"  ");
        concatener(ist,ist,rgst[1]);
        concatener(ist,ist," 0");
        return identification(ist);
    }
    else{
        Instruction L ;
        L.format = find_type(find_index_string(instruction,cons)); // trouve l'index de l'instruction dans le tableau "instruction" et renvoie l'index du format correspondant
        memcpy(L.decalages, decalage[find_index_char(type_instr, type_instr[L.format], 0)], sizeof(L.decalages));
        L.opcode=opcode[find_index_char(type_instr, type_instr[L.format], 0)];
        int nbr_rgstr = nbre_rgstr[L.format];
        char registre[nbr_rgstr][10];
        recup_arg(nbr_rgstr ,line,registre);
        switch (L.format)
        {
            case 0: // R-type
                if(strcmp(cons,"sub")==0) L.opcode += (32<<25);
                for(int i = 0;i<3;i++){L.registres[i]= normalisation_rgstr(registre[i]);}
                break;
            case 1: // I-type
                if(strcmp(cons,"addi")==0) {
                    L.opcode += 16;
                    for(int i = 0;i<2;i++){L.registres[i]= normalisation_rgstr(registre[i]);
                    L.registres[2] = atol(registre[2]);
                    }
                }
                else {
                    L.opcode +=(3<<12);
                    L.registres[0] = normalisation_rgstr(registre[0]);
                    L.registres[1] = normalisation_rgstr(registre[2]);
                    L.registres[2] = atol(registre[1]);
                    }
                break;
            case 2: // S-type
                L.registres[0] = (atol(registre[1]) & 31) ;
                L.registres[1] = normalisation_rgstr(registre[2]) ;
                L.registres[2] = normalisation_rgstr(registre[0]) ;
                L.registres[3] = (atol(registre[1]) & 4066)>>5 ;
                break;
            case 3: // B-type
                if(strcmp(cons,"bne")==0) L.opcode += (1<<12);
                else if (strcmp(cons,"blt")==0) L.opcode+=(4<<12);
                else if (strcmp(cons,"bge")==0) L.opcode+=(5<<12);
                L.registres[0] = (atol(registre[2]) & 30) + ((atol(registre[2]) & 2048)>>11);
                L.registres[1] = normalisation_rgstr(registre[0]) ;
                L.registres[2] = normalisation_rgstr(registre[1]) ;
                L.registres[3] = ((atol(registre[2]) & 4096)>>1) +((atol(registre[2]) & 2018)>>5);
                break;
            case 4: // J-type
                L.registres[0] = normalisation_rgstr(registre[0]) ;
                uint32_t reg = atol(registre[1]);
                L.registres[1] = ((reg & 1048576)>>1) + ((reg & 2046)<<8 ) + ((reg & 2048)>>3) + ((reg & 1044480)>>12);
                break;
            default: printf("ERROR\n");break;
        }
        code_assemble = assemble(L);
    }
    free(cons); // libération de mémoire
    return code_assemble;
}