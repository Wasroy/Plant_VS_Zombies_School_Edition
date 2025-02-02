#ifndef TOURELLE_H
#define TOURELLE_H

#define LIGNES 7
#define COLONNES 15

typedef struct tourtour{ // !!! on ne pourra pas la placer si un etudiant est sur la case
    char type;
    int ligne;  // Ligne de la tourelle
    int colonne; //colonne de la tourelle
    int portee; // Portée de la tourelle
    int vie; //plutot explicit
    int degats; //explicit
    struct tourtour *suivant; // Pointeur vers la tourelle suivante

} Tourelle;

Tourelle* supprimer_tourelle(Tourelle *tete, int ligne, int colonne);
Tourelle* ajouter_tourelle(Tourelle *tete, int ligne, int colonne, char type);
void attaquer_ennemis(char grille[LIGNES][COLONNES], Tourelle *tourelles, Etudiant *ennemis, int* cagnotte);
void attaquer_tourelles(Tourelle **tourelles, Etudiant *ennemis);


#endif
