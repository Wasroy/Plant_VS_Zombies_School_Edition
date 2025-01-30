#include "../headers/tourelles.h"
#include "../headers/etudiant.h"
#include "stdlib.h"
#include "stdio.h"

#include <windows.h>

#define LIGNES 7
#define COLONNES 15


Tourelle* ajouter_tourelle(Tourelle *tete, int ligne, int colonne, int portee) {
    Tourelle *nouvelle_tourelle = malloc(sizeof(Tourelle));
    if (nouvelle_tourelle == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    nouvelle_tourelle->ligne = ligne;
    nouvelle_tourelle->colonne = colonne;
    nouvelle_tourelle->portee = portee;
    nouvelle_tourelle->suivant = tete; // Ajoute en tête de liste
    nouvelle_tourelle->vie = 5;
    return nouvelle_tourelle;
}


void attaquer_ennemis(char grille[LIGNES][COLONNES], Tourelle *tourelles, Etudiant *ennemis) { //tourelles->>>>>etudiants
    Tourelle *courant_t = tourelles;

    while (courant_t != NULL) { 

        for (int c = 1; c <= courant_t->portee; c++) {
            
            int colonne_cible = courant_t->colonne + c;

            Etudiant *courant_e = ennemis;

            while (courant_e != NULL) { //on parcourt toute la liste chainée d'étudiant

                if (courant_e->actif && courant_e->ligne == courant_t->ligne && courant_e->colonne == colonne_cible) {

                    //printf("Tourelle [%d, %d] tire sur l'ennemi [%c] (ligne : %d, colonne : %d).\n", courant_t->ligne, courant_t->colonne+1, courant_e->type, courant_e->ligne, courant_e->colonne);

                    courant_e->pointsDeVie-=3;

                    if (courant_e->pointsDeVie<=0){
                        //printf("\x1B[38;2;255;0;0mEnnemi [%c] éliminé!\033[0m\n", courant_e->type);
                        courant_e->actif = 0; // Désactive l'ennemi 
                        //A FAIRE supprimer_enenemi(courant_e)
                        //A FAIRE rajouter de l'argent a la cagnotte
                        grille[courant_e->ligne - 1][courant_e->colonne] = '.'; // Efface l'ennemi de la grille

                    }
 
                    break;
                }

                courant_e = courant_e->suivant;
            }
        }
        courant_t = courant_t->suivant;
    }

}


void attaquer_tourelles(Tourelle **tourelles, Etudiant *ennemis) {
    Etudiant *courant_e = ennemis;

    while (courant_e != NULL) {
        if (courant_e->actif) {
            Tourelle *courant_t = *tourelles;

            while (courant_t != NULL) {
                if (courant_e->ligne == courant_t->ligne && courant_e->colonne == courant_t->colonne) {
                    printf("\x1B[38;2;255;0;0mL'ennemi [%c] attaque la tourelle en [%d, %d]!\033[0m\n",
                           courant_e->type, courant_t->ligne, courant_t->colonne);

                    courant_t->vie -= courant_e->degats; // Réduction en fonction des dégâts de l'ennemi

                    if (courant_t->vie <= 0) {
                        printf("\x1B[38;2;255;0;0mTourelle en [%d, %d] détruite!\033[0m\n",
                               courant_t->ligne, courant_t->colonne);

                        *tourelles = supprimer_tourelle(*tourelles, courant_t->ligne, courant_t->colonne);
                        break;
                    }
                }
                courant_t = courant_t->suivant;
            }
        }
        courant_e = courant_e->suivant;
    }
}





Tourelle* supprimer_tourelle(Tourelle *tete, int ligne, int colonne) {
    Tourelle *courant = tete;
    Tourelle *precedent = NULL;

    while (courant != NULL) {
        if (courant->ligne == ligne && courant->colonne == colonne) {
            printf("DEBUG : Suppression de la tourelle en [%d, %d]\n", ligne, colonne);
            if (precedent == NULL) {  
                Tourelle *temp = courant->suivant;
                free(courant);
                return temp;
            } else {
                precedent->suivant = courant->suivant;
                free(courant);
                return tete;
            }
        }

        precedent = courant;
        courant = courant->suivant;
    }

    printf("DEBUG : Aucune tourelle trouvée à [%d, %d]\n", ligne, colonne);
    return tete;
}

