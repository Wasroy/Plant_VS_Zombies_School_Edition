#ifndef TOURELLE_H
#define TOURELLE_H

#define LIGNES 7
#define COLONNES 15

typedef struct tourtour{ // !!! on ne pourra pas la placer si un etudiant est sur la case
    int ligne;  // Ligne de la tourelle
    int colonne; //colonne de la tourelle
    int portee; // Portée de la tourelle
    int vie; //plutot explicit
    struct tourtour *suivant; // Pointeur vers la tourelle suivante

} Tourelle;
Tourelle* ajouter_tourelle(Tourelle *tete, int ligne, int colonne, int portee);
void attaquer_ennemis(char grille[LIGNES][COLONNES], Tourelle *tourelles, Etudiant *ennemis);
Tourelle* supprimer_tourelle(Tourelle *tete, int ligne, int colonne);

#endif
