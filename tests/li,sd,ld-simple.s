li x10,4
ld  x4, 4(x0) #commentaire
sd  t0, 3(x10)
ld  t1, 6(x10)

# EXPECTED
# x2: 16384
# x5: 12
# x6: 24
