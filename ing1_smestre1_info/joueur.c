#include <stdio.h>
#include "joueur.h"

void creerjoueur(Joueur joueurs[], int nombredejoueur){
    for (int i = 0; i < nombredejoueur; i++){
        printf("Entrez le nom du joueur %d:\n", i+1);
        scanf("%s", joueurs[i].nombre);
        printf("Choisissez le symbole pour votre pion :\n");
        scanf("%s", joueurs[i].pion);
        joueurs[i].numjoueur = joueurs[i].numjoueur + 1;
        joueurs[i].nbbarriere = (nombredejoueur == 2) ? 10 : 5 ;
        joueurs[i].score = 0;
    }
}