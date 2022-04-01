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

/**
 * \struct t_bool_param
 * \brief Valeurs booléennes
 */
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

    int volume_audio; /**< Volume audio du jeu */

    SDL_Scancode key_up; /**< Touche du clavier associé au déplacement vers le haut */
    SDL_Scancode key_down; /**< Touche du clavier associé au déplacement vers le bas */
    SDL_Scancode key_left; /**< Touche du clavier associé au déplacement vers la gauche */
    SDL_Scancode key_right; /**< Touche du clavier associé au déplacement vers la droite */

    SDL_Scancode attack_up; /**< Touche du clavier associé au lancement d'une attaque vers le haut */
    SDL_Scancode attack_down; /**< Touche du clavier associé au lancement d'une attaque vers le bas */
    SDL_Scancode attack_right; /**< Touche du clavier associé au lancement d'une attaque vers la droite */
    SDL_Scancode attack_left; /**< Touche du clavier associé au lancement d'une attaque vers la gauche */

    SDL_Scancode dash; /**< Touche du clavier associé au lancement d'une esquive */
    SDL_Scancode key_interaction; /**< Touche du clavier associé au lancement d'une interaction */
} t_parametres;

/**
 * \struct t_moteur
 * \brief Objet contenant les données nécessaires au rendu du jeu, aussi
 * pour la gestion des collisions.
 */
typedef struct s_moteur
{
    SDL_Window * window;/**< La fenetre du jeu*/
    SDL_Renderer * renderer;/**< Le renderer du jeu*/
    t_textures * textures;/**< Les textures du jeu */
    t_bruitages * bruitages;/**< Les bruitages du jeu*/
    t_musiques * musiques;/**< Les musiques du jeu*/
    unsigned int temps; /**< Temps au début d'une frame */
    unsigned int temps_precedent; /**< Temps au début de la frame précédente */

    char * galaxie; /**< Nom de la partie */
    t_camera * camera; /**< Caméra du jeu */
    t_niveau * niveau_charge; /**< Niveau actuellement chargé */
    t_liste * liste_entites; /**< Liste des entités rendues "vivantes" */
    int echelle; /**< Echelle du jeu, c'est à dire la taille des éléments */

    int window_width; /**< Largeur de la fenêtre */
    int window_height; /**< Hauteur de la fenêtre */

    t_parametres parametres;/**<Les différents paramètres*/
} t_moteur;


void regulerFPS(t_moteur * moteur);
t_moteur * chargerMoteur(unsigned int temps);
void detruireMoteur(t_moteur ** moteur);
void updateEchelle(t_moteur * moteur);


#endif // _JEU_MOTEUR_