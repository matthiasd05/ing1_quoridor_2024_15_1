#include <stdio.h>
#include "plateau.h"
#include "outils.h"
#include "joueur.h"

void initialisationplateau(CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            plateau[i][j].type = VIDE;
            plateau[i][j].symbole = ' ';
            plateau[i][j].couleurtexte = 15; // Blanc
            plateau[i][j].couleurfond = 0;   // Noir
            plateau[i][j].barrierehaut = false;
            plateau[i][j].barrierebas = false;
            plateau[i][j].barrieregauche = false;
            plateau[i][j].barrieredroite = false;
        }
    }
}
void afficherplateau(CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nombredejoueurs) {
    // Afficher la numérotation des colonnes
    printf("   ");
    for (int col = 0; col < TAILLE_PLATEAU; col++) {
        printf("  %2d  ", col);
    }
    printf("\n");

    for (int lig = 0; lig < TAILLE_PLATEAU; lig++) {
        // Affichage des barrières horizontales supérieures
        printf("   ");
        for (int col = 0; col < TAILLE_PLATEAU; col++) {
            if (plateau[lig][col].barrierehaut) {
                printf(" _____");
            } else {
                printf("      ");
            }
        }
        printf("\n");

        // Affichage du numéro de ligne
        printf(" %2d ", lig);

        // Affichage des barrières verticales et des cases
        for (int col = 0; col < TAILLE_PLATEAU; col++) {
            // Barrière gauche
            if (plateau[lig][col].barrieregauche) {
                printf("|");
            } else {
                printf(" ");
            }

            // Affichage de la case avec gestion des couleurs
            Color(plateau[lig][col].couleurtexte, plateau[lig][col].couleurfond);
            printf(" %c ", plateau[lig][col].symbole);
            Color(15, 0); // Réinitialiser les couleurs

            // Barrière droite
            if (plateau[lig][col].barrieredroite) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");

        // Affichage des barrières horizontales inférieures
        printf("   ");
        for (int col = 0; col < TAILLE_PLATEAU; col++) {
            if (plateau[lig][col].barrierebas) {
                printf(" -----");
            } else {
                printf("      ");
            }
        }
        printf("\n");
    }

    // Affichage des informations des joueurs
    for (int i = 0; i < nombredejoueurs; i++) {
        printf("Joueur %d: %s (Pion: %c, Barrières restantes: %d)\n",
               joueurs[i].numJoueur, joueurs[i].nom, joueurs[i].pion, joueurs[i].nbBarriere);
    }
}
