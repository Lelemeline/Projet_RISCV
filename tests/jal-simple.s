

    jal x0, 8  
    addi x10, x0, 10  
    addi x11, x0, 20  
    li x16,1
    li x28,2

    jal x0,-12000 #pour tester des grosses valeurs
    jal x0,12000

# EXPECTED 
#x2: 16384
#x11:20
#x16:1
#x28:2
