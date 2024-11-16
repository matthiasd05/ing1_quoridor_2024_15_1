#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>
#include <string.h>

#define MAX_JOUEURS 100
#define NOM_MAX 50

/**
 * @brief Structure pour stocker le nom et le score d'un joueur.
 */
typedef struct {
 char nom[NOM_MAX];
 int score;
} ScoreJoueur;

/**
 * @brief Lit les scores depuis le fichier et les stocke dans un tableau.
 *
 * @param scores Tableau pour stocker les scores des joueurs.
 * @param nbJoueurs Pointeur vers un entier pour stocker le nombre de joueurs lus.
 */
void lireScores(ScoreJoueur scores[], int *nbJoueurs);

/**
 * @brief Sauvegarde les scores des joueurs dans le fichier.
 *
 * @param scores Tableau contenant les scores des joueurs.
 * @param nbJoueurs Nombre de joueurs à sauvegarder.
 */
void sauvegarderScores(ScoreJoueur scores[], int nbJoueurs);

/**
 * @brief Met à jour le score d'un joueur après une partie.
 *
 * @param scores Tableau contenant les scores des joueurs.
 * @param nbJoueurs Pointeur vers le nombre de joueurs.
 * @param nomJoueur Nom du joueur à mettre à jour.
 * @param scorePartie Score obtenu lors de la partie.
 */
void mettreAJourScore(ScoreJoueur scores[], int *nbJoueurs, const char *nomJoueur, int scorePartie);

#endif // SCORE_H
