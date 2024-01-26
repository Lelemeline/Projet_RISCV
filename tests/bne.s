
li t4,0
li t3,10
li t5,36
addi t6,t6,1


add t2, t2, t6

addi t4, t4, 1
mv a0, t4
bne t4, t3, -12


li a0,0

#EXPECTED
#x2 : 16384
#x7 : 10
#x28 : 10
#x29 : 10
#x30 : 36
#x31 :1