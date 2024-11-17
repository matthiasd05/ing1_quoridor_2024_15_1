#ifndef JEUX_H
#define JEUX_H

#include "plateau.h"
#include "joueur.h"
#include "score.h"
#include <stdbool.h>

/**
 * @brief Lance une nouvelle partie du jeu.
 */
void nouvellepartie();

/**
 * @brief Charge une partie sauvegardée.
 */
void chargerpartie();

/**
 * @brief Affiche l'aide du jeu.
 */
void afficheraide();

/**
 * @brief Affiche les scores des joueurs.
 */
void afficherscore();

/**
 * @brief Quitte le jeu.
 */
void quitterlejeu();

/**
 * @brief Joue une partie chargée depuis une sauvegarde.
 *
 * @param plateau Le plateau de jeu chargé.
 * @param joueurs Tableau des joueurs chargés.
 * @param nombredejoueurs Nombre total de joueurs.
 * @param joueurCourant Indice du joueur dont c'est le tour.
 */
void jouerPartieChargee(CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nombredejoueurs, int joueurCourant, ScoreJoueur scores[], int *nbJoueursScores);
/**
 * @brief Gère le tour d'un joueur.
 *
 * @param joueur Pointeur vers le joueur qui joue son tour.
 * @param plateau Le plateau de jeu.
 * @param joueurs Tableau des joueurs.
 * @param nombredejoueur Nombre de joueurs.
 */
void jouerTour(Joueur *joueur, CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nombredejoueur);

/**
 * @brief Vérifie si le déplacement du pion est valide.
 *
 * @param joueur Pointeur vers le joueur.
 * @param x Coordonnée X de la case cible.
 * @param y Coordonnée Y de la case cible.
 * @param plateau Le plateau de jeu.
 * @param joueurs Tableau des joueurs.
 * @param nombredejoueur Nombre de joueurs.
 * @return true si le déplacement est valide, false sinon.
 */
bool estDeplacementValide(Joueur *joueur, int x, int y, CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nombredejoueur);

/**
 * @brief Déplace le pion du joueur.
 *
 * @param joueur Pointeur vers le joueur.
 * @param plateau Le plateau de jeu.
 * @param joueurs Tableau des joueurs.
 * @param nombredejoueur Nombre de joueurs.
 */
void deplacerPion(Joueur *joueur, CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nombredejoueur);

/**
 * @brief Permet au joueur de placer une barrière.
 *
 * @param joueur Pointeur vers le joueur.
 * @param plateau Le plateau de jeu.
 */
void placerBarriere(Joueur *joueur, CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

/**
 * @brief Vérifie si le placement de la barrière est valide.
 *
 * @param x Coordonnée X de la case de départ.
 * @param y Coordonnée Y de la case de départ.
 * @param orientation Orientation de la barrière ('h' ou 'v').
 * @param plateau Le plateau de jeu.
 * @return true si le placement est valide, false sinon.
 */
bool estPlacementBarriereValide(int x, int y, char orientation, CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

/**
 * @brief Vérifie si la partie est terminée.
 *
 * @param joueur Pointeur vers le joueur à vérifier.
 * @return true si la partie est terminée, false sinon.
 */
bool verifierFinDePartie(Joueur *joueur);

/**
 * @brief Annule le dernier coup joué.
 *
 * @param joueur Pointeur vers le joueur.
 * @param plateau Le plateau de jeu.
 */
void annulerDernierCoup(Joueur *joueur, CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]);

/**
 * @brief Sauvegarde la partie actuelle dans un fichier.
 *
 * @param plateau Le plateau de jeu.
 * @param joueurs Tableau des joueurs.
 * @param nombredejoueurs Nombre total de joueurs.
 * @param joueurCourant Indice du joueur dont c'est le tour.
 */
void sauvegarderPartie(CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nombredejoueurs, int joueurCourant);

void gererFinDePartie(Joueur joueurs[], int nombredejoueur, int joueurGagnantIndex, ScoreJoueur scores[], int *nbJoueursScores);
#endif // JEUX_H
