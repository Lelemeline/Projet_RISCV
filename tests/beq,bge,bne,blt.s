
# Initialisation des valeurs dans les registres
li  x1, 10
li  x2, 20
li  x3, 10
li  x4, 5

# Comparaison pour tester les instructions de branchement
beq x1, x3, 8   # Sautera une instruction si x1 est égal à x3
addi x5, x0, 1  # instruction sautée si l'instruction si dessus est vrai
bne x2, x4, 8   # Sautera une instruction si x2 n'est pas égal à x4
addi x6, x0, 2  # sautée si bne est vrai
blt x1, x2, 8   # Sautera une instruction si x1 est inférieur à x2
addi x7, x0, 3  # sautée si blt est vrai
bge x3, x4, 8  # Sautera une instruction si x3 est supérieur ou égal à x4
addi x8, x0, 4  # sautée si bge est vrai

# test pour si les conditions pour les instructions ne sont pas vérifiés
# debeugage qui ne peut être fait qu'en ayant les valeurs des registres
beq x1, x2, 4
addi x9, x0, 1
bne x1, x3, 4
addi x10, x0, 2
blt x2, x1, -4004
addi x11, x0, 3
bge x4, x3, 4
addi x12, x0, 4


# EXPECTED
# x1 :10
# x2 :20
# x3 :10
# x4 :5
# x9 :1
# x10 :2
# x11 :3
# x12 :4