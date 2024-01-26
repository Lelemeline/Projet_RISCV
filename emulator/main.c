#include <stdio.h>
#include "executer.h"


int main(int argc, char **argv)
{
    /* ./riscv-emulator <HEX INPUT> <EMULATION OUTPUT> */
    if(argc != 3) {
        printf("Usage: ./riscv-emulator <HEX INPUT> <EMULATION OUTPUT>\n");
        printf("error: invalid command\n");
        return 1;
    }

    char *hex_input_file = argv[1];
    char *emu_output_file = argv[2];

    /* déclaration et ouverture du fichier d’entrée en mode lecture et du fichier de
    sortie en mode écriture*/

    FILE *fe ; // fe = fichier d'entrée
    FILE *fs ; // fs = fichier de sortie
    fe = fopen(hex_input_file,"r");
    fs = fopen(emu_output_file,"w+");

    /* déclaration et initialisation de variables*/
    uint32_t reg[33]; // 32 registres + PC
    memset(reg,0,sizeof(reg)) ; // on initialise les registres et PC à 0
    reg[2] = 16384 ;

    /*programme*/
    // initialisation : lecture et chargement des instructions dans la mémoire
    int i = 0;
    while(fscanf(fe,"%08x ",&memoire[i])!=EOF){ // lit le fichier ligne à ligne (-1<=> fin de fichier)
        i++;
    }
    //lecture(memoire);
    // boucle lecture-décodage-exécution
    //lecture à l'adresse PC d'une instruction. Par convention, on sort de cette boucle si reg[PC]==0
    while(memoire[reg[32]]!=0) {
        Instruction D;
        D.instr = malloc(5*sizeof(char));
        init_struct(&D);
        decode(memoire[reg[32]],&D);
        executer(D,reg);
        //printf("PC = %i\n",reg[32]);
    }
    //printf("sortie de while\n");
    ecriture_registre(reg,fs); // écriture des registres dans le fichier .state
    //printf("écriture registre\n");
    /*fermeture des fichiers d'entrée et de sortie*/
    fclose(fe);
    fclose(fs);

    return 0;
}
