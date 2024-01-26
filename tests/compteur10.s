li t0, 0
li t1,10
beq t0, t1,16 
mv a0,t0
addi t0, t0, 1
j -12
li t3,1


#EXPECTED
#x2 : 16384
#x5 : 10
#x6 : 10
#x10 : 9
#x28 :1
