#ifndef _JEU_MOTEUR_
#define _JEU_MOTEUR_

#include <SDL2/SDL.h>
#include <textures.h>
#include <camera.h>

#define NB_FPS 60
#define TEMPS_POUR_CHAQUE_SECONDE ((float)1000/NB_FPS)

#define NB_FRAME_POUR_ANIMATION 60 /**< Le temps que mets le jeu à changer de salle */
#define DUREE_TRANSITION 1000
#define VITESSE_TRANSITION 10 /** Vitesse d'une transition exprimée en tile par secondes */

#define NOMBRE_DE_PORTES 4 /**< Nombre de portes d'une salle (une par mur) */
#define NB_TILE_LARGEUR 13 /**< Surface au sol en largeur */
#define NB_TILE_HAUTEUR 7 /**< Surface au sol en hauteur */

/**
 * \struct t_moteur
 * \brief Objet contenant les données nécéssaires au rendu du jeu
 */
typedef struct
{
    SDL_Window * window;
    SDL_Renderer * renderer;
    t_textures * textures;
    t_camera * camera;
    unsigned int temps;
    unsigned int temps_precedent;

    SDL_Rect * collisions; /**< Tableau des zones non accessibles au joueur  */
    int taille_collisions; /**< Taille du tableau de collisions */
} t_moteur;

t_moteur * chargerMoteur(unsigned int temps);
void detruireMoteur(t_moteur ** moteur);

#endif // _JEU_MOTEUR_