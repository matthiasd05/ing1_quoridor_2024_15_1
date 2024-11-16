#include <stdio.h>
#include "menu.h"
#include "jeux.h"

/**
 * @file menu.c
 * @brief Implémentation des fonctions liées au menu principal du jeu.
 */

/**
 * @brief Affiche le menu principal et gère la navigation.
 *
 * Propose à l'utilisateur de démarrer une nouvelle partie, charger une partie existante,
 * afficher l'aide, voir les scores ou quitter le jeu.
 */
void affichermenuprincipal() {
    int choix;
    do {
        printf("\n=== Menu Principal ===\n");
        printf("1. Nouvelle Partie\n");
        printf("2. Charger une Partie\n");
        printf("3. Afficher l'Aide\n");
        printf("4. Afficher les Scores\n");
        printf("5. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
        case 1:
            nouvellepartie();
            break;
        case 2:
            chargerpartie();
            break;
        case 3:
            afficheraide();
            break;
        case 4:
            afficherscore();
            break;
        case 5:
            quitterlejeu();
            break;
        default:
            printf("Le choix n'est pas correct. Veuillez reessayer.\n");
        }
    } while (choix != 5);
}
