### README pas du tout officiel
(juste pour que je puisse réfléchir et bien mettre au propre mes idées.)

Il faut une structure qui sera allouée pour chaque nouvelle ligne ( malloc + free) et remplie dans la fonction de définition de l'instruction.
Il faut une fonction qui récupère le type de l'instruction, la recherche dans le tableau instruction,  et remplisse le champ decalage du tableau correspondant


## lecture et écriture

Il faut deux fonctions pour lire/écrire dans le fichier.
À la lecture, on prend en paramètre le nom du fichier à lire et on renvoie la ligne qu'on lit? Où le fichier complet?
À l'écriture, on prend en paramètre le nom du fichire dans lequel on écrit et ce qu'on veut écrire, et on ne renvoie rien.

    - [ ] char *read_file(char nomduFichier[])
    - [ ] void write_file(char nomduFichier[],*line)

## traitement ligne à ligne
    - [ ] normalisation
    - [ ] identification de l'intruction
    - [ ] type d'instruction
    - [ ] identification des registres
    - [ ] association de l'opcode
    - [ ] additions et shift

## gestion de l'erreur
    - [x] à la normalisation, si ligne vide => on n'imprime rien
    - [ ] on ne traite pas de majuscule
    - [ ] à trouver

/!\ dans l'identification d'abord identifier si c'est une pseudo instruction ou non.


int conversion(char *string){} --> int

int conversion(['4','5','\0']) -> 45