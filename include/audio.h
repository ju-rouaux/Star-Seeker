
/**
 * \file audio.h
 * 
 * \brief Librairie de audio.h
 *
 * \author Camille REMOUÉ
 *  
 */





#ifndef _JEU_AUDIO_
#define _JEU_AUDIO_


#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct{

    Mix_Music * boiling;
    Mix_Music * treasure;

} t_bruitages;


typedef struct{

    Mix_Music * menu_principal;


} t_musiques;

int chargerAudio(int volume, t_musiques ** musiques, t_bruitages ** bruitages);
void detruireAudio(t_musiques ** m, t_bruitages ** b);

#endif // _JEU_AUDIO_
