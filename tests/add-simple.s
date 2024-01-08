ADDI a1,                zero,  20
ADDI a2,zero, 22
ADD a0, a1 ,a2
addi t1,zero,2047
addi t2,zero, -2048
add t3,zero,t2
add t4,zero,t1

# EXPECTED
# x2: 16384
# x10: 42
# x11: 20
# x12: 22
# x6: 2047
# x7: -2048
# x28: -2048
# x29: 2047
