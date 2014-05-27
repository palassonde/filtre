//NOM et Prénom : LASSONDE Pierre-Alexandre
//Code permanent : LASP16128901

//NOM et Prénom : BAUMONT Florian
//Code permanent : BAUF12059008

#include <stdio.h>
#include "fonctions.h"
#include "affichage.h"
#include <stdlib.h>
#include <string.h>

int nbre_lignes_fichier(FILE *fp)
{
    int c;
    int nbLigne = 1;

    //trouve le nombre total de ligne dans le fichier
    do
    {
        c=fgetc(fp);
        if (c == '\n')
        {  
            nbLigne++;
        }
    }while (c != EOF);
    
    fclose(fp);
    return nbLigne;
}

int max_occurence(int * vecteur , int v)
{
    if (vecteur == NULL)
    {
        return 0;
    }
        
    int max = 0;

    // on trouve le nombre maximale d'occurence d'entier
    for (int i = 0; i < v; i++)
    {
        if (max < vecteur[i])
        {
            max = vecteur[i];
        }
    }
    return max;
}

struct tab2D charger(char * filename)
{
    FILE *fp = fopen(filename,"r");
    
    if (!fp)
    {
        signaler_erreur(OUVERTURE_FICHIER_ERREUR);
        exit(1);
    }
    struct tab2D matrice;
    int nbre_lignes_total = nbre_lignes_fichier(fp);
    int *vecteur = calloc(nbre_lignes_total, sizeof(int));
    fp = fopen(filename,"r");
    vecteur = creerVecteur(vecteur, fp);
    matrice.colonnes = max_occurence(vecteur, nbre_lignes_total);
	
    int cptLigne = 0;
	char elem[256];
    int cpt = 0;
    char *(*ptrtab2d)[matrice.colonnes] = NULL;

    for (int i = 0; i < nbre_lignes_total; ++i)
    {
		if (vecteur[i])
        {
            cptLigne++;
        }
    }
    
    matrice.lignes = cptLigne;
    
    ptrtab2d = malloc((matrice.lignes * matrice.colonnes) * (sizeof(char*)));
    
    int tab[cptLigne];

    for (int i = 0; i < nbre_lignes_total; ++i)
    {
        if (vecteur[i])
        {
            tab[cpt] = vecteur[i];
            cpt++;
        }
    }
    
    fp = fopen(filename,"r");

    for (int i = 0; i < matrice.lignes; ++i)
    {
        for (int j = 0; j < matrice.colonnes; ++j)
        {
            if (j < tab[i])
            {
                fscanf(fp, "%s", elem);
                ptrtab2d[i][j] = strcpy(malloc(sizeof(elem)),elem);
            }
            else
            {
                ptrtab2d[i][j] = "";
            }
        }
    }
    matrice.ptr = &(ptrtab2d[0][0]);
    return matrice;
}

int get_nbre_domaines(char  *const argv[], int pos)
{
    int cpt = 0;
    int i = 0;
    int flagL = 0;
    int flagC = 0;

    // Donne le nombre de paramètres dans la liste dépendamment de la position du paramètre
    while (argv[i] != NULL)
    {
        if (!strcmp(argv[i], "-L"))
        {
            if (flagL == 1)
            {
                signaler_erreur(OPTION_ERREUR);
                exit(1);
            }
            flagL = 1;
        }
        if (!strcmp(argv[i], "-C"))
        {
            if (flagC == 1)
            {
                signaler_erreur(OPTION_ERREUR);
                exit(1);
            }
            flagC = 1;
        }
        i++;
    }

    i = 1;
    while (argv[pos+i] != NULL)
    {
        if (strcmp(argv[pos+i], "-L") && strcmp(argv[pos+i], "-C"))
        {
            cpt++;
            i++;
        }
        else
        {
            return cpt;
        }
    }
    return cpt;
}

int check_domaine(char *domaine)
{
    char *ptr = domaine;
    int flagT = 0;
    int flagN = 0;

    //Vérifie que le domaine est bien indiqué
    while(*ptr != '\0')
    {
        if ((*ptr >= '0' && *ptr <= '9') || *ptr == '-')
        {
            if (*ptr >= '0' && *ptr <= '9')
            {
                flagN = 1;
            }
            if (*ptr == '-')
            {
                if (flagT)
                {
                    return 0;
                }
                flagT += 1;
            }
        }
        else
        {
            return 0;
        }
        ptr++;
    }
    if (flagN == 0)
    {
        return 0;
    }
    return 1;
}

int get_debut_fin_domaine(char * domaine, int max, int *debut, int *fin)
{
    int cpt = 0;
    int tailleDomaine = 0;
    int nbr;
    int i = 0;
    int flagNombre = 0;
    int flagT = 0;

    //Selon tous les figure possible de domaine, donne le début et la fin
    if (!check_domaine(domaine))
    {
        return 0;
    }

    while(domaine[i] != '\0')
    {
        tailleDomaine ++;
        if (domaine[i] == '-')
        {
            flagT = 1;
        }
        i++;
    }
    i = 0;

	// CAS OU IL N'Y A PAS DE TIRET
    if (flagT == 0)
    {
        while(domaine[i] != '\0')
        {
            if(flagNombre == 1)
            {
                nbr = nbr * 10 + (int)(domaine[i] - '0');
            }
            if (flagNombre == 0)
            {
                nbr = (int)(domaine[i] - '0');
                flagNombre = 1;
            }
            
            i++;
        }
        *debut = nbr;
        *fin = nbr;

        return 1;
    }
    i = 0;
 
    flagNombre = 0;

	// CAS OU LE TIRET EST AU DEBUT
    if (domaine[i] == '-')
    {
        *debut = 0;
        i++;
        while(domaine[i] != '\0')
        {
            if(flagNombre == 1)
            {
                nbr = nbr * 10 + (int)(domaine[i] - '0');
            }
            if (flagNombre == 0)
            {
                nbr = (int)(domaine[i] - '0');
                flagNombre = 1;
            }     
            i++;
        }
        *fin = nbr;

        return 1;
    }

    i = 0;
    flagNombre = 0;

	// CAS OU LE TIRET EST À LA FIN
    while(domaine[i] != '\0')
    {
        if (domaine[i] == '-' && cpt == tailleDomaine-1)
        {
            i = 0;
            while(domaine[i]!= '-')
            {
                if(flagNombre == 1)
                {
                    nbr = nbr * 10 + (int)(domaine[i] - '0');
                }
                if (flagNombre == 0)
                {
                    nbr = (int)(domaine[i] - '0');
                    flagNombre = 1;
                }  
                i++;
            }
            *debut = nbr;
            *fin = max;
            return 1;
        }
        i++;
        cpt++;
    }

    i = 0;
    flagNombre = 0;

    // CAS OU LE TIRET EST AU MILIEU
    while(domaine[i] != '\0')
    {
        if (domaine[i] == '-')
        {
            *debut = nbr;
            nbr = 0;
            flagNombre = 0;
            i++;
            while(domaine[i] != '\0')
            {
                if(flagNombre == 1)
                {
                    nbr = nbr * 10 + (int)(domaine[i] - '0');
                }
                else
                {
                    nbr = (int)(domaine[i] - '0');
                    flagNombre = 1;
                }
                    i++;
            }
            *fin = nbr;
            return 1;
        }
        if(flagNombre == 1)
        {
            nbr = nbr * 10 + (int)(domaine[i] - '0');
        }
        else
        {
            nbr = (int)(domaine[i] - '0');
            flagNombre = 1;
        }
        i++;
    }
    return 1;    
}

int seek_option(char *const argv[], char option)
{
    int i = 0;
    // Retourne la position de l'option C ou L
    while(argv[i] != NULL)
    {
        if (argv[i][1] == option)
        {
            return i;
        }
        i++;
    }
    return -1;
}

int * control(char *const argv[], int dim, char c)
{    
    int deb =0;
    int fn =0;
    int *debut = &deb;
    int *fin = &fn;
    int *vecteurC = calloc(dim, sizeof(int));
    int index = 0;
    index = seek_option(argv, c);

    // Crée le vecteur correspondant au lignes ou colonnes à effacer
    if (index == -1)
    {
        return vecteurC;
    }

    int nbreDomaines = 0;
    nbreDomaines = get_nbre_domaines(argv, index);

    for (int i = 0; i < nbreDomaines; i++)
    {
        if (get_debut_fin_domaine(argv[index + i + 1], dim, debut, fin))
        {
            for (int j = *debut; j <= *fin && j < dim ; j++)
            {
                vecteurC[j] = 1;
            }
        }
        else
        {
            signaler_erreur(2);
            exit(1);
        }
    }
    return vecteurC;
}

struct tab2D filter(struct tab2D matrice_fusion, int *controlC, int *controlL)
{
    int matrice2_nbre_lignes = 0;
    int matrice2_nbre_colonnes = 0;
    int cpt = 0;
    
    //Cree la nouvelle matrice en fonctions des lignes et/ou colonnes a effacer
    for (int i = 0; i < matrice_fusion.colonnes; i++)
    {
        if (!controlC[i])
        {
            matrice2_nbre_colonnes++;
        }
    }
    
    for (int i = 0; i < matrice_fusion.lignes; i++)
    {
        if (!controlL[i])
        {
            matrice2_nbre_lignes++;
        }
    }
    
    char * (*ptrtab2d)[matrice2_nbre_colonnes] = NULL;
    ptrtab2d = malloc((matrice2_nbre_lignes * matrice2_nbre_colonnes) * (sizeof(char*)));
    
    char * (*lignePtr)[matrice_fusion.colonnes] = NULL;
    lignePtr = (char * (*)[matrice_fusion.colonnes]) matrice_fusion.ptr;
    
    char **nouvemat = malloc((matrice2_nbre_colonnes * matrice2_nbre_lignes) * sizeof(char*));
    
    for (int i = 0; i < matrice_fusion.lignes; i++)
    {
        if (!controlL[i])
        {
            for (int j = 0; j < matrice_fusion.colonnes; j++)
            {
                if (!controlC[j])
                {
                    nouvemat[cpt] = lignePtr[i][j];
                    cpt++;
                }
            }
        }
    }
    cpt = 0;
    
    for (int i = 0; i < matrice2_nbre_lignes; ++i)
    {
        for (int j = 0; j < matrice2_nbre_colonnes; ++j)
        {
            ptrtab2d[i][j] = nouvemat[cpt];
            cpt++;
        }
    }
    
    struct tab2D matrice2 = {0,0,NULL};
    matrice2.ptr = &ptrtab2d[0][0];
    matrice2.lignes = matrice2_nbre_lignes;
    matrice2.colonnes = matrice2_nbre_colonnes;
    
    return matrice2;
}

struct tab2D fusionMatrice(struct tab2D *vecteurMatrice, int nbre_fichier, char option)
{
    int nbc = 0;
    int nbl = 0;
    int max = 0;
    int maxl = 0;
    
    if (option == 'V')
    {
        for (int i = 0; i < nbre_fichier; ++i) {
            
            nbl += vecteurMatrice[i].lignes;
            
            if (max < vecteurMatrice[i].colonnes)
            {
                max = vecteurMatrice[i].colonnes;
            }
        }
        nbc = max;
    }
    else if (option == 'H')
    {
        for (int i = 0; i < nbre_fichier; ++i) {
            
            nbc += vecteurMatrice[i].colonnes;
            
            if (maxl < vecteurMatrice[i].lignes)
            {
                maxl = vecteurMatrice[i].lignes;
            }
        }
        max = nbc;
        nbl = maxl;
    }
    else
    {
        signaler_erreur(OPTION_ERREUR);
        exit(1);
    }
    
    char *(*ptrtab2d)[max] = NULL;
    ptrtab2d = malloc((nbc * nbl) * (sizeof(char*)));
    int pos = 0;
    int cpt = 0;
    
    if (option == 'H')
    {
        for (int x = 0; x < nbre_fichier; ++x)
        {
            for (int i = 0; i < nbl; ++i)
            {
                for (int j = 0; j < vecteurMatrice[x].colonnes; ++j)
                {
                    if (i < vecteurMatrice[x].lignes)
                    {
                        ptrtab2d[i][j+pos] = vecteurMatrice[x].ptr[cpt];
                        cpt++;
                    }
                    else
                    {
                        ptrtab2d[i][j+pos] = "";
                    }
                    
                }
            }
            cpt = 0;
            pos += vecteurMatrice[x].colonnes;
        }
    }
    else if (option == 'V')
    {
        for (int x = 0; x < nbre_fichier; ++x)
        {
            for (int i = 0; i < nbl; ++i)
            {
                for (int j = 0; j < nbc; ++j)
                {
                    if (j < vecteurMatrice[x].colonnes)
                    {
                        ptrtab2d[i+pos][j] = vecteurMatrice[x].ptr[cpt];
                        cpt++;
                    }
                    else
                    {
                        ptrtab2d[i+pos][j] = "";
                    }
                    
                }
            }
            cpt = 0;
            pos += vecteurMatrice[x].lignes;
        }
    }
    
    struct tab2D matrice_fusion;
    matrice_fusion.colonnes = nbc;
    matrice_fusion.lignes = nbl;
    matrice_fusion.ptr = &ptrtab2d[0][0];
    
    return matrice_fusion;
}