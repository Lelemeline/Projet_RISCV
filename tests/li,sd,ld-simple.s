li x10,4
ld  x1, 4(x0) #commentaire
sd  t0, 3(x10)
ld  t1, 6(x10)

# EXPECTED
# sp: 16384
# t0: 12
# t1: 24
