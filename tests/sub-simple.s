aDDi x11, x0, 20
ADDI a2, zero, 22
SUB a0, a2, a1
MV x14,x11
li x16,2047
li x17,-2047
sub x18,zero,x16
sub x19,zero,x17

# EXPECTED
# x2: 16384
# x10: 2
# x11: 20
# x12: 22
# x14: 20
# x16: 2047
# x17: -2047
# x18: -2047
# x19: 2047
