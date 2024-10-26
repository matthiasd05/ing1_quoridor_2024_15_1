#include <windows.h>
#include "plateau.h"
#include "joueur.h"

int main() {
    CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
    initialisationplateau(plateau);

    int nombreDeJoueurs = 2;
    Joueur joueurs[nombreDeJoueurs];

    // Initialisation des joueurs pour le test
    strcpy(joueurs[0].nom, "Alice");
    joueurs[0].pion = 'A';
    joueurs[0].numJoueur = 1;
    joueurs[0].nbBarriere = 10;

    strcpy(joueurs[1].nom, "Bob");
    joueurs[1].pion = 'B';
    joueurs[1].numJoueur = 2;
    joueurs[1].nbBarriere = 10;

    // Positionner les pions sur le plateau
    plateau[0][TAILLE_PLATEAU / 2].type = PION;
    plateau[0][TAILLE_PLATEAU / 2].symbole = joueurs[0].pion;

    plateau[TAILLE_PLATEAU - 1][TAILLE_PLATEAU / 2].type = PION;
    plateau[TAILLE_PLATEAU - 1][TAILLE_PLATEAU / 2].symbole = joueurs[1].pion;

    // Afficher le plateau
    afficherplateau(plateau, joueurs, nombreDeJoueurs);

    return 0;
}
