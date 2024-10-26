#ifndef JOUEUR_H
#define JOUEUR_H

#define TAILLE_NOM 50

/**
 * @brief Structure représentant un joueur.
 */
typedef struct {
    char nom[TAILLE_NOM]; /**< Nom du joueur */
    char pion;            /**< Symbole du pion */
    int numJoueur;        /**< Numéro du joueur */
    int nbBarriere;       /**< Nombre de barrières restantes */
    int positionX;        /**< Position X sur le plateau */
    int positionY;        /**< Position Y sur le plateau */
    int score;            /**< Score du joueur */
} Joueur;

/**
 * @brief Crée les joueurs pour la partie.
 *
 * @param joueurs Tableau des joueurs.
 * @param nombredejoueur Nombre de joueurs.
 */
void creerjoueur(Joueur joueurs[], int nombredejoueur);

#endif // JOUEUR_H
