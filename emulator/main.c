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
    // initialisation
    int i = 0;
    while(fscanf(fe,"%08x ",&memoire[i])!=EOF){ // lit le fichier ligne à ligne (-1<=> fin de fichier)
        i++;
    }
    // boucle lecture-décodage-exécution
    int j=0;
    while(memoire[reg[32]]!=0) {
        Instruction D;
        D.instr = malloc(5*sizeof(char));
        decode(memoire[reg[32]],&D);
        executer(D,reg);
        j++;
    }

    ecriture_registre(reg,fs); // écriture des registres dans le fichier .state

    /*fermeture des fichiers d'entrée et de sortie*/
    fclose(fe);
    fclose(fs);

    return 0;
}
