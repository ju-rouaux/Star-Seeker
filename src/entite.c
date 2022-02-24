/**
 * \file entite.c
 * 
 * \brief Module de manipulation des entites.
 * 
 * Pour faciliter le développement, ce module permet l'affichage, l'animation et
 * le déplacement automatique d'une entité selon ses paramètres.
 * 
 * \author Julien Rouaux
 */


#include <math.h> //Pour la normalisation de vecteurs
#include <SDL2/SDL.h>
#include <moteur.h>
#include <textures.h> //Pour découper une texture
#include <animation.h>
#include <entite.h>
#include <liste.h>
#include <niveau.h>


/**
 * \brief Dessine l'entité à ses coordonnées, tout en gérant son animation s'il en possède une.
 * 
 * \param moteur Structure moteur du jeu
 * \param entite L'entité à afficher
 * 
 * \return 0 si succès, sinon une valeur négative (SDL_Error() pour connaitre l'erreur).
 */
int dessinerEntite(t_moteur * moteur, t_entite * entite)
{
    int indice_texture = 0;
    SDL_Rect source;

    entite->hitbox.h = moteur->echelle * entite->taille;
    entite->hitbox.w = moteur->echelle * entite->taille;
    
    //Ainsi l'entité apparait avec le point de ses coordonnées au centre en bas de l'image
    entite->hitbox.x = moteur->echelle*(entite->x - moteur->camera->x) - entite->hitbox.w / 2;
    entite->hitbox.y = moteur->echelle*(entite->y - moteur->camera->y) - entite->hitbox.h;

    if(entite->animation != NULL) //Si l'entité est animé
    {
        updateAnimation(entite->animation, moteur->temps);
        indice_texture = entite->animation->indice_texture;
    }

    splitTexture(&source, indice_texture, entite->id_animation);

    return SDL_RenderCopy(moteur->renderer, entite->texture, &source, &entite->hitbox);
}


/**
 * \brief Déplace l'entité selon sa direction et sa vitesse. L'entité n'est pas avancé si
 * sa future position entraine une collision avec un mur.
 * 
 * La fonction teste si une collision survient en traitant les deux axes de déplacement séparément
 * afin que l'entité puisse glisser contre le mur s'il se dirige en diagonale au lieu de se voir
 * annuler son déplacement.
 * 
 * \param moteur Structure moteur du jeu
 * \param entite L'entité à afficher
 * 
 * \return -1 si collision, sinon 0.
 */
int deplacerEntite(const t_moteur * moteur, t_entite * entite)
{
    int i; //Variable pour parcourir le tableau des collisions
    int collision = 0; //Faux, vrai si une collision occure 
    
    //Distance à parcourir
    float distance = entite->vitesse * (moteur->temps - moteur->temps_precedent) / 1000;
    
    //Normalisation du vecteur direction en divisant par sqrt(x^2 + y^2)
    float normalisation = sqrt(pow(entite->direction_vx, 2) + pow(entite->direction_vy, 2));
    float futur_x = entite->x + distance * (entite->direction_vx / normalisation);
    float futur_y = entite->y + distance * (entite->direction_vy / normalisation);
    
    //Définir la taille de la hitbox
    SDL_Rect hitbox; //Zone aux pieds de l'entité, aire où il entre en collision avec le mur
    hitbox.w = entite->taille/3 * moteur->echelle;
    hitbox.h = entite->taille/2 * moteur->echelle;

    //Test d'une collision en axe x
    hitbox.x = moteur->echelle * (futur_x - moteur->camera->x) - hitbox.w / 2;
    hitbox.y = moteur->echelle * (entite->y - moteur->camera->y) - 9*hitbox.h/10;
    i = 0;
    while(i < moteur->niveau_charge->taille_collisions && !SDL_HasIntersection(&hitbox,&moteur->niveau_charge->collisions[i]))
        i++;

    if(i != moteur->niveau_charge->taille_collisions)
        collision = -1; //Vrai
    else
        entite->x = futur_x;

    //Test d'une collision en axe y
    hitbox.x = moteur->echelle * (entite->x - moteur->camera->x) - hitbox.w / 2;
    hitbox.y = moteur->echelle * (futur_y - moteur->camera->y) - 9*hitbox.h/10;
    i = 0;
    while(i < moteur->niveau_charge->taille_collisions && !SDL_HasIntersection(&hitbox,&moteur->niveau_charge->collisions[i]))
        i++;

    if(i != moteur->niveau_charge->taille_collisions)
        collision = -1; //Vrai
    else
        entite->y = futur_y;

    return collision;
}