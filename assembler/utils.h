char *normalisation(char *line); // permet d'enlever les virgules
char *rcp_instr(char *line,char *cons); // récupération de l'instruction
char *identification(char *line); // identification de l'instruction
void recup_2_arg(char *line, char *rd, char *imm); // recupere deux arguments
void recup_3_arg(char *line, char *rd, char *rs1,char *rs2); // récupère trois arguments
void trtmt_rgstr(char *registre); // permet de traiter les deux noms de chaque registre


// ces procédure reçoivent une ligne de code correpondant à la bonne procédure ( exemple : "add" sera traité par e_add)
// procédure nécessitant trois registres
void e_add(char *line);
void e_sub(char *line);
void e_addi(char *line);
void e_beq(char *line);
void e_bne(char *line);
void e_blt(char *line);
void e_bge(char *line);

// procédure nécessitant deux registres
void e_ld(char *line);
void e_sd(char *line);
void e_jal(char *line);
void e_li(char *line);
void e_mv(char *line);

// procédure nécessitant un registre ( un offset)
void e_j(char *line);