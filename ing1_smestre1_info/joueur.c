#include <stdio.h>
#include <string.h>
#include "joueur.h"
#include "plateau.h"

/**
 * @brief Crée les joueurs et initialise leurs informations.
 *
 * Demande les informations nécessaires à chaque joueur, telles que le nom et le symbole du pion,
 * initialise le nombre de barrières en fonction du nombre de joueurs,
 * et positionne chaque pion sur le plateau de jeu.
 *
 * @param joueurs Tableau des joueurs à initialiser.
 * @param nombredejoueur Nombre total de joueurs dans la partie.
 */
void creerjoueur(Joueur joueurs[], int nombredejoueur) {
    for (int i = 0; i < nombredejoueur; i++) {
        printf("Entrez le nom du joueur %d:\n", i + 1);
        scanf("%s", joueurs[i].nom);

        printf("Choisissez le symbole pour votre pion :\n");
        scanf(" %c", &joueurs[i].pion);

        joueurs[i].numJoueur = i + 1;
        joueurs[i].nbBarriere = (nombredejoueur == 2) ? 10 : 5;
        joueurs[i].score = 0;

        // Initialisation des positions du pion selon le joueur
        if (nombredejoueur == 2) {
            if (i == 0) {
                joueurs[i].positionX = TAILLE_PLATEAU / 2;
                joueurs[i].positionY = 0;
            } else {
                joueurs[i].positionX = TAILLE_PLATEAU / 2;
                joueurs[i].positionY = TAILLE_PLATEAU - 1;
            }
        } else if (nombredejoueur == 4) {
            // Initialiser les positions pour 4 joueurs
            if (i == 0) {
                joueurs[i].positionX = TAILLE_PLATEAU / 2;
                joueurs[i].positionY = 0;
            } else if (i == 1) {
                joueurs[i].positionX = TAILLE_PLATEAU - 1;
                joueurs[i].positionY = TAILLE_PLATEAU / 2;
            } else if (i == 2) {
                joueurs[i].positionX = TAILLE_PLATEAU / 2;
                joueurs[i].positionY = TAILLE_PLATEAU - 1;
            } else if (i == 3) {
                joueurs[i].positionX = 0;
                joueurs[i].positionY = TAILLE_PLATEAU / 2;
            }
        }
    }
}
