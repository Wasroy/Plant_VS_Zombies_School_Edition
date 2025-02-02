#include <stdio.h>
#include <windows.h> //modification de la bib 

#include "../headers/etudiant.h"
#include "etudiant.c"

#include "affichage.c"
#include "../headers/affichage.h"

#include "jeu_william.c"
#include "../headers/jeu_william.h"

#include "tourelles.c"
#include "../headers/tourelles.h"

#define LIGNES 7
#define COLONNES 15
#define MAX_TOURELLES 10 // on ne peux pas avoir plus de 10 tourelles

int main() {

    char grille[LIGNES][COLONNES];

    //initialisé les listes chainés
    Tourelle *tourelles = NULL;
    Etudiant *ennemis = NULL;

    int cagnotte = 0;
    int tour = 0;

    if (fichier_existe("C:\\Users\\willi\\Desktop\\Programmation_C\\Projet_C_nv\\donnees\\sauvegarde.txt")) { // faudra changer le chemin d'accès
        printf("\n \x1B[38;2;11;250;131m J'ai detecté une sauvegarde. Veux tu la charger ? (Ecrire 1 si Oui ou 0 sinon) : \033[0m");
        int charger;
        scanf("%d", &charger);

        if (charger) { //le joueur a ecrit 1
            charger_sauvegarde("C:\\Users\\willi\\Desktop\\Programmation_C\\Projet_C_nv\\donnees\\sauvegarde.txt", &tour, &cagnotte, &tourelles, &ennemis);
        }
        
        else { //le joueur a écrit 0
            printf("\n\033[32m Pas de soucis. Je vais te créer une nouvelle partie... \033[0m\n");
            ennemis = charger_partie("C:\\Users\\willi\\Desktop\\Programmation_C\\Projet_C_nv\\donnees\\Niveau_facile.txt", &cagnotte); //Niveau_facile.txt   Niveau_impossible.txt
        }

    } 
    
    else {//pas de sauvegarde
        printf("\n\033[32m Je n'ai trouvé aucune sauvegarde. Création d'une nouvelle partie...\033[0m\n");
        ennemis = charger_partie("C:\\Users\\willi\\Desktop\\Programmation_C\\Projet_C_nv\\donnees\\Niveau_facile.txt", &cagnotte);
    }

    if (ennemis == NULL) {
        printf("ATTENTION ! le chemin d'accès du fichier de la partie est invalide \n");
        return EXIT_FAILURE;
    }


    //on commence avec 3 tourelles de base
    tourelles = ajouter_tourelle(tourelles, 1,0, 'T');
    tourelles = ajouter_tourelle(tourelles, 7,0, 'L');
    tourelles = ajouter_tourelle(tourelles, 4,2, 'P');


    int tourelles_place = 3; //on commence chaque partie avec 3 tourelles dès le début !


    while (1) { //Boucle du jeu

        //printf("\033[2J"); // Efface l'écran

        initialiser_grille(grille, tourelles);

        ajouter_ennemis_a_la_grille(grille, ennemis);

        afficher_grille(grille, tour, cagnotte, ennemis, tourelles);

        if (tour % 10 == 0 && tour != 0) { 
            printf("\n\033[33mSouhaite-tu sauvegarder la partie ? (1 = Oui, 0 = Non) : \033[0m");
            int sauvegarder;
            scanf("%d", &sauvegarder);

            if (sauvegarder) {
                sauvegarder_partie("sauvegarde.txt", tour, cagnotte, tourelles, ennemis);
                break;

            }
        }

        if (tourelles_place < MAX_TOURELLES && tour % 5 == 0) { // Demande tous les 5 tours
            int i = 1;
            while (i) {
                printf("On va placer une tourelle à la ligne/colonne que tu veux ! \n");

                int l;
                int col;
                char type_tour;

                // Demander une ligne et une colonne valides
                do {
                    printf("Entre la ligne où tu veux placer ta tourelle : ");
                    scanf("%d", &l);
                    while (l < 1 || l > 7) {
                        printf("Indice incorrect\n");
                        printf("Entre la ligne où tu veux placer ta tourelle : ");
                        scanf("%d", &l);
                    }

                    printf("Entre la colonne où tu veux placer ta tourelle : ");
                    scanf("%d", &col);
                    while (col < 1 || col > 15) {
                        printf("Indice incorrect\n");
                        printf("Entre la colonne où tu veux placer ta tourelle : ");
                        scanf("%d", &col);
                    }

                    col--; //on decale col par ce que diff entre ce qu'on voit et la colonne de la grille officisuemeent, elle est décalé car commebce en [0] et non en 1

                    int statut = est_case_occupee(l, col, tourelles, ennemis);

                    if (statut == 1) {
                        printf("\033[31mERREUR : Une tourelle est déjà placée à cet endroit ! Choisis une autre position.\033[0m\n");
                    } else if (statut == 2) {
                        printf("\033[31mERREUR : Un ennemi est sur cette case ! Impossible de placer une tourelle ici.\033[0m\n");
                    }

                } while (est_case_occupee(l, col, tourelles, ennemis) != 0);  // Répéter tant que la case est occupée

                printf("\nTypes de tourelles : -- T (Basique) -- P (Puissante) -- L (Longue portée) --\n");

                do {
                    printf("Entre le type de ta tourelle : ");
                    scanf(" %c", &type_tour);
                } while (type_tour != 'T' && type_tour != 'P' && type_tour != 'L');

                int prix_tourelle = (type_tour == 'T') ? 100 : (type_tour == 'L') ? 200 : 300;
                if (cagnotte >= prix_tourelle) {
                    tourelles = ajouter_tourelle(tourelles, l, col, type_tour);
                    cagnotte -= prix_tourelle;
                    initialiser_grille(grille, tourelles);
                    afficher_grille(grille, tour, cagnotte, ennemis, tourelles);
                    printf("Tu viens de placer une tourelle !\n \nIl te reste %d pièces d'or \n", cagnotte);
                    tourelles_place += 1;
                } else {
                    printf("Dommage, pas assez d'argent ! (Tue des ennemis pour récupérer de l'argent)\n");
                    i = 0;
                    break;
                }

                printf("\nVeux-tu rajouter d'autres tourelles ? (1 = Oui, 0 = Non) : ");
                scanf("%d", &i);
                while (i != 1 && i != 0) {
                    printf("Choix incorrect\n");
                    printf("Entre ton choix : ");
                    scanf("%d", &i);
                }
            }
        }


        
        Etudiant* e_courant = ennemis;
        
        while (e_courant != NULL) {

            if (e_courant->tour==tour){
                e_courant->actif = 1;
            }

            if (e_courant->actif) {
                e_courant->colonne--; //fait bouger l'ennemi 
                if (e_courant->colonne < 0) {
                    e_courant->actif = 0; //rend l'étudiant inactif (ou mort mais c un peu glauque)
                }
            }
            e_courant = e_courant->suivant;
        }

        attaquer_ennemis(grille, tourelles, ennemis,&cagnotte);

        attaquer_tourelles(&tourelles,ennemis);

    
        tour++;

        Sleep(1000);
        
        if ((verifier_fin(grille)==1) && (tour > 1)) {
            printf("Il n'y a plus d'ennemis dans le jeu ! Gg à toi mon gourmand ! ");
            break;
        }
        
        if (verifier_fin(grille)==-1){
            printf("Un étudiant a atteint la base. Tu as perdu ! ");
            break;
        }

        if (tourelles == NULL) {
            printf("\n\033[31mToutes les tourelles ont été détruites !\033[0m\n");
            break;
        }

    }

    while (tourelles != NULL) {
        Tourelle *temp = tourelles;
        tourelles = tourelles->suivant;
        free(temp);
    }

    while (ennemis != NULL) {
        Etudiant *temp = ennemis;
        ennemis = ennemis->suivant;
        free(temp);
    }

    return 0;
}