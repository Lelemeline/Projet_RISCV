li x11,1
li x12,2
j 12
#commentaire
#commentaire
add x3,x11,  x12
    add x4,zero,x11
li x5,5
li x6,6
li x7,7


#EXPECTED
#x2: 16384
#x11:1
#x12:2
#x5:5
#x6:6
#x7:7
