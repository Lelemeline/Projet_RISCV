# Projet RISC-V CS351

Auteurs : THOMAS KILLIAN et TAVIER LÉA

## Rendu 1

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :
  - [x] Vérifié que `make test` se plaint sur le nombre d'instructions et pas
      sur l'existence des fichiers de sortie.
  - [x] Vu sur Chamilo que les soumissions se font avec `make tar`.


## Rendu 2
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

Les tests ont été écrits de manière à détecter le maximum d'erreurs sur le code. Pour ce faire, les tests ont chacun des objectifs différents :
  - Deux tests ont été réalisés pour vérifier que les deux noms de registres sont reconnus.
  - Ensuite, dans les tests "simples" d'une instruction, des espaces, des majuscules ainsi que des commentaires (à la fin d'une ligne ou sur une ligne entière) ont  été ajoutés pour vérifier que le programme récupère correctement les instructions.
  - Enfin, d'autres fichiers de test ont été créés pour tester le bon fonctionnement de chaque instruction peu importe les valeurs utilisées (test de valeurs négatives ou de grandes valeurs).

Nous sommes assez confiants quant à la gestion de toutes les instructions et arguments demandés.

* Quelle a été votre expérience avec l'utilisation et la compréhension de la
documentation fournie sur l'encodage des instructions RISC-V ?

Au début, la description semblait obscure, mais peu à peu, en avançant dans le projet, les points se sont éclairés et le projet ( tout du moins sa première partie) a été compris dans son ensemble.

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :
  - [x] Implémenté la traduction pour toutes les instructions de la documentation
  - [x] Pris en compte les cas particuliers comme les valeurs immédiates négatives et le bit manquant dans l'encodage de `jal`
  - [x] Écrit du code de gestion d'erreur pour que le programme ait une réaction propre si le code assembleur est invalide _(pas demandé par le sujet)_


## Rendu 3
```Date de rendu 19/01```

Questions à remplir _avant_ de programmer l'émulateur (10 lignes sont conseillées à chaque fois pour bien y réfléchir) :

* Listez tous les éléments matériels auxquels vous pouvez penser dont l'émulateur doit reproduire le comportement, et déduisez-en une liste de toutes les tâches individuelles de l'émulateur.

Dans notre cas, l'émulateur doit imiter le comportement d'un processeur 64 bits (CPU), de ces 33 registres (32 registres + PC) ainsi que de la mémoire principale (16 kio ) tout en gérant les accès en lecture/écriture sur celle-ci (lectures/écritures de 8 ou 4 octets en fonction de l'instruction).
Pour ce faire, l'émulateur devra :
  - Charger toutes les instructions du programme dans la mémoire.
  - Initialiser les registres aux bonnes valeurs (attention à sp).
  - Exécuter les instructions chargées en mémoire jusqu à l'arrêt.
      * Pour ce faire, il faudra correctement utiliser le registre PC qu'on incrémentera correctement à chaque lecture d'instruction.
  - Afficher les valeurs finales des registres dans un fichier .state.

L'émulateur doit reproduire le fonctionnement d'une pile 
* Quelle fonction de la bibliothèque standard pouvez-vous utiliser pour lire les valeurs listées dans le fichier `.hex` sans vous casser la tête ? (Indice : ces valeurs ont été écrites avec `fprintf()`.)

On peut utiliser la fonction "fscanf()" de la bibliothèque standard qui nous permet d'éviter de convertir manuellement les valeurs hexadécimales du fichier ".hex". En effet, il suffit d'utiliser les bons formats ("%08x") pour pouvoir convertir nos valeurs hexadécimales en entier non signé plutôt que de coder le protocole nous-même.

* Décrivez comment vous allez répartir les tâches de l'émulateur en différents fichiers, ou ne pas les répartir et tout faire dans le même fichier. Expliquez les avantages de votre choix.

Pour des problèmes de lisibilité du code, nous préférerons répartir les tâches de l'émulateur en trois fichiers :
  - Le premier fichier qui comportera les différentes fonctions nécessaires au fonctionnement de l'émulateur (sois les fonctions nécessaires pour l'initialisation, la lecture, le décodage et l'exécution.)
  - Le deuxième fichier qui comportera notre main : il effectua les tâches nécessaires proprement et dans l'ordre grâce au premier fichier (Initialisation puis pour chaque instruction : lecture-décodage-exécution)
  - Le troisième fichier qui sert à déclarer les différentes fonctions, structures ...

Questions à remplir _après_ avoir programmé l'émulateur :

* Aviez-vous réussi à listé toutes les tâches dans la première question ? Rétrospectivement, y a-t-il des tâches dont vous aviez sous-estimé ou sur-estimé la complexité ?

Oui, les tâches principales ont été citées même si la complexité de leur implémentation n'était pas forcément apparente. En effet, le décodage peut nécessiter beaucoup plus d'étapes qu'on pourrait le penser et est très souvent source de petites erreurs pas toujours facile à trouver. À l'inverse, l'exécution qui pourrait paraître compliquée au premier abord l'est bien moins dès lors que le code est claire et bien structuré (structure correctement mise à jour pour stocker les différentes valeurs identifiées durant le décodage...).

* Avez-vous compris le fonctionnement de chaque instruction à partir de la
documentation fournie ? Si non, quels sont les points obscurs ?

Oui, la documentation fournie est très claire. De plus, les cours de CE 313 donnés au même moment permette d'accélérer et de facilité la compréhension des toutes ces instructions.  

* Quels exemples de programmes avez-vous choisi pour tester le calcul ? Les
comparaisons et sauts ? La mémoire ?

[COMPLÉTER ICI]

* Reste-t-il des bugs que vous avez découverts et pas corrigés ?

[COMPLÉTER ICI]

* D'autres remarques sur votre programme ?

[COMPLÉTER ICI]

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :**
  - [x] Implémenté l'émulation de toutes les instructions gérées par le rendu 2.
  - [x] Implémenté l'émulation de toutes les instructions.
  - [ ] Tous vos tests qui passent.
  - [x] Vérifié que vous tests couvrent toutes les instructions émulées.
  - [x] Testé les cas particuliers : valeurs négatives, overflows...
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
