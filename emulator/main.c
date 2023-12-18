#include <stdio.h>
#include "utils.h"

uint32_t memoire[16384] = {0};
uint32_t *sp = 16384 - 1 ;


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

    /* déclaration de variables*/

    char *buffer = NULL; // buffer = contient chacune des lignes dans son ensemble
    size_t buf_size;
    int line_size;
    int i = 0;
    /*programme*/
    while(fscanf(fe,"%08hhx",buffer)!=0){ // lit le fichier ligne à ligne (-1<=> fin de fichier)
        /*programme*/
        printf("%s\n",buffer);
    }
    //  for (int i =0;i<10;i++){printf("%s\n",buffer);}
    /*libération de mémoire dynamique*/
    free(buffer);

    /*fermeture des fichiers d'entrée et de sortie*/
    fclose(fe);
    fclose(fs);

    return 0;
}
