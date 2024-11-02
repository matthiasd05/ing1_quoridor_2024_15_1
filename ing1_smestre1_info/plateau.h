#ifndef PLATEAU_H
#define PLATEAU_H

#include <stdbool.h>
#include "joueur.h"

#define TAILLE_PLATEAU 9

/**
 * @brief Enumération pour les types de cases du plateau.
 */
typedef enum {
 VIDE, /**< Case vide */
 PION  /**< Case contenant un pion */
} TypeDeCase;

/**
 * @brief Structure représentant une case du plateau.
 */
typedef struct {
 TypeDeCase type;     /**< Type de la case (VIDE ou PION) */
 char symbole;        /**< Symbole affiché sur la case */
 int couleurtexte;    /**< Couleur du texte */
 int couleurfond;     /**< Couleur du fond */
 bool barrierehaut;   /**< Indique la présence d'une barrière en haut */
 bool barrierebas;    /**< Indique la présence d'une barrière en bas */
 bool barrieregauche; /**< Indique la présence d'une barrière à gauche */
 bool barrieredroite; /**< Indique la présence d'une barrière à droite */
} CasePlateau;

/**
 * @brief Initialise le plateau de jeu en réinitialisant toutes les cases.
 *
 * @param plateau Le plateau de jeu à initialiser.
 */
void initialisationplateau(CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

/**
 * @brief Affiche le plateau de jeu avec les pions et les barrières.
 *
 * Affiche le plateau en tenant compte des pions des joueurs,
 * des barrières positionnées, ainsi que des couleurs associées.
 *
 * @param plateau Le plateau de jeu.
 * @param joueurs Le tableau des joueurs.
 * @param nombredejoueurs Le nombre total de joueurs.
 */
void afficherplateau(CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nombredejoueurs);

#endif // PLATEAU_H
