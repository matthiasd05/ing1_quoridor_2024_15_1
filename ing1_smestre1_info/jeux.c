#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "joueur.h"
#include "plateau.h"
#include "jeux.h"
#include "outils.h" // Pour les fonctions utilitaires comme Color

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

void jouerTour(Joueur *joueur, CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nombredejoueur) {
    int choix;
    printf("C'est le tour de %s.\n", joueur->nom);
    printf("1. Déplacer le pion\n");
    printf("2. Placer une barrière\n");
    printf("3. Passer le tour\n");
    printf("4. Annuler le dernier coup\n");
    printf("Votre choix: ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            deplacerPion(joueur, plateau, joueurs, nombredejoueur);
            break;
        case 2:
            placerBarriere(joueur, plateau);
            break;
        case 3:
            printf("%s passe son tour.\n", joueur->nom);
            break;
        case 4:
            annulerDernierCoup(joueur, plateau);
            break;
        default:
            printf("Choix invalide. Veuillez réessayer.\n");
            jouerTour(joueur, plateau, joueurs, nombredejoueur);
    }
}

bool verifierFinDePartie(Joueur *joueur) {
    // Vérifier si le joueur a atteint le bord opposé
    if (joueur->numJoueur == 1) {
        if (joueur->positionY == TAILLE_PLATEAU - 1) {
            return true;
        }
    } else if (joueur->numJoueur == 2) {
        if (joueur->positionY == 0) {
            return true;
        }
    } else if (joueur->numJoueur == 3) {
        if (joueur->positionX == TAILLE_PLATEAU - 1) {
            return true;
        }
    } else if (joueur->numJoueur == 4) {
        if (joueur->positionX == 0) {
            return true;
        }
    }
    return false;
}

// Les autres fonctions à implémenter
void chargerpartie() {
    // Implémenter la fonctionnalité de chargement de partie
    printf("Chargement de la partie...\n");
    // Code à implémenter
}

void afficheraide() {
    // Afficher les règles du jeu ou l'aide
    printf("=== Aide du Jeu ===\n");
    printf("Le but du jeu est d'atteindre le côté opposé du plateau avant vos adversaires.\n");
    printf("Vous pouvez déplacer votre pion ou placer des barrières pour bloquer vos adversaires.\n");
    // Ajoutez plus de détails selon les règles
}

void afficherscore() {
    // Afficher les scores des joueurs
    printf("Affichage des scores...\n");
    // Code à implémenter
}

void quitterlejeu() {
    // Sauvegarder l'état si nécessaire et quitter
    printf("Au revoir !\n");
    // Code à implémenter si nécessaire
}

void deplacerPion(Joueur *joueur, CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nombredejoueur) {
    int x, y;
    printf("Entrez les coordonnées X et Y de la case où vous voulez déplacer votre pion :\n");
    scanf("%d %d", &x, &y);

    // Vérifier si le déplacement est valide
    if (estDeplacementValide(joueur, x, y, plateau, joueurs, nombredejoueur)) {
        // Mettre à jour le plateau
        plateau[joueur->positionY][joueur->positionX].type = VIDE;
        plateau[joueur->positionY][joueur->positionX].symbole = ' ';

        joueur->positionX = x;
        joueur->positionY = y;

        plateau[y][x].type = PION;
        plateau[y][x].symbole = joueur->pion;
    } else {
        printf("Déplacement invalide. Veuillez réessayer.\n");
        deplacerPion(joueur, plateau, joueurs, nombredejoueur);
    }
}

bool estDeplacementValide(Joueur *joueur, int x, int y, CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nombredejoueur) {
    // Vérifier que les coordonnées sont dans le plateau
    if (x < 0 || x >= TAILLE_PLATEAU || y < 0 || y >= TAILLE_PLATEAU) {
        return false;
    }

    // Calcul de la différence entre la position actuelle et la position cible
    int dx = x - joueur->positionX;
    int dy = y - joueur->positionY;

    // Vérifier que le déplacement est d'une case adjacente
    if ((abs(dx) == 1 && dy == 0) || (dx == 0 && abs(dy) == 1)) {
        // Vérifier qu'il n'y a pas de barrière entre les cases
        if (dx == 1) { // Déplacement vers la droite
            if (!plateau[joueur->positionY][joueur->positionX].barrieredroite && !plateau[y][x].barrieregauche) {
                return plateau[y][x].type == VIDE;
            }
        } else if (dx == -1) { // Déplacement vers la gauche
            if (!plateau[joueur->positionY][joueur->positionX].barrieregauche && !plateau[y][x].barrieredroite) {
                return plateau[y][x].type == VIDE;
            }
        } else if (dy == 1) { // Déplacement vers le bas
            if (!plateau[joueur->positionY][joueur->positionX].barrierebas && !plateau[y][x].barrierehaut) {
                return plateau[y][x].type == VIDE;
            }
        } else if (dy == -1) { // Déplacement vers le haut
            if (!plateau[joueur->positionY][joueur->positionX].barrierehaut && !plateau[y][x].barrierebas) {
                return plateau[y][x].type == VIDE;
            }
        }
    }

    // Vérifier le cas où un pion est en face et possibilité de sauter par-dessus
    // À implémenter si nécessaire

    return false;
}

void placerBarriere(Joueur *joueur, CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    if (joueur->nbBarriere <= 0) {
        printf("Vous n'avez plus de barrières disponibles.\n");
        return;
    }

    int x, y;
    char orientation;
    printf("Entrez les coordonnées de la case de départ pour la barrière (x y) :\n");
    scanf("%d %d", &x, &y);
    printf("Entrez l'orientation de la barrière (h pour horizontale, v pour verticale) :\n");
    scanf(" %c", &orientation);

    // Vérifier que le placement est valide
    if (estPlacementBarriereValide(x, y, orientation, plateau)) {
        // Placer la barrière
        if (orientation == 'h') {
            // Placer une barrière horizontale
            plateau[y][x].barrierebas = true;
            plateau[y][x + 1].barrierebas = true;
        } else if (orientation == 'v') {
            // Placer une barrière verticale
            plateau[y][x].barrieredroite = true;
            plateau[y + 1][x].barrieredroite = true;
        }
        joueur->nbBarriere--;
        printf("Barrière placée avec succès.\n");
    } else {
        printf("Placement de barrière invalide. Veuillez réessayer.\n");
        placerBarriere(joueur, plateau);
    }
}

bool estPlacementBarriereValide(int x, int y, char orientation, CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    // Vérifier que les coordonnées sont dans le plateau
    if (x < 0 || y < 0 || x >= TAILLE_PLATEAU || y >= TAILLE_PLATEAU) {
        return false;
    }

    if (orientation == 'h') {
        // Vérifier que la barrière ne sort pas du plateau
        if (x + 1 >= TAILLE_PLATEAU) {
            return false;
        }
        // Vérifier qu'il n'y a pas déjà une barrière horizontale à cet endroit
        if (plateau[y][x].barrierebas || plateau[y][x + 1].barrierebas) {
            return false;
        }
    } else if (orientation == 'v') {
        // Vérifier que la barrière ne sort pas du plateau
        if (y + 1 >= TAILLE_PLATEAU) {
            return false;
        }
        // Vérifier qu'il n'y a pas déjà une barrière verticale à cet endroit
        if (plateau[y][x].barrieredroite || plateau[y + 1][x].barrieredroite) {
            return false;
        }
    } else {
        // Orientation invalide
        return false;
    }

    // Vérifier que le placement de la barrière ne bloque pas complètement le chemin
    // Pour simplifier, cette vérification n'est pas implémentée ici
    // Vous pouvez l'ajouter ultérieurement

    return true;
}

void annulerDernierCoup(Joueur *joueur, CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    // Implémenter l'annulation du dernier coup
    printf("Annulation du dernier coup non implémentée.\n");
}
