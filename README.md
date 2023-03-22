#takuzu - 11c

Projet réalisé par les étudiants : 
Arnaud Gomes
Yasmine Maabout
Justine Ruch

## Le jeu takuzu
On dispose d'une grille qu'il faut remplir de carrés noirs et blancs en respectent les règles suivantes :
    -il ne peut pas y avoir plus de 2 carrés de meme couleur à la suite
    -il ne doit pas y avoir plus de la mpotié des case d'une ligne ou colonne d'une meme couleur
Il est possible de rajouter deux règles facultatives : 
    -il ne peut y avoir deux lignes ou colonnes identiques
    -le jeu se replie sur lui-meme et ainsi les cases de deux extrémités se suivent

## game_text.c
Permet de jouer avec le jeu et les règles par défaut en utilisant la commande ./game_text dans le terminal.

##game_solve.c
Permet de chercher la ou les solutions d'un jeu chargé.

## game.c
Implémentation des fonctions pour utiliser un jeu

## game_aux.c
Implémentation des fonctions d'affichage et de définition du jeu par défaut.

## game_ext.c
Implémentation de la V2 avec les règles facultatives.
Ajout des fonction undo et redo.

## game_solve.c
Implémentation des fonctions load et save qui permettent de charger et de sauvgarder un jeu.
Ainsi que les fonctions solve et nb_solutions qui cherche une solution et le nombre de solution d'un jeu donné.
