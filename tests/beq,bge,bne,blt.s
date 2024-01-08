
# Initialisation des valeurs dans les registres
li  x16, 10
li  x28, 20
li  x3, 10
li  x4, 5


# Comparaison pour tester les instructions de branchement
beq x16, x3, 8   # Sautera une instruction si x16 est égal à x3
addi x5, x0, 1  # instruction sautée si l'instruction si dessus est vrai
bne x28, x4, 8   # Sautera une instruction si x28 n'est pas égal à x4
addi x6, x0, 2  # sautée si bne est vrai
blt x16, x28, 8   # Sautera une instruction si x16 est inférieur à x28
addi x7, x0, 3  # sautée si blt est vrai
bge x3, x4, 8  # Sautera une instruction si x3 est supérieur ou égal à x4
addi x8, x0, 4  # sautée si bge est vrai

# test pour si les conditions pour les instructions ne sont pas vérifiés
# debeugage qui ne peut être fait qu'en ayant les valeurs des registres
beq x16, x28, 4
addi x9, x0, 1
bne x16, x3, 4
addi x10, x0, 2
blt x28, x16, 4
addi x11, x0, 3
bge x4, x3, 4
addi x12, x0, 4

# EXPECTED
# x2: 16384
# x16 :10
# x28 :20
# x3 :10
# x4 :5
# x9 :1
# x10 :2
# x11 :3
# x12 :4
