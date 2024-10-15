#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
/////////// PROTOTYPES DES SOUS-PROGRAMMES
void Color(int couleurDuTexte,int couleurDeFond);
///////////////////////////////////////
// Nom du sous-programme : COLOR
// Rôle : change la couleur du texte dans la console, ainsi que la couleur du fond pour la ligne
// Compatibilité : Xindows
///////////////////////////////////////
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

int main()
{
    /*
    0 : Noir
    1 : Bleu foncé
    2 : Vert foncé
    3 : Turquoise
    4 : Rouge foncé
    5 : Violet
    6 : Vert caca d'oie
    7 : Gris clair
    8 : Gris foncé
    9 : Bleu fluo
    10 : Vert fluo
    11 : Turquoise
    12 : Rouge fluo
    13 : Violet 2
    14 : Jaune
    15 : Blanc
    */
    // essai numero 1
    Color(12,3);
    printf("Le texte va avoir la couleur 12 et le Fond la couleur 3\n");

    // essai numero 2 : on repasse au noir et blanc
    Color(15, 0);
    printf("Hello world!\n");

    // essai 3 : un peu de turquoise
    Color(11, 0);
    printf("Hello world!\n");
    // et la derniere couleur reste jusqu'à ce qu'on change de nouveau
    printf("Hello world!\n");

    return 0;
}