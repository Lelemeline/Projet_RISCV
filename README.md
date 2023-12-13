# Projet RISC-V CS351

Auteurs : THOMAS KILLIAN et TAVIER LÉA

## Rendu 1

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :
  - [x] Vérifié que `make test` se plaint sur le nombre d'instructions et pas
      sur l'existence des fichiers de sortie.
  - [x] Vu sur Chamilo que les soumissions se font avec `make tar`.


## Rendu 2
```Date de rendue: 15/12 23h59 (comme indiqué sur Chamillo)```
# commande pour test facile : make && ./riscv-assembler tests/add-simple.s test.hex && cat test.hex
(Une dizaine de lignes devrait suffire à chaque fois)

* Comment avez-vous choisi de programmer l'analyse de texte (dont la lecture
des opérandes entières) ? Comment identifiez-vous les noms de registres, des noms "jolis", des entiers ?

Dans le fichier main.c on lit le fichier ligne à ligne,et on normalise. Puis main.c appelle l'identification, ce qui nous permet donc d'avoir une ligne sans virgules et tout en minsucule. On se trouve donc avec une chaîne de caractères.
La lecture des registres en elle-même est simple : on lit la ligne, on "élimine" l'instruction et ensuite on lit chacun des caractères différent d'un espace qu'on copie dans un tableau de char ensuite. À l'issue de cette fonction, on a donc un tableau de tableau de char.
```C
// Exemple : on veut traiter addi a0  a1  3 (la ligne est normalisée)
// La fonction de lecture va renvoyer le tableau registre[3][10]
// registre[3][10] = {"a0","a1","3"};
```
Ensuite, on traite au cas par cas selon les formats. Une valeur immmédiate est "rangée" à sa place dans la structure adéquate,après avoir été convertie en int avec la fonction atol() (incluse dans <math.h>).
Les registres sont ensuite identifiés avec une fonction qui récupère la bonne chaîne de caractères et fonctionne en disjonction de cas :
  - si le registre est en "xY" elle récupère la chaîne de caractères tronquée du 'x' et renvoie atol(Y);
  - si le registre est un "joli" nom, elle récupère l'indice de cette chaîne dans le tableau de registre et le retourne.

* Avez-vous vu des motifs récurrents émerger ? Avez-vous "factorisé" ces motifs
pour éviter de les répéter ? Si non, serait-ce difficile ?

Au départ, la fonction d'identification reconnaissait chacune des 13 instructions à l'aide de "if/else if" puis traitait l'instruction comme demandé par le sujet (le code était écrit uniquement pour deux instructions : add et addi). Une fois ces deux instructions codées, les motifs récurrents étaient plus visibles : pour chaque instruction on récupère un nombre donné d'instructions et on récupère un opcode fixe selon le type de l'instruction puis chaque format a un traitement différent. Le if/else du début a donc été remplacé par un tableau contenant toutes les instructions et une fonction d'identification du format de l'instruction selon son index dans ledit tableau.
On reconnaît ensuite dans la fonction principale le format grâce à un switch, et on peut traiter l'instruction. Bien sûr, il reste encore du cas par cas, comme le traitement de l'opcode car au sein d'un même format, il y a des différences dans les opcodes (évidemment), mais ce code est factorisé.

* Comment avez-vous procédé pour écrire les tests ? Étes-vous confiant·e·s que
toutes les instructions gérées et tous les types d'arguments sont couverts ?

Les tests ont été écrits de manière à ce que s'ils sont mal interprétés par le programme, l'erreur soit facilement identifiable. Pour ce faire, les tests ont chacun des objectifs différents :
  - Deux tests ont été réalisés pour vérifier que les deux noms de registres sont reconnus.
  - Ensuite, dans les tests "simples" d'une instruction, des espaces, des majuscules ainsi que des commentaires (à la fin d'une ligne ou sur une ligne entière)      ont  été ajoutés pour vérifier que le programme récupère correctement les instructions.
  - Enfin, d'autres fichiers de test ont été créés pour tester le bon fonctionnement de chaque instruction.
Nous sommes assez confiants quant à la gestion de toutes les instructions et arguments demandés. Néanmoins, on attend l'élaboration de l'émulateur pour vérifier le bon fonctionnement de certaines instructions, certains tests ont quand même déjà été pensés pour pouvoir identifier certains problèmes.

* Quelle a été votre expérience avec l'utilisation et la compréhension de la
documentation fournie sur l'encodage des instructions RISC-V ?

Au début, la description semblait obscure, mais peu à peu, en avançant dans le projet, les points se sont éclairés et le projet ( tout du moins sa première partie) a été compris dans son ensemble.

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :
  - [x] Implémenté la traduction pour toutes les instructions de la documentation
  - [x] Pris en compte les cas particuliers comme les valeurs immédiates négatives et le bit manquant dans l'encodage de `jal`
  - [x] Écrit du code de gestion d'erreur pour que le programme ait une réaction propre si le code assembleur est invalide _(pas demandé par le sujet)_


## Rendu 3

Questions à remplir _avant_ de programmer l'émulateur (10 lignes sont conseillées à chaque fois pour bien y réfléchir) :

* Listez tous les éléments matériels auxquels vous pouvez penser dont l'émulateur doit reproduire le comportement, et déduisez-en une liste de toutes les tâches individuelles de l'émulateur.

[COMPLÉTER ICI]

* Quelle fonction de la bibliothèque standard pouvez-vous utiliser pour lire les valeurs listées dans le fichier `.hex` sans vous casser la tête ? (Indice : ces valeurs ont été écrites avec `fprintf()`.)

[COMPLÉTER ICI]

* Décrivez comment vous allez répartir les tâches de l'émulateur en différents fichiers, ou ne pas les répartir et tout faire dans le même fichier. Expliquez les avantages de votre choix.

[COMPLÉTER ICI]

Questions à remplir _après_ avoir programmé l'émulateur :

* Aviez-vous réussi à listé toutes les tâches dans la première question ? Rétrospectivement, y a-t-il des tâches dont vous aviez sous-estimé ou sur-estimé la complexité ?

[COMPLÉTER ICI]

* Avez-vous compris le fonctionnement de chaque instruction à partir de la
documentation fournie ? Si non, quels sont les points obscurs ?

[COMPLÉTER ICI]

* Quels exemples de programmes avez-vous choisi pour tester le calcul ? Les
comparaisons et sauts ? La mémoire ?

[COMPLÉTER ICI]

* Reste-t-il des bugs que vous avez découverts et pas corrigés ?

[COMPLÉTER ICI]

* D'autres remarques sur votre programme ?

[COMPLÉTER ICI]

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :**
  - [ ] Implémenté l'émulation de toutes les instructions gérées par le rendu 2.
  - [ ] Implémenté l'émulation de toutes les instructions.
  - [ ] Tous vos tests qui passent.
  - [ ] Vérifié que vous tests couvrent toutes les instructions émulées.
  - [ ] Testé les cas particuliers : valeurs négatives, overflows...
  - [ ] Testé les cas d'erreur : division par zéro, sauts invalides... _(pas demandé par le sujet)_
  - [ ] Un port fonctionnel de DOOM pour votre émulateur.

* Des retours sur le projet en général ?

[COMPLÉTER ICI]
#Projet_MIPS
# Projet_MIPS
# Projet_MIPS
# Projet_MIPS
# Projet_MIPS
# Projet_MIPS
