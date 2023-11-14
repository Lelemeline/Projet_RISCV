#include <stdio.h>

int main(int argc, char **argv)
{
    /* ./riscv-assembler <ASSEMBLER INPUT> <HEX OUTPUT> */
    if(argc != 3) {
        printf("usage: ./riscv-assembler <ASSEMBLER INPUT> <HEX OUTPUT>\n");
        return 1;
    }

    char *asm_input_file = argv[1];
    char *hex_output_file = argv[2];

    /* ouvre le fichier d’entrée en mode lecture et le fichier de
    sortie en mode écriture, puis les ferme à la fin du un programme. */
    FILE *fe ; // fe = fichier d'entrée
    FILE *fs ; // fs = fichier de sortie
    fe = fopen(asm_input_file,"r");
    fs = fopen(hex_output_file,"w");
    /*programme*/
    fclose(fe);
    fclose(fs);
    return 0;
}
