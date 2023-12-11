addi a1, zero,  20
addi a2,zero, 22
add a0, a1, a2
MV a0, a1
li t0, 12
li x1, 1
sd x0, 3(x10)
bne a1, a2, 32
jal x0, 66048
j 16

# EXPECTED
# sp: 16384
# a0: 42
# a1: 20
# a2: 22

addi a0, a1, 0
addi t0, zero, 12