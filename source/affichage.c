#include <stdio.h>
#include "../headers/affichage.h"
#include "../headers/jeu_william.h"
#include "../headers/tourelles.h"

#define LIGNES 7
#define COLONNES 15


void afficher_grille(char grille[LIGNES][COLONNES], int tour, int cagnotte, Etudiant *ennemis, Tourelle *tourelles) {
    printf("\n \033[33m Tour %d  | Cagnotte %d \033[0m \n", tour, cagnotte);

    // Affichage des numéros de colonnes
    printf("    "); 
    for (int j = 0; j < COLONNES; j++) {
        printf("%2d ", j + 1);
    }
    printf("\n");

    for (int i = 0; i < LIGNES; i++) {
        printf("%2d |", i + 1); // Affichage du numéro de ligne

        for (int j = 0; j < COLONNES; j++) {
            char type = grille[i][j]; //la case

            // Déterminer si une entité est un ennemi et récupérer ses points de vie
            int vie = -1;
            Etudiant *courant = ennemis;
            while (courant != NULL) {
                if (courant->ligne - 1 == i && courant->colonne == j && courant->actif) {
                    vie = courant->pointsDeVie;
                    break;
                }
                courant = courant->suivant;
            }

            // Affichage des ennemis avec couleur dynamique selon leurs PV
            if (vie > 0) {  
                char couleur[20];

                if (vie >= 7) {  
                    snprintf(couleur, sizeof(couleur), "\x1B[38;2;225;0;0m");  // Rouge foncé
                } 
                else if (vie >= 3) {  
                    snprintf(couleur, sizeof(couleur), "\x1B[38;2;255;100;0m");  // Rouge moyen
                } 
                else {  
                    snprintf(couleur, sizeof(couleur), "\x1B[38;2;255;165;0m");  // Orange
                }

                printf(" %s%-2c\033[0m", couleur, type);  // Appliquer la couleur dynamique
            }


            // Vérifier si c'est une tourelle pour appliquer l'effet orange si endommagée
            else if (type == 'T' || type=='L' || type=='P') {  

                Tourelle *courant_t = tourelles;

                while (courant_t != NULL) {
                    if (courant_t->ligne - 1 == i && courant_t->colonne == j) {
                        break;
                    }
                    courant_t = courant_t->suivant;
                }

                if (courant_t != NULL) {
                    if (courant_t->vie < 3) { // Si la tourelle a peu de vie, elle devient orange
                        printf(" \x1B[38;2;255;165;0m%-2c\033[0m", type);
                    } 
                    
                    else {
                        printf(" \033[34m%-2c\033[0m", type);  // Affichage des tourelles normales en bleu
                    }
                } 
                
                else {
                    printf(" %-2c", type); // Affichage normal
                }
            }

            else {  
                printf(" %-2c", type);  // cases vides
            }

        }

        printf("\n");

    }
}



void initialiser_grille(char grille[LIGNES][COLONNES], Tourelle *tete) {
    // Initialisation de la grille avec des points
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            grille[i][j] = '_'; // on met _ ça change des .
        }
    }

    // Vérification des tourelles avant placement
    Tourelle *courant = tete;

    while (courant != NULL) {

        // Vérification des bornes de la grille
        if (courant->ligne - 1 < 0 || courant->ligne - 1 >= LIGNES || courant->colonne < 0 || courant->colonne >= COLONNES) {
            printf("Tentative de placement hors grille");
        } 
        
        else {
            grille[courant->ligne - 1][courant->colonne] = courant->type; //on met la bonne lettre par rapport au type de l'ennemi
            //printf("debug typpe est : %c .",courant->type);
        }
        
        courant = courant->suivant;
    }
}
