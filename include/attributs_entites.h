//--Comportement
float x; /**< Position en abscisse sur le niveau */
float y; /**< Position en ordonné sur le niveau */
int direction_vx; /** Vecteur direction de l'entité en x */
int direction_vy; /** Vecteur direction de l'entité en y */
float vitesse; /**< Vitesse exprimée en tile par secondes */
t_type_entite type; /** Type de l'entité */
//--Apparence
SDL_Texture * texture; /** Texture de l'entité */
float taille; /** Taille de l'entité proportionnellement à une tile */
t_animation * animation; /** L'animation de l'entité */
int id_animation; /** L'animation active sur l'entité */
//--Méthodes
int (*update)(t_moteur *, t_entite *); /** Actualise les données sur l'entité, retourne -1 si l'entité doit être détruit */
int (*dessiner)(t_moteur *, t_entite *); /** Affiche l'entité sur l'écran */