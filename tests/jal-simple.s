

    jal x0, 8  
    addi x10, x0, 10  
    addi x11, x0, 20  
    li x1,1
    li x2,2

    jal x0,-12000 #pour tester des grosses valeurs
    jal x0,12000

# EXPECTED 
#x11:20
#x1:1
#x2:2
