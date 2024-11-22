void sauvegarderScores(ScoreJoueur scores[], int nbJoueurs) {
    printf("Appel de sauvegarderScores() avec nbJoueurs = %d\n", nbJoueurs);
    FILE *file = fopen("scores.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier de scores.\n");
        perror("fopen");
        return;
    }
