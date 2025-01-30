#ifndef ETUDIANT_H
#define ETUDIANT_H

#define LIGNES 7
#define COLONNES 15

typedef struct e {
    int tour;       // Tour où l'ennemi apparaît
    int ligne;      // Ligne de l'ennemi
    int colonne;    // Colonne de l'ennemi
    char type;      // (ex. :'Z')
    int actif;      // 1 si on veut qu'il apparaisse 0 si on veut le faire disparaitre genre s'il meurt
    int degats;
    int pointsDeVie;
    struct e *suivant; // Pointeur vers l'étudiant suivant
    struct e *precedent; // Pointeur vers l'étudiant précédent
} Etudiant;

Etudiant* ajouter_ennemi(Etudiant *tete, int tour, int ligne, int colonne, char type);
Etudiant* supprimer_ennemi(Etudiant *tete, Etudiant *ennemi);
void ajouter_ennemis_a_la_grille(char grille[LIGNES][COLONNES], Etudiant *ennemis);

#endif
