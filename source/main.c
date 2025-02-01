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
#define MAX_TOURELLES 3

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
    tourelles = ajouter_tourelle(tourelles, 3,0, 'L');
    tourelles = ajouter_tourelle(tourelles, 4,2, 'P');


    int tourelles_place = 2; //on commence chaque partie avec 2 tourelles dès le début !

    int iteration = 0; 

    while (1) { //Boucle du jeu

        printf("\033[2J"); // Efface l'écran

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

        if (tourelles_place<MAX_TOURELLES){
   
            int i = 1;
            while(i){

                printf("On va placer une tourelle à la ligne/colonne que tu veux ! \n");


                int l; //var tempor pour la ligne qu'on va demandé, sera dcp réinitalise a chaque tour 
                int col; //var tempor...
                char type_tour;

                
                printf("Entre la ligne ou tu veux placer ta tourelle : ");
                scanf("%d", &l);
                while(l < 1 || l > 7){
                    printf("Indice incorrect\n");
                    printf("Entre la ligne ou tu veux placer ta tourelle : ");
                    scanf("%d", &l);
                }

                printf("Entre la colonne ou tu veux placer ta tourelle : ");
                scanf("%d", &col);
                while(col < 1 || col > 15){
                    printf("Indice incorrect\n");
                    printf("Entre la colonne ou tu veux placer ta tourelle : ");
                    scanf("%d", &col);
                }

                printf("\nTypes de tourelles : -- T (Basique) -- P (Puissante) -- L (Longue portée) --\n");

                do { //on utilise un do pour le demander au moins une fois (puis ça change des while d'au dessus)
                    printf("Entre le type de ta tourelle : ");
                    scanf(" %c", &type_tour);  // Ajout d’un espace avant `%c` pour éviter le problème de buffer
                } while (type_tour != 'T' && type_tour != 'P' && type_tour != 'L');

                col--;

                //faudra aussi verifie si la ligne est pas déja occupé et renvoyé une erreur ou un msg d'erreur en mode TANT PIS place deja prise donc faudra faire gaffe en tant que joueur car pas de joker
                /*if (grille[l][col] != '.') {
                    printf("Attention tu as voulu placer une tourelle mais il y a déjà un étudiant dans la case.")
                    printf("Tu perds la tourelle et ton argent ! ")
                } */

                if (cagnotte >= 100 ) { // Coût d'une tourelle : 100 et on est a moins de tourelles sur la grille que de la CONSTANTE MAX_TOURELLES defini plus haut juste en dessous des #include
                    tourelles = ajouter_tourelle(tourelles, l, col, type_tour);
                    cagnotte -= 100;
                    initialiser_grille(grille, tourelles); // A chaque fois on réinitialise la grille pour afficher la nouvelle grille (avec la nouvelle tourelle)
                    afficher_grille(grille, tour, cagnotte,ennemis,tourelles); 
                    printf("Tu viens de placer une tourelle !\n \nIl te reste %d pièces d'or \n", cagnotte);
                    tourelles_place+=1;
                    
                }

                else { //on a pas assez d'argent pour placer
                    printf("Dommage pas assez de sous ! (Tue des ennemis pour récuper des sous) \n"); // A FAIRE DANS tourelles.c 
                    i = 0;
                    break;
                }

                printf("\n");
                printf("Veux tu rajouter d'autres toutelles ? (Ecris '1' si tu en veux, ou '0' sinon) : "); //gerer bug si diff de 1 ou 0
                scanf("%d", &i);
                
                while(i!=1 && i!=0){ // tant qu'on a pas le bon choix 1 ou 0
                    printf("Choix incorrect\n");
                    printf("Entre ton choix : ");
                    scanf("%d", &i);
                }

            }
        }

        
        // Met à jour les ennemis actifs pour le tour courant
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

        attaquer_ennemis(grille, tourelles, ennemis);

        attaquer_tourelles(&tourelles,ennemis);

    
        tour++;

        Sleep(1000);
        
        if ((verifier_fin(grille)==1) && (iteration > 1)) {
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

        iteration++;
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