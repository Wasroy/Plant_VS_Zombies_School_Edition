#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#include "../headers/jeu_william.h"
#include "../headers/etudiant.h"
#include "../headers/affichage.h"
#include "../headers/tourelles.h"

#define LIGNES 7
#define COLONNES 15
#define MAX_VAGUES 100

int fichier_existe(const char *nom_fichier) {
    FILE *fp = fopen(nom_fichier, "r");
    if (fp) {
        fclose(fp);
        return 1; // Le fichier existe
    }
    return 0; // Le fichier n'existe pas
}


int verifier_fin(char grille[LIGNES][COLONNES]) {
    for (int i = 0; i < LIGNES; i++) {
        if (grille[i][0]>='A' && grille[i][0]<='Z' && grille[i][0]!='T') {
            return -1; // Un étudiant a atteint la base
        }
    }
    // Maintenant, on va vérifier qu'il n'y a plus d'ennemis dans le jeu 
    int p=0;
    for(int i = 0; i<LIGNES; i++){
        for(int j = 0; j < COLONNES; j++){
            if (grille[i][j]=='Z' && grille[i][j]=='A' && grille[i][j]=='V' && grille[i][j]=='M' && grille[i][j]=='S')
                p=1;
        }
    }
    if(p==0)
        return 1; //Il n'y a plus d'ennemis dans le jeu 
    return 0;

}

Etudiant* charger_partie(const char *fichier, int *cagnotte) {
    FILE *fp = fopen(fichier, "r");

    if (fp == NULL) {
        perror("PROBLEME pour ouvrir le fichier");
        return NULL;
    }

    // Lecture de la cagnotte
    if (fscanf(fp, "%d", cagnotte) != 1) {
        fprintf(stderr, "ATTENTION !!! le fichier n'est pas bien organisé : il n'y a pas de cagnotte à la première ligne\n");
        fclose(fp);
        return NULL;
    }

    Etudiant *tete = NULL;
    int tour; 
    int ligne;
    char type;

    while (fscanf(fp, "%d %d %c", &tour, &ligne, &type) == 3) {
        tete = ajouter_ennemi(tete, tour, ligne, COLONNES, type);
    }

 
    fclose(fp);
    return tete;
}

void sauvegarder_partie(const char *fichier, int tour, int cagnotte, Tourelle *tourelles, Etudiant *ennemis) {
    FILE *fp = fopen(fichier, "w");
    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sauvegarde");
        return;
    }

    fprintf(fp, "%d %d\n", tour, cagnotte);

    Tourelle *t_courant = tourelles;
    while (t_courant != NULL) {
        fprintf(fp, "%c %d %d %d\n", t_courant->type, t_courant->ligne, t_courant->colonne);
        t_courant = t_courant->suivant;
    }

    Etudiant *e_courant = ennemis;

    while (e_courant != NULL) {
        fprintf(fp, "E %d %d %d %c %d\n", e_courant->tour, e_courant->ligne, e_courant->colonne, e_courant->type, e_courant->actif);
        e_courant = e_courant->suivant;
    }

    fclose(fp);
    printf("\n\033[32mPartie sauvegardée avec succès !\033[0m\n");
}

void charger_sauvegarde(const char *fichier, int *tour, int *cagnotte, Tourelle **tourelles, Etudiant **ennemis) {
    FILE *fp = fopen(fichier, "r");
    if (fp == NULL) {
        perror("Aucune sauvegarde trouvée, démarrage d'une nouvelle partie.");
        return;
    }

    if (fscanf(fp, "%d %d", tour, cagnotte) != 2) {
        fprintf(stderr, "Erreur : format de sauvegarde invalide.\n");
        fclose(fp);
        return;
    }

    *tourelles = NULL;
    *ennemis = NULL;

    char type;
    while (fscanf(fp, " %c", &type) == 1) {
        if (type == 'T' || type=='L' || type=='P') {
            int ligne, colonne, portee;
            if (fscanf(fp, "%d %d", &ligne, &colonne) == 2) {
                *tourelles = ajouter_tourelle(*tourelles, ligne, colonne, type);
            }

        } 

        else if (type == 'E') {
            int t, l, c, actif;
            char e_type;
            if (fscanf(fp, "%d %d %d %c %d", &t, &l, &c, &e_type, &actif) == 5) { // en gros on verif si la ligne possède bien toutes les infos necessaire grace au ==
                Etudiant *nouvel_ennemi = ajouter_ennemi(*ennemis, t, l, c, e_type);
                nouvel_ennemi->actif = actif;
                *ennemis = nouvel_ennemi;
            }
        }
    }

    fclose(fp);
    printf("\n\033[32mSauvegarde chargée avec succès !\033[0m\n");
}
