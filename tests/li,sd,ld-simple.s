li  t0, 99              # Charge la valeur immédiate 99 dans t0
sd  t0, 0x1000          # Stocke la valeur de t0 à l'adresse 0x1000   
ld  t1, 0x1000          # Charge le contenu de la mémoire à l'adresse 0x1000 dans t1


# EXPECTED
# sp: 16384
# t0: 99
# t1: 99

