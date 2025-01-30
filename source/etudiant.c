#include "stdlib.h"
#include "stdio.h"
#include "../headers/etudiant.h"


#define LIGNES 7
#define COLONNES 15


Etudiant* ajouter_ennemi(Etudiant *tete, int tour, int ligne, int colonne, char type) {

    Etudiant *nouvel_etudiant = malloc(sizeof(Etudiant));

    if (nouvel_etudiant == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    nouvel_etudiant->tour = tour;
    nouvel_etudiant->ligne = ligne;
    nouvel_etudiant->colonne = colonne;
    nouvel_etudiant->type = type;
    nouvel_etudiant->actif = 0; //si etudiant visible ou pas (1 si en vie 0 si éliminé (ou mort mais c'est un peu glauque un étudiant mort) )
    nouvel_etudiant->suivant = tete;
    nouvel_etudiant->precedent = NULL;
    //nouvel_etudiant->pointsDeVie = 10;

    if (tete != NULL) {
        tete->precedent = nouvel_etudiant;
    }

    switch (type) {
        case 'Z': // Ennemi basique
            nouvel_etudiant->pointsDeVie = 3;
            nouvel_etudiant->degats = 1;
            break;
        case 'A': // Ennemi rapide
            nouvel_etudiant->pointsDeVie = 2;
            nouvel_etudiant->degats = 1;
            //nouvel_etudiant->vitesse = 2;
            break;
        case 'S': // Ennemi solide
            nouvel_etudiant->pointsDeVie = 6;
            nouvel_etudiant->degats = 2;
            break;
        
        case 'C'://colosse
            nouvel_etudiant->pointsDeVie = 10;
            nouvel_etudiant->degats = 0;

        case 'V'://vif
            nouvel_etudiant->pointsDeVie = 1;
            nouvel_etudiant->degats = 5;
        
        default: //on met le meme que ennemis basique au cas ou on sait jamais tsais
            nouvel_etudiant->pointsDeVie = 3;
            nouvel_etudiant->degats = 1;
            break;
    }
    return nouvel_etudiant;
}


Etudiant* supprimer_ennemi(Etudiant *tete, Etudiant *ennemi) {

    if (ennemi->precedent != NULL) {
        ennemi->precedent->suivant = ennemi->suivant;
    } 
    
    else {
        tete = ennemi->suivant; // Si l'ennemi est en tête
    }

    if (ennemi->suivant != NULL) {
        ennemi->suivant->precedent = ennemi->precedent;
    }

    free(ennemi);
    printf("on a suppr l'ennemi t'a capté en brrr");
    return tete;
}

void ajouter_ennemis_a_la_grille(char grille[LIGNES][COLONNES], Etudiant *ennemis) {
    Etudiant *courant = ennemis;
    while (courant != NULL) {
        if (courant->actif && courant->colonne >= 0 && courant->colonne < COLONNES) {
            grille[courant->ligne - 1][courant->colonne] = courant->type;
        }
        courant = courant->suivant;
    }
}


