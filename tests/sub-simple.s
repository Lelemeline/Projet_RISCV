aDDi x11, x0, 20
ADDI a2, zero, 22
SUB a0, a2, a1
MV x14,x11
li x16,2047
li x17,-2047
sub x18,zero,x16
sub x19,zero,x17

# EXPECTED
# sp: 16384
# a0: 2
# a1: 20
# a2: 22
# a4: 20
# x16: 2047
# x17: -2047
# x18: -2047
# x19: 2047
