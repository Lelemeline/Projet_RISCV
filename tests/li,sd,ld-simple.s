ld  x1, 4(x0) #commentaire dont on se fout
sd  t0, 3(t0)
ld  t1, 6(x0)

# EXPECTED
# sp: 16384
# t0: 99
# t1: 99
