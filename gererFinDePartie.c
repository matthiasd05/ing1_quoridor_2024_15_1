void gererFinDePartie(Joueur joueurs[], int nombredejoueur, int joueurGagnantIndex, ScoreJoueur scores[], int *nbJoueursScores) {
    printf("Le joueur %s a gagne!\n", joueurs[joueurGagnantIndex].nom);

    // Ajouter 5 points au gagnant
    joueurs[joueurGagnantIndex].scorePartie += 5;

    // Mettre à jour les scores de tous les joueurs
    for (int i = 0; i < nombredejoueur; i++) {
        printf("ScorePartie pour %s est %d\n", joueurs[i].nom, joueurs[i].scorePartie);
        mettreAJourScore(scores, nbJoueursScores, joueurs[i].nom, joueurs[i].scorePartie);
    }

    // Sauvegarder les scores mis à jour
    printf("Appel de sauvegarderScores() depuis gererFinDePartie()\n");
    sauvegarderScores(scores, *nbJoueursScores);
}
