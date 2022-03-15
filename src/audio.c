/**
 * \file audio.c
 * 
 * \brief Gestion des musiques et des bruitages
 *
 * \author Camille REMOUÉ
 *  
 */


#include <stdio.h>
#include <audio.h>


int chargerAudio(t_musiques ** musiques, t_bruitages ** bruitages){

    t_musiques * m = malloc(sizeof(t_musiques));

      if(m == NULL)
    {
        printf("Impossible d'allouer la mémoire pour la structure musiques\n");
        return -1;
    }

    t_bruitages * b = malloc(sizeof(t_bruitages));

    if(b == NULL)
    {
        printf("Impossible d'allouer la mémoire pour la structure bruitages\n");
        return -1;
    }



    /* MUSIQUES */

    m -> menu_principal = Mix_LoadMUS("audio/musiques/main_menu.mp3");


    /* BRUITAGES */

    b -> treasure =  Mix_LoadMUS("audio/bruitages/treasure.wav");
    b -> boiling =  Mix_LoadMUS("audio/bruitages/boiling.wav");


    *bruitages = b;
    *musiques = m;



    return 0;

}


void detruireAudio(t_musiques ** m, t_bruitages ** b){


    /* MUSIQUES */
    if(*m != NULL)
    {
        Mix_FreeMusic((*m) -> menu_principal);
        free(*m);
    }

    *m = NULL;

    /* BRUITAGES */
    if(*b != NULL)
    {
        Mix_FreeMusic((*b) -> boiling);
        Mix_FreeMusic((*b) -> treasure);
        free(*b);
    }
    *b = NULL;
}


