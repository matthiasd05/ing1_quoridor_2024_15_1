#include "score.h"
#include <stdlib.h>

void lireScores(ScoreJoueur scores[], int *nbJoueurs) {
    FILE *file1 = fopen("scores.txt", "r");
    if (file1 == NULL) {
        printf("\nAucun fichier de scores trouve. Un nouveau fichier sera cree lors de la sauvegarde.\n");
        *nbJoueurs = 0;
        return;
    }

    *nbJoueurs = 0;
    while (fscanf(file1, "%49s %d", scores[*nbJoueurs].nom, &scores[*nbJoueurs].score) == 2) {
        (*nbJoueurs)++;
        if (*nbJoueurs >= MAX_JOUEURS) {
            break;
        }
    }

    fclose(file1);
}

void sauvegarderScores(ScoreJoueur scores[], int nbJoueurs) {
    printf("Appel de sauvegarderScores() avec nbJoueurs = %d\n", nbJoueurs);
    FILE *file = fopen("scores.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier de scores.\n");
        perror("fopen");
        return;
    }

    printf("Sauvegarde des scores...\n");

    for (int i = 0; i < nbJoueurs; i++) {
        fprintf(file, "%s %d\n", scores[i].nom, scores[i].score);
        printf("Enregistrement : %s %d\n", scores[i].nom, scores[i].score);
    }

    fclose(file);
    printf("Scores sauvegardes avec succes.\n");
}

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
