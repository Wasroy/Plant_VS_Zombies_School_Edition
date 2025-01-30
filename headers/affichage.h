#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#define LIGNES 7
#define COLONNES 15

#include "jeu_william.h"
#include "../headers/tourelles.h"

void initialiser_grille(char grille[LIGNES][COLONNES], Tourelle *tete);
void ajouter_ennemis_a_la_grille(char grille[LIGNES][COLONNES], Etudiant *ennemis);

#endif
