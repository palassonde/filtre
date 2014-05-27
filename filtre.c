//NOM et Prénom : LASSONDE Pierre-Alexandre
//Code permanent : LASP16128901

//NOM et Prénom : BAUMONT Florian
//Code permanent : BAUF12059008

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "affichage.h"

int main(int argc, char *argv[])
{
    // VERIFICATION DES PARAMÈTRES
    if (argc < 2)
    {
        signaler_erreur(OPTION_ERREUR);
        exit(1);
    }

    // PROCESSUS
    int nbre_fichier = get_nbre_fichier(argv, 2, argc);
    struct tab2D *vecteurMatrice = malloc(nbre_fichier * sizeof(struct tab2D));
    
    for (int i = 0; i < nbre_fichier; ++i)
    {
        vecteurMatrice[i] = charger(argv[i+2]);
    }
    
    struct tab2D matrice_fusion = fusionMatrice(vecteurMatrice, nbre_fichier, argv[1][1]);
    struct tab2D matrice_final = {0,0,NULL};
    int *controlL = control(argv, matrice_fusion.lignes, 'L');
    int *controlC = control(argv, matrice_fusion.colonnes, 'C');
    matrice_final = filter(matrice_fusion, controlC, controlL);
    affiche_Tab2D(matrice_final);
    
    return 0;
} 




