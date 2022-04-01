/**
 * \file audio.c
 * 
 * \brief Gestion des musiques et des bruitages
 *
 * \author Camille Remoué
 *  
 */


#include <stdio.h>
#include <audio.h>

#define NB_CHANNELS 7

void changerVolume(int volume)
{
    Mix_VolumeMusic(3*volume/4);
    Mix_Volume(-1, volume);
}


int chargerAudio(int volume, t_musiques ** musiques, t_bruitages ** bruitages){

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

    m -> menu_principal = Mix_LoadMUS("assets/audio/musiques/main_menu.mp3");
    m -> ambiant =  Mix_LoadMUS("assets/audio/musiques/ambiant.wav");


    /* BRUITAGES */
    Mix_AllocateChannels(NB_CHANNELS);

    b -> treasure =  Mix_LoadWAV("assets/audio/bruitages/treasure.wav");
    b -> dash =  Mix_LoadWAV("assets/audio/bruitages/dash.wav");
    b -> hit =  Mix_LoadWAV("assets/audio/bruitages/hit.wav");
    b -> mort =  Mix_LoadWAV("assets/audio/bruitages/mort.wav");
    b -> menu_selection =  Mix_LoadWAV("assets/audio/bruitages/menu_select.wav");
    b -> swoop =  Mix_LoadWAV("assets/audio/bruitages/swoop.wav");
    b -> tir =  Mix_LoadWAV("assets/audio/bruitages/tir.wav");


    changerVolume(volume);

    *bruitages = b;
    *musiques = m;


    return 0;

}


void detruireAudio(t_musiques ** m, t_bruitages ** b){


    /* MUSIQUES */
    if(*m != NULL)
    {
        Mix_FreeMusic((*m) -> menu_principal);
        Mix_FreeMusic((*m) -> ambiant);
        free(*m);
    }

    *m = NULL;

    /* BRUITAGES */
    if(*b != NULL)
    {
        Mix_FreeChunk((*b) -> treasure);
        Mix_FreeChunk((*b) -> dash);
        Mix_FreeChunk((*b) -> hit);
        Mix_FreeChunk((*b) -> mort);
        Mix_FreeChunk((*b) -> menu_selection);
        Mix_FreeChunk((*b) -> swoop);
        Mix_FreeChunk((*b) -> tir);

        free(*b);
    }
    *b = NULL;
}


