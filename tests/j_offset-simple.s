li x1,1
li x2,2
j 12
#commentaire
#commentaire
add x3,x1,  x2
    add x4,zero,x1
li x5,5
li x6,6
li x7,7

j -80000
j 80000

#EXPECTED
#x1:1
#x2:2
#x5:5
#x6:6
#x7:7
