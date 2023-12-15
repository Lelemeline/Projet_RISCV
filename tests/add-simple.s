ADDI a1,                zero,  20
ADDI a2,zero, 22
ADD a0, a1 ,a2
addi x1,zero,2047
addi x2,zero, -2048
add x3,zero,x2
add x4,zero,x1

# EXPECTED
# sp: 16384
# a0: 42
# a1: 20
# a2: 22
# x1: 2047
# x2: -2048
# x3: 2047
# x4: -2048
