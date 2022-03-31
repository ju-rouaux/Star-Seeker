
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

/**
 * \struct t_bruitages
 * \brief Modelise les bruitages
 * 
 */
typedef struct{

    Mix_Chunk  * treasure;/*son du trésor*/
    Mix_Chunk  * dash;/*son du dash*/
    Mix_Chunk  * hit;/*son lorsqu'une entité est touchée*/
    Mix_Chunk  * mort;/*son lors de la mort*/
    Mix_Chunk  * menu_selection;/*son lors de la selection dans le menu*/
    Mix_Chunk  * swoop;/*son du swoop*/
    Mix_Chunk  * tir;/*son du tir*/

} t_bruitages;

/**
 * \struct t_musiques
 * \brief Modelise les musiques
 * 
 */
typedef struct{

    Mix_Music * menu_principal; /**<musique dans le menu principal*/
    Mix_Music * ambiant;/**<musique ambiante*/

} t_musiques;

int chargerAudio(int volume, t_musiques ** musiques, t_bruitages ** bruitages);
void detruireAudio(t_musiques ** m, t_bruitages ** b);
void changerVolume(int volume);

#endif // _JEU_AUDIO_
