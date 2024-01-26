li a0,0
li x6,6
jal x6, 8
ADDI x10, x0, 10
addi x11, x0, 20
li x16,1
li x28,2
sub x28,x28,x16
li x14, 0
jal x14,36
addi x16,x16,1
addi x16,x16,1
addi x16,x16,1
addi x16,x16,1
addi x16,x16,1
addi x16,x16,1
addi a6,x16,1
addi x16,x16,1
addi x6,x6,1
addi a0,a0, 1
# EXPECTED
# x2: 16384
# x6: 4
# x10 :1
# x11: 20
# x14 :10
# x16 : 1
# x28 :1
