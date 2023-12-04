#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "utils.h"

int main(int argc, char **argv)
{
    /* ./riscv-assembler <ASSEMBLER INPUT> <HEX OUTPUT> */
    if(argc != 3) {
        printf("usage: ./riscv-assembler <ASSEMBLER INPUT> <HEX OUTPUT>\n");
        return 1;
    }

    char *asm_input_file = argv[1];
    char *hex_output_file = argv[2];

    /* déclaration et ouverture du fichier d’entrée en mode lecture et du fichier de
    sortie en mode écriture*/

    FILE *fe ; // fe = fichier d'entrée
    FILE *fs ; // fs = fichier de sortie
    fe = fopen(asm_input_file,"r");
    fs = fopen(hex_output_file,"w+");

    /* déclaration de variables*/

    char *buffer = NULL; // buffer = contient chacune des lignes dans son ensemble
    size_t buf_size;
    int line_size;

    /*programme*/

    while((line_size = getline(&buffer,&buf_size,fe))!=-1){ // lit le fichier ligne à ligne
        buffer = normalisation(buffer);
        if (buffer[0]!='\0'){
            //fprintf(fs,"%s",buffer);
            //printf("%s",buffer);
            fprintf(fs,"%x\n",identification(buffer));
        }

    }
    free(buffer);

    // pour l'instant on  1. normalise les lignes 2. on les identifie

    /*libération de mémoire dynamique*/


    /*fermeture des fichiers d'entrée et de sortie*/
    fclose(fe);
    fclose(fs);

    return 0;
}
