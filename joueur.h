#ifndef JOUEUR_H
#define JOUEUR_H
typedef struct joueur{
    char name[50];      /**<Nom du joueur*/
    char pion;          /**<Symbole du pion*/
    int numerojoueur;   /**<numero du joueur*/
    int nbbarrier;      /**<nb de barrieres restantes*/
    int positionX;      /**<Position du joueur en Y */
    int positionY;      /**<Postion du joueur en Y*/
    int score;          /**<Score du joueur*/
} joueur;

void creerjoueur(Joueur joueurs[], int nombredejoueur);
#endif //JOUEUR_H
