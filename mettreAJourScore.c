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
