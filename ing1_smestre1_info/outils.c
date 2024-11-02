#include "outils.h"
#include <windows.h>
#include <stdio.h>

/**
 * @brief Déplace le curseur à une position spécifique dans la console.
 *
 * Cette fonction utilise les API Windows pour positionner le curseur
 * à la ligne et la colonne spécifiées, ce qui permet de contrôler
 * précisément l'affichage dans la console.
 *
 * @param lig Ligne où déplacer le curseur (axe Y).
 * @param col Colonne où déplacer le curseur (axe X).
 */
void gotoligcol(int lig, int col) {
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}

/**
 * @brief Change la couleur du texte et du fond dans la console.
 *
 * Modifie les attributs de couleur de la console pour le texte et le fond
 * en utilisant les codes de couleur spécifiés. Les codes de couleur sont
 * basés sur la table des couleurs de la console Windows.
 *
 * @param couleurDuTexte Code de la couleur du texte (0-15).
 * @param couleurDeFond Code de la couleur du fond (0-15).
 */
void Color(int couleurDuTexte, int couleurDeFond) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}

/**
 * @brief Efface l'écran de la console.
 *
 * Cette fonction utilise la commande système `cls` pour effacer l'écran,
 * réinitialisant ainsi l'affichage de la console.
 */
void effacerEcran() {
    system("cls");
}
