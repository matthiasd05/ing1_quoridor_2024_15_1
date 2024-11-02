#ifndef OUTILS_H
#define OUTILS_H

/**
 * @brief Déplace le curseur à la position spécifiée dans la console.
 *
 * @param lig Ligne où déplacer le curseur (axe Y).
 * @param col Colonne où déplacer le curseur (axe X).
 */
void gotoligcol(int lig, int col);

/**
 * @brief Change la couleur du texte et du fond dans la console.
 *
 * @param couleurDuTexte Code de la couleur du texte (0-15).
 * @param couleurDeFond Code de la couleur du fond (0-15).
 */
void Color(int couleurDuTexte, int couleurDeFond);

/**
 * @brief Efface l'écran de la console.
 */
void effacerEcran();

#endif // OUTILS_H
