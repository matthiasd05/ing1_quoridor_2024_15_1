void lireScores(ScoreJoueur scores[], int *nbJoueurs) {
    FILE *file1 = fopen("scores.txt", "r");
    if (file1 == NULL) {
        printf("\nAucun fichier de scores trouve. Un nouveau fichier sera cree lors de la sauvegarde.\n");
        *nbJoueurs = 0;
        return;
    }
