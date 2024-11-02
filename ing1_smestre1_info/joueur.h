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
 * @brief Crée et initialise les joueurs pour la partie.
 *
 * Cette fonction demande à chaque joueur de saisir son nom et son symbole de pion,
 * initialise leur position de départ en fonction du nombre de joueurs,
 * et attribue le nombre initial de barrières.
 *
 * @param joueurs Tableau des joueurs à initialiser.
 * @param nombredejoueur Nombre total de joueurs dans la partie.
 */
void creerjoueur(Joueur joueurs[], int nombredejoueur);

#endif // JOUEUR_H
