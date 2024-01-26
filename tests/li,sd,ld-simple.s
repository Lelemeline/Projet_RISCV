 li a0 ,  0
  addi a0,a0,36
	addi t1, zero, -1
    sd s0, 0(a0)
    add a0,a0,t1
   ld a1, 0(a0)

# EXPECTED
# x2: 16384
# x6: -1
# a0: 35
