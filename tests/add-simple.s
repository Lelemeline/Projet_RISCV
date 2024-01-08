ADDI a1,                zero,  20
ADDI a2,zero, 22
ADD a0, a1 ,a2
addi t1,zero,2047
addi t2,zero, -2048
add t3,zero,t2
add t4,zero,t1

# EXPECTED
# sp: 16384
# a0: 42
# a1: 20
# a2: 22
# t1: 2047
# t2: -2048
# t3: 2047
# t4: -2048
