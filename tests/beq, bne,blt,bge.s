
    # Initialisation des valeurs dans les registres
    li  x1, 10
    li  x2, 20
    li  x3, 10
    li  x4, 5

    # Comparaison pour tester les instructions de branchement
    beq x1, x3, label_eq       # Sautera à label_eq si x1 est égal à x3
    bne x2, x4, label_ne       # Sautera à label_ne si x2 n'est pas égal à x4
    blt x1, x2, label_lt       # Sautera à label_lt si x1 est inférieur à x2
    bge x4, zero, label_ge       # Sautera à label_ge si x4 est supérieur ou égal à zero

label_eq:
    # Code à exécuter si x1 est égal à x3
    li x5,5

label_ne:
    # Code à exécuter si x2 n'est pas égal à x4
    li x6,6
   

label_lt:
    # Code à exécuter si x1 est inférieur à x2
    li x7,7

label_ge:
    # Code à exécuter si x4 est supérieur ou égal à x3
    li x7,8

#EXPECTED
#



#DEBUGAGE EN FONCTION DES VALEURS DES REGISTRES
#
