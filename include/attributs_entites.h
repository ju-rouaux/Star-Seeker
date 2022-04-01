/**
 * \file attributs_entites.h
 * 
 * \brief Fichier à inclure dans une structure héritant des attributs des entités.
 * 
 * \author Julien Rouaux
 */

float x; /**< Position en abscisse sur le niveau (renseignée) */
float y; /**< Position en ordonné sur le niveau (renseignée) */
float direction_vx; /**< Vecteur direction de l'entité en x (1 par défaut) */
float direction_vy; /**< Vecteur direction de l'entité en y (0 par défaut) */
float vitesse; /**< Vitesse exprimée en tile par secondes (0 par défaut) */
e_type_entite type; /**< Type de l'entité (AUCUN par défaut)*/

SDL_Rect hitbox; /** Zone où l'entité est présent physiquement. Elle est actualisée à l'échelle du jeu lorsque l'entité est dessinée. (0 par défaut) */

SDL_Texture * texture; /**< Texture de l'entité (renseignée) */
float taille; /**< Taille de l'entité proportionnellement à une tile (1 par défaut) */
t_animation * animation; /**< L'animation de l'entité (NULL par défaut)*/
int id_animation; /**< L'animation active sur l'entité (ligne du tileset si pas d'animaion, 0 par défaut) */

int (*update)(t_moteur *, t_entite *, float, float); /**< Actualise les données sur l'entité, retourne -1 si l'entité doit être détruite (NULL par défaut) */
int (*dessiner)(t_moteur *, t_entite *); /**< Dessine l'entité sur l'écran (desinnerEntite par défaut) */
void (*detruire)(t_entite**); /**< Destruction de l'entité (detruireEntite par défaut) */