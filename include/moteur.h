/**
 * \file moteur.h
 * \brief Module de chargement d'une fenêtre, du renderer, des textures, d'une caméra
 * et les retournes dans une structure.
 * 
 * Le moteur contient aussi les collisions 
 * 
 * \author Julien Rouaux
 */

#ifndef _JEU_MOTEUR_
#define _JEU_MOTEUR_

#include <SDL2/SDL.h>
#include <textures.h>
#include <audio.h>
#include <camera.h>

typedef struct s_liste t_liste;

#define NB_FPS 60 /**< Nombre de frames par secondes du jeu */
#define TEMPS_POUR_CHAQUE_SECONDE ((float)1000/NB_FPS)

#define VITESSE_TRANSITION 10 /**< Vitesse d'une transition exprimée en tile par secondes */

#define NOMBRE_DE_PORTES 4 /**< Nombre de portes d'une salle (une par mur) */
#define NB_TILE_LARGEUR 13 /**< Surface au sol en largeur */
#define NB_TILE_HAUTEUR 7 /**< Surface au sol en hauteur */

typedef struct s_niveau t_niveau; 


typedef enum
{
    FAUX, VRAI
} t_bool_param;


/**
 * \struct t_parametres
 * \brief Structure contenant les paramètres techniques du jeu pouvant être changés par le joueur.
 */
typedef struct
{
    t_bool_param reset_sauvegarde_joueur; /**< Vrai si le jeu doit écraser la sauvegarde du joueur au lancement de la partie */
    int volume_audio; //(ou volume musique puis volume sons)
    SDL_Scancode key_up;
    SDL_Scancode key_down;
    SDL_Scancode key_left;
    SDL_Scancode key_right;
    SDL_Scancode key_projectile;
    SDL_Scancode key_interaction;

} t_parametres;

/**
 * \struct t_moteur
 * \brief Objet contenant les données nécessaires au rendu du jeu, aussi
 * pour la gestion des collisions.
 */
typedef struct s_moteur
{
    SDL_Window * window;
    SDL_Renderer * renderer;
    t_textures * textures;
    t_bruitages * bruitages;
    t_musiques * musiques;
    unsigned int temps; /**< Temps au début d'une frame */
    unsigned int temps_precedent; /** Temps au début de la frame précédente */

    char * galaxie; /** Nom de la partie */
    t_camera * camera; /** Caméra du jeu */
    t_niveau * niveau_charge; /** Niveau actuellement chargé */
    t_liste * liste_entites; /**< Liste des entités rendues "vivantes" */
    int echelle; /**< Echelle du jeu, c'est à dire la taille des éléments */

    int window_width; /**< Largeur de la fenêtre */
    int window_height; /**< Hauteur de la fenêtre */

    t_parametres parametres;
} t_moteur;


void regulerFPS(t_moteur * moteur);
t_moteur * chargerMoteur(unsigned int temps);
void detruireMoteur(t_moteur ** moteur);
void updateEchelle(t_moteur * moteur);


#endif // _JEU_MOTEUR_