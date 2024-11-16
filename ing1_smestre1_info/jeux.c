#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "joueur.h"
#include "plateau.h"
#include "jeux.h"
#include "outils.h"
#include "score.h"
/**
 * @brief Démarre une nouvelle partie de jeu.
 *
 * Cette fonction initialise les joueurs, le plateau, et lance la boucle principale du jeu
 * jusqu'à ce qu'un joueur remporte la partie. Elle gère également le calcul des scores
 * et la mise à jour du fichier de scores à la fin de la partie.
 */
void nouvellepartie() {
    int nombredejoueur;
    printf("Entrez le nombre de joueurs (2 ou 4): \n");
    scanf("%d", &nombredejoueur);

    if (nombredejoueur != 2 && nombredejoueur != 4) {
        printf("Nombre de joueurs invalide. Veuillez entrer 2 ou 4.\n");
        return;
    }

    // Lecture des scores actuels
    ScoreJoueur scores[MAX_JOUEURS];
    int nbJoueursScores = 0;
    lireScores(scores, &nbJoueursScores);

    Joueur joueurs[nombredejoueur];
    creerjoueur(joueurs, nombredejoueur);

    // Mise à jour des scores des joueurs
    for (int i = 0; i < nombredejoueur; i++) {
        // Initialiser le score total du joueur
        joueurs[i].score = 0;

        // Rechercher si le joueur existe déjà dans les scores
        for (int j = 0; j < nbJoueursScores; j++) {
            if (strcmp(joueurs[i].nom, scores[j].nom) == 0) {
                // Le joueur existe, mettre à jour son score total
                joueurs[i].score = scores[j].score;
                break;
            }
        }

        // Initialiser le score de la partie
        joueurs[i].scorePartie = 0;
    }

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
    int joueurCourant = 0;

    while (!finDePartie) {
        printf("Début du tour du joueur %d (%s)\n", joueurCourant + 1, joueurs[joueurCourant].nom);
        afficherplateau(plateau, joueurs, nombredejoueur);
        jouerTour(&joueurs[joueurCourant], plateau, joueurs, nombredejoueur);

        // Vérifier la fin de la partie
        printf("Vérification de fin de partie pour le joueur %d (%s) à la position (%d, %d)\n",
               joueurs[joueurCourant].numJoueur, joueurs[joueurCourant].nom,
               joueurs[joueurCourant].positionX, joueurs[joueurCourant].positionY);

        finDePartie = verifierFinDePartie(&joueurs[joueurCourant]);
        printf("finDePartie après vérification : %d\n", finDePartie);

        if (finDePartie) {
            printf("Le joueur %s a gagné!\n", joueurs[joueurCourant].nom);

            // Mettre à jour les scores
            // Ajouter 5 points au gagnant
            joueurs[joueurCourant].scorePartie += 5;

            // Mettre à jour les scores de tous les joueurs
            for (int i = 0; i < nombredejoueur; i++) {
                printf("ScorePartie pour %s est %d\n", joueurs[i].nom, joueurs[i].scorePartie);
                mettreAJourScore(scores, &nbJoueursScores, joueurs[i].nom, joueurs[i].scorePartie);
            }

            // Sauvegarder les scores mis à jour
            printf("Appel de sauvegarderScores() depuis nouvellepartie()\n");
            sauvegarderScores(scores, nbJoueursScores);



            break;
        }

        joueurCourant = (joueurCourant + 1) % nombredejoueur;
    }
}


/**
 * @brief Gère le tour d'un joueur.
 *
 * Propose au joueur les différentes actions possibles lors de son tour
 * et exécute l'action choisie.
 *
 * @param joueur Pointeur vers le joueur dont c'est le tour.
 * @param plateau Le plateau de jeu.
 * @param joueurs Tableau des joueurs.
 * @param nombredejoueur Nombre total de joueurs.
 */
void jouerTour(Joueur *joueur, CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nombredejoueur) {
    int choix;
    printf("C'est le tour de %s.\n", joueur->nom);
    printf("1. Déplacer le pion\n");
    printf("2. Placer une barrière\n");
    printf("3. Sauvegarder la partie\n");
    printf("4. Passer le tour\n");
    printf("5. Annuler le dernier coup\n");
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
            sauvegarderPartie(plateau, joueurs, nombredejoueur, joueur->numJoueur - 1);
            jouerTour(joueur, plateau, joueurs, nombredejoueur); // Reprendre le tour après la sauvegarde
            break;
        case 4:
            printf("%s passe son tour.\n", joueur->nom);
            break;
        case 5:
            annulerDernierCoup(joueur, plateau);
            break;
        default:
            printf("Choix invalide. Veuillez réessayer.\n");
            jouerTour(joueur, plateau, joueurs, nombredejoueur);
    }
}

/**
 * @brief Vérifie si un joueur a atteint la condition de victoire.
 *
 * La condition de victoire est d'atteindre le côté opposé du plateau
 * en fonction du numéro du joueur.
 *
 * @param joueur Pointeur vers le joueur à vérifier.
 * @return true si le joueur a gagné, false sinon.
 */
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

/**
 * @brief Charge une partie sauvegardée.
 *
 * Cette fonction permet de charger une partie précédemment sauvegardée.
 */
void chargerpartie() {
    char nomFichier[100];
    printf("Entrez le nom du fichier de sauvegarde à charger : ");
    scanf("%s", nomFichier);

    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }

    int nombredejoueurs;
    int joueurCourant;

    // Charger le nombre de joueurs et le joueur courant
    fscanf(fichier, "%d", &nombredejoueurs);
    fscanf(fichier, "%d", &joueurCourant);

    Joueur joueurs[nombredejoueurs];

    // Charger les informations des joueurs
    for (int i = 0; i < nombredejoueurs; i++) {
        fscanf(fichier, "%s %c %d %d %d %d",
               joueurs[i].nom,
               &joueurs[i].pion,
               &joueurs[i].nbBarriere,
               &joueurs[i].positionX,
               &joueurs[i].positionY,
               &joueurs[i].score);
        joueurs[i].numJoueur = i + 1;
    }

    // Charger l'état du plateau
    CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            int type, symbole_int, couleurtexte, couleurfond;
            int barrierehaut, barrierebas, barrieregauche, barrieredroite;
            char symbole;

            fscanf(fichier, "%d %d %d %d %d %d %d %d",
                   &type,
                   &symbole_int, // Lire le symbole en entier
                   &barrierehaut,
                   &barrierebas,
                   &barrieregauche,
                   &barrieredroite,
                   &couleurtexte,
                   &couleurfond);

            symbole = (char)symbole_int; // Convertir l'entier en char

            plateau[i][j].type = type;
            plateau[i][j].symbole = symbole;
            plateau[i][j].barrierehaut = barrierehaut;
            plateau[i][j].barrierebas = barrierebas;
            plateau[i][j].barrieregauche = barrieregauche;
            plateau[i][j].barrieredroite = barrieredroite;
            plateau[i][j].couleurtexte = couleurtexte;
            plateau[i][j].couleurfond = couleurfond;
        }
    }

    fclose(fichier);
    printf("Partie chargée avec succès depuis le fichier %s.\n", nomFichier);

    // Lancer la partie chargée
    jouerPartieChargee(plateau, joueurs, nombredejoueurs, joueurCourant);
}


/**
 * @brief Joue une partie chargée depuis une sauvegarde.
 *
 * Cette fonction reprend la partie à partir de l'état chargé.
 *
 * @param plateau Le plateau de jeu chargé.
 * @param joueurs Tableau des joueurs chargés.
 * @param nombredejoueurs Nombre total de joueurs.
 * @param joueurCourant Indice du joueur dont c'est le tour.
 */
void jouerPartieChargee(CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nombredejoueurs, int joueurCourant) {
    bool finDePartie = false;
    int indiceJoueur = joueurCourant;

    while (!finDePartie) {
        afficherplateau(plateau, joueurs, nombredejoueurs);
        jouerTour(&joueurs[indiceJoueur], plateau, joueurs, nombredejoueurs);
        finDePartie = verifierFinDePartie(&joueurs[indiceJoueur]);
        if (finDePartie) {
            printf("Le joueur %s a gagne!\n", joueurs[indiceJoueur].nom);
            // Calcul des scores et sauvegarde si nécessaire
            break;
        }
        indiceJoueur = (indiceJoueur + 1) % nombredejoueurs;
    }
}

/**
 * @brief Sauvegarde la partie actuelle dans un fichier.
 *
 * Demande à l'utilisateur le nom du fichier de sauvegarde et enregistre
 * l'état actuel du plateau, des joueurs, et du joueur courant.
 *
 * @param plateau Le plateau de jeu.
 * @param joueurs Tableau des joueurs.
 * @param nombredejoueurs Nombre total de joueurs.
 * @param joueurCourant Indice du joueur dont c'est le tour.
 */
void sauvegarderPartie(CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nombredejoueurs, int joueurCourant) {
    char nomFichier[100];
    printf("Entrez le nom du fichier de sauvegarde : ");
    scanf("%s", nomFichier);

    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Erreur lors de la création du fichier de sauvegarde.\n");
        return;
    }

    // Sauvegarder le nombre de joueurs et le joueur courant
    fprintf(fichier, "%d\n", nombredejoueurs);
    fprintf(fichier, "%d\n", joueurCourant);

    // Sauvegarder les informations des joueurs
    for (int i = 0; i < nombredejoueurs; i++) {
        fprintf(fichier, "%s %c %d %d %d %d\n",
                joueurs[i].nom,
                joueurs[i].pion,
                joueurs[i].nbBarriere,
                joueurs[i].positionX,
                joueurs[i].positionY,
                joueurs[i].score);
    }

    // Sauvegarder l'état du plateau
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            fprintf(fichier, "%d %d %d %d %d %d %d %d\n",
                    plateau[i][j].type,
                    (int)plateau[i][j].symbole, // Symbole enregistré en entier
                    plateau[i][j].barrierehaut,
                    plateau[i][j].barrierebas,
                    plateau[i][j].barrieregauche,
                    plateau[i][j].barrieredroite,
                    plateau[i][j].couleurtexte,
                    plateau[i][j].couleurfond);
        }
    }

    fclose(fichier);
    printf("Partie sauvegardée avec succès dans le fichier %s.\n", nomFichier);
}


/**
 * @brief Affiche l'aide du jeu.
 *
 * Fournit des informations sur les règles et le fonctionnement du jeu.
 */
void afficheraide() {
    // Afficher les règles du jeu ou l'aide
    printf("=== Aide du Jeu ===\n");
    printf("Le but du jeu est d'atteindre le cote opposé du plateau avant vos adversaires.\n");
    printf("Vous pouvez deplacer votre pion ou placer des barrieres pour bloquer vos adversaires.\n");
    // Ajoutez plus de détails selon les règles
}

/**
 * @brief Affiche les scores des joueurs.
 *
 * Présente le classement des joueurs en fonction de leurs scores.
 */
void afficherscore() {
    // Lecture des scores actuels
    ScoreJoueur scores[MAX_JOUEURS];
    int nbJoueursScores = 0;
    lireScores(scores, &nbJoueursScores);

    // Vérifier si des scores ont été lus
    if (nbJoueursScores == 0) {
        printf("\nAucun score à afficher.\n");
        return;
    }

    // Afficher les scores des joueurs
    printf("\n=== Scores des joueurs ===\n");
    for (int i = 0; i < nbJoueursScores; i++) {
        printf("%s : %d points\n", scores[i].nom, scores[i].score);
    }
}

/**
 * @brief Quitte le jeu après avoir éventuellement sauvegardé l'état.
 *
 * Permet de sauvegarder la partie en cours avant de quitter le jeu.
 */
void quitterlejeu() {
    // Sauvegarder l'état si nécessaire et quitter
    printf("Au revoir !\n");
    // Code à implémenter si nécessaire
}

/**
 * @brief Déplace le pion du joueur sur le plateau.
 *
 * Demande au joueur les coordonnées de la case cible et vérifie si le déplacement est valide.
 *
 * @param joueur Pointeur vers le joueur qui déplace son pion.
 * @param plateau Le plateau de jeu.
 * @param joueurs Tableau des joueurs.
 * @param nombredejoueur Nombre total de joueurs.
 */
void deplacerPion(Joueur *joueur, CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nombredejoueur) {
    int x, y;
    printf("Entrez les coordonnees X et Y de la case ou vous voulez deplacer votre pion :\n");
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
        printf("Deplacement invalide. Veuillez reessayer.\n");
        deplacerPion(joueur, plateau, joueurs, nombredejoueur);
    }
}

/**
 * @brief Vérifie si le déplacement du pion est valide.
 *
 * Vérifie que la case cible est adjacente, qu'il n'y a pas de barrières bloquantes,
 * et que la case n'est pas occupée par un autre pion.
 *
 * @param joueur Pointeur vers le joueur qui souhaite se déplacer.
 * @param x Coordonnée X de la case cible.
 * @param y Coordonnée Y de la case cible.
 * @param plateau Le plateau de jeu.
 * @param joueurs Tableau des joueurs.
 * @param nombredejoueur Nombre total de joueurs.
 * @return true si le déplacement est valide, false sinon.
 */
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

/**
 * @brief Permet au joueur de placer une barrière sur le plateau.
 *
 * Demande au joueur les coordonnées et l'orientation de la barrière,
 * vérifie si le placement est valide, puis met à jour le plateau.
 *
 * @param joueur Pointeur vers le joueur qui place la barrière.
 * @param plateau Le plateau de jeu.
 */
void placerBarriere(Joueur *joueur, CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    if (joueur->nbBarriere <= 0) {
        printf("Vous n'avez plus de barrieres disponibles.\n");
        return;
    }

    int x, y;
    char orientation;
    printf("Entrez les coordonnees de la case de départ pour la barriere (x y) :\n");
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
        printf("Barriere placee avec succes.\n");
    } else {
        printf("Placement de barriere invalide. Veuillez reessayer.\n");
        placerBarriere(joueur, plateau);
    }
}

/**
 * @brief Vérifie si le placement d'une barrière est valide.
 *
 * Vérifie que la barrière ne sort pas du plateau, qu'elle ne chevauche pas une autre barrière,
 * et qu'elle ne bloque pas complètement le chemin d'un joueur.
 *
 * @param x Coordonnée X de la case de départ.
 * @param y Coordonnée Y de la case de départ.
 * @param orientation Orientation de la barrière ('h' pour horizontale, 'v' pour verticale).
 * @param plateau Le plateau de jeu.
 * @return true si le placement est valide, false sinon.
 */
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

/**
 * @brief Annule le dernier coup joué par le joueur.
 *
 * Permet au joueur de revenir à l'état précédent.
 *
 * @param joueur Pointeur vers le joueur.
 * @param plateau Le plateau de jeu.
 */
void annulerDernierCoup(Joueur *joueur, CasePlateau plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    // Implémenter l'annulation du dernier coup
    printf("Annulation du dernier coup non implementee.\n");
}
