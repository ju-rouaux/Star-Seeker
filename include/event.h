#ifndef _JEU_EVENTS_
#define _JEU_EVENTS_

#include <joueur.h>

/**
 * \brief Codes retournés par la fonction handleEvents indiquant les différents
 * contextes de sortie d'un niveau.
 */
typedef enum
{
    NIVEAU_QUITTER = -1, NIVEAU_CONTINUER = 0, NIVEAU_SUIVANT, NIVEAU_PRECEDENT
} e_code_sortie;

int handleEvents(t_joueur * joueur);

#endif
