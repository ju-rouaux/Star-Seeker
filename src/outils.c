/**
 * \file outils.c
 * \brief Bibliothèque de petites fonctions pratiques dans de nombreux cas.
 * \author Camille
*/

#include <stdlib.h>
#include <outils.h>



/**
 * Lancer de dé avec un nombre de faces personnalisé .
 * \param nbFaces Nombre de faces du dé à lancer
*/ 

int de(const int nbFaces){
    return(rand() % nbFaces + 1);
}