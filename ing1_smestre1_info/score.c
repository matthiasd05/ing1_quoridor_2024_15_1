#include "score.h"
#include <stdlib.h>

/**
 * @brief Lit les scores depuis le fichier et les stocke dans un tableau.
 *
 * @param scores Tableau pour stocker les scores des joueurs.
 * @param nbJoueurs Pointeur vers un entier pour stocker le nombre de joueurs lus.
 */
void lireScores(ScoreJoueur scores[], int *nbJoueurs) {
    FILE *file1 = fopen("scores.txt", "r");
    if (file1 == NULL) {
        printf("Aucun fichier de scores trouvé.\n"); // Message de débogage
        perror("fopen");
        *nbJoueurs = 0;
        return;
    }

    printf("Lecture des scores...\n"); // Message de débogage

    *nbJoueurs = 0;
    while (fscanf(file1, "%49s %d", scores[*nbJoueurs].nom, &scores[*nbJoueurs].score) == 2) {
        printf("Lu : %s %d\n", scores[*nbJoueurs].nom, scores[*nbJoueurs].score); // Message de débogage
        (*nbJoueurs)++;
        if (*nbJoueurs >= MAX_JOUEURS) {
            break;
        }
    }

    fclose(file1);
}

/**
 * @brief Sauvegarde les scores des joueurs dans le fichier.
 *
 * @param scores Tableau contenant les scores des joueurs.
 * @param nbJoueurs Nombre de joueurs à sauvegarder.
 */
void sauvegarderScores(ScoreJoueur scores[], int nbJoueurs) {
    printf("Appel de sauvegarderScores() avec nbJoueurs = %d\n", nbJoueurs);
    FILE *file = fopen("scores.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier de scores.\n");
        return;
    }

    printf("Sauvegarde des scores...\n");

    for (int i = 0; i < nbJoueurs; i++) {
        fprintf(file, "%s %d\n", scores[i].nom, scores[i].score);
        printf("Enregistrement : %s %d\n", scores[i].nom, scores[i].score);
    }

    fclose(file);
    printf("Scores sauvegardés avec succès.\n");
}


/**
 * @brief Met à jour le score d'un joueur après une partie.
 *
 * @param scores Tableau contenant les scores des joueurs.
 * @param nbJoueurs Pointeur vers le nombre de joueurs.
 * @param nomJoueur Nom du joueur à mettre à jour.
 * @param scorePartie Score obtenu lors de la partie.
 */
void mettreAJourScore(ScoreJoueur scores[], int *nbJoueurs, const char *nomJoueur, int scorePartie) {
    int indiceJoueur = -1;

    // Rechercher si le joueur existe déjà
    for (int i = 0; i < *nbJoueurs; i++) {
        if (strcmp(scores[i].nom, nomJoueur) == 0) {
            indiceJoueur = i;
            break;
        }
    }

    if (indiceJoueur != -1) {
        // Le joueur existe, mettre à jour son score
        scores[indiceJoueur].score += scorePartie;
    } else {
        // Nouveau joueur, l'ajouter au tableau
        if (*nbJoueurs < MAX_JOUEURS) {
            strncpy(scores[*nbJoueurs].nom, nomJoueur, NOM_MAX - 1);
            scores[*nbJoueurs].nom[NOM_MAX - 1] = '\0'; // Assurer la terminaison de la chaîne
            scores[*nbJoueurs].score = scorePartie;
            (*nbJoueurs)++;
        } else {
            printf("Nombre maximum de joueurs atteint. Impossible d'ajouter %s.\n", nomJoueur);
        }
    }
}
