# Filtre Matrix

## Compiler

$ make

## Description du programme

Transforme des matrices selon les parametres,

Le programme prend en paramètre un ou plusieurs fichiers contenant des elements à intégrer dans une matrice.

Exemple :

A B C
D
E F

Fera une matrice 3x3

Si il y a plusieurs matrices, ils seront collés l'une à l'autre de façon verticale ou horizontale

Finalement, il est possible d'effacer des lignes et des colonnes dans un domaine écrit en paramètre.

## Execution

./filtre [nom du ou des fichiers] [-V pour verticale -H pour horizontale] [-C pour effacer colonnes -L pour effacer lignes]
