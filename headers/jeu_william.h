
#ifndef JEU_WILLIAM_H
#define JEU_WILLIAM_H

#include "../headers/tourelles.h"

#define LIGNES 7
#define COLONNES 15

typedef struct {
    int ligne;    // Ligne où les ennemis apparaissent
    int colonne;  // Position de la vague sur la grille
    char type;
    int tour;
    int actif;
    
} Vague;


int verifier_fin(char grille[LIGNES][COLONNES]);
Etudiant* charger_partie(const char *fichier, int *cagnotte);
void charger_sauvegarde(const char *fichier, int *tour, int *cagnotte, Tourelle **tourelles, Etudiant **ennemis);
void sauvegarder_partie(const char *fichier, int tour, int cagnotte, Tourelle *tourelles, Etudiant *ennemis);

#endif
