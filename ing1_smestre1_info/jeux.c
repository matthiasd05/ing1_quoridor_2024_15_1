#include <stdio.h>
#include "joueur.h"
#include "plateau.h"
#include "jeux.h"

/**
 * @brief Lance une nouvelle partie du jeu.
 */
void nouvellepartie() {
    int nombredejoueur;
    printf("Entrez le nombre de joueurs (2 ou 4): \n");
    scanf("%d", &nombredejoueur);

    if (nombredejoueur != 2 && nombredejoueur != 4) {
        printf("Nombre de joueurs invalide. Veuillez entrer 2 ou 4.\n");
        return;
    }

    Joueur joueurs[nombredejoueur];
    creerjoueur(joueurs, nombredejoueur);

    // Initialisation du plateau
    CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
    initialisationplateau(plateau);

    // Positionnement des pions des joueurs sur le plateau
    for (int i = 0; i < nombredejoueur; i++) {
        int x = joueurs[i].positionX;
        int y = joueurs[i].positionY;
        plateau[y][x].type = PION;
        plateau[y][x].symbole = joueurs[i].pion;
    }

    // Lancer la boucle principale du jeu
    bool finDePartie = false;
    while (!finDePartie) {
        for (int i = 0; i < nombredejoueur; i++) {
            afficherplateau(plateau, joueurs, nombredejoueur);
            jouerTour(&joueurs[i], plateau, joueurs, nombredejoueur);
            finDePartie = verifierFinDePartie(&joueurs[i]);
            if (finDePartie) {
                printf("Le joueur %s a gagné!\n", joueurs[i].nom);
                // Calcul des scores et sauvegarde
                break;
            }
        }
    }
}
