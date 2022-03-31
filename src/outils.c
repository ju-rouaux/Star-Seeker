/**
 * \file outils.c
 * \brief Bibliothèque de petites fonctions pratiques dans de nombreux cas.
 * \author Camille
*/

#include <stdlib.h>
#include <outils.h>
#include <stdlib.h>
#include <math.h>


/**
 * Lancer de dé avec un nombre de faces personnalisé .
 * \param nbFaces Nombre de faces du dé à lancer
*/ 
int de(const int nbFaces){
    return(rand() % nbFaces + 1);
}

/**
 * \brief Calcul la difficulté a partir de l'xp que le joueur possède
 * 
 * \param xp xp du joueur
 * \return indice de difficulté
 */
int calculDifficulte(int xp){
    if(xp < 10)
        return 1;
    return sqrt(xp/10);
}


//print the meaning of life