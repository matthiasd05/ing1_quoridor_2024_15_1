#ifndef PLATEAU_H
#define PLATEAU_H

#include <stdbool.h>
#include "joueur.h"
#define TAILLE_PLATEAU 9

/**
 * @brief Enumération pour les types de cases du plateau.
 */
typedef enum {
    VIDE,
    PION
} TypeDeCase;

/**
 * @brief Structure représentant une case du plateau.
 */
typedef struct {
    TypeDeCase type;
    char symbole;
    int couleurtexte;
    int couleurfond;
    bool barrierehaut;
    bool barrierebas;
    bool barrieregauche;
    bool barrieredroite;
} CasePlateau;

/**
 * @brief Initialise le plateau de jeu.
 *
 * @param plateau Le plateau de jeu à initialiser.
 */
void initialisationplateau(CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

/**
 * @brief Affiche le plateau de jeu avec les pions et les barrières.
 *
 * @param plateau Le plateau de jeu.
 * @param joueurs Le tableau des joueurs.
 * @param nombredejoueurs Le nombre de joueurs.
 */
void afficherplateau(CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nombredejoueurs);

#endif // PLATEAU_H
