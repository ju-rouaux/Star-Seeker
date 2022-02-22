/**
 * \file niveau.c
 * \brief Module de chargement d'un niveau en structure interprétable pour le jeu.
 * 
 * \author Julien Rouaux
 */

#include <stdio.h>
#include <stdlib.h>
#include <moteur.h>
#include <niveau.h>

//A faire
//static void chargerMonstres();
//static void chargerObstacles();


/**
 * \brief Génère une structure dimensions de salle.
 * 
 * \param i Coordonnée en hauteur, de la salle d'origine dans la matrice niveau
 * \param j Coordonnée en largeur, de la salle d'origine dans la matrice niveau
 * 
 * \return Le pointeur des dimensions, NULL si echec.
 */
static t_dimensions_salle * creerDimensions(int i, int j)
{
    t_dimensions_salle * dimensions = malloc(sizeof(t_dimensions_salle));
    if(dimensions == NULL)
    {
        printf("Impossible d'allouer la mémoire d'une dimension de salle\n");
        return NULL;
    }

    dimensions->i = i;
    dimensions->j = j;
    dimensions->largeur = 1;
    dimensions->hauteur = 1;
    dimensions->nombre = 1;

    return dimensions;
}


/**
 * \brief Libère la mémoire seulement si plus aucune salle ne pointe sur la dimension et mets son pointeur à NULL.
 * 
 * C'est à dire si le champ nombre vaut 0.
 * 
 * \param dimensions L'adresse du pointeur de la dimension
 */
static void detruireDimensions(t_dimensions_salle ** dimensions)
{
    if(*dimensions != NULL && (*dimensions)->nombre == 0)
        free(*dimensions);

    *dimensions = NULL;
}


/**
 * \brief Remplie la matrice t_salle * portes[] du pointeur des salles voisines de chaque salles, 
 * et génère les dimensions de chaque salle.
 * 
 * Fonctionnement : 
 *      Pour chaque salle, si une voisine existe, il faut lier les portes des salles. 
 *      Sinon ne rien faire, pour que les portes pointent toujours vers NULL.
 *      Deux salles liées et ayant un même identifiant ne formeront qu'une salle.
 *      Si deux salles liées ne forment qu'une salle, actualiser les dimensions et
 *      faire pointer les salles sur la même structure dimensions.
 * 
 * \param niveau Le niveau dont il faut lier les salles
 * 
 * \return 0 si succès. Valeur négative si échec.
 */
static int lierSalles(t_niveau * niveau)
{   
    t_salle * salle_courante = NULL;
    int liee = 0; //Vrai si la salle courante a été liée

    for(int i = 0; i < niveau->h; i++)
    {
        for(int j = 0; j < niveau->l; j++)
        {
            salle_courante = niveau->salles[i*niveau->l + j];

            if(salle_courante != NULL) //Si la salle courante existe
            {
                if( i > 0 && //Pour éviter de sortir du haut de la matrice
                    niveau->salles[(i-1)*niveau->l + j] != NULL) //Si la salle du dessus existe
                {
                    //Lier porte haut salle courante à celle du bas de la salle du dessus
                    salle_courante->portes[UP] = niveau->salles[(i-1)*niveau->l + j];
                    niveau->salles[(i-1)*niveau->l + j]->portes[DOWN] = salle_courante;
                    //Lier les dimensions
                    if(salle_courante->id_salle == salle_courante->portes[UP]->id_salle)
                    {
                        liee++;
                        salle_courante->dimensions = salle_courante->portes[UP]->dimensions;
                        if(i > salle_courante->dimensions->i + salle_courante->dimensions->hauteur - 1)
                            (salle_courante->dimensions->hauteur)++;
                    }
                }

                if( j > 0 && //Pour éviter de sortir d'à gauche de la matrice
                    niveau->salles[i*niveau->l + (j-1)] != NULL) //Si la salle de gauche existe
                {
                    //Lier porte gauche salle courante à celle de droite de la salle de gauche
                    salle_courante->portes[LEFT] = niveau->salles[i*niveau->l + (j-1)];
                    niveau->salles[i*niveau->l + (j-1)]->portes[RIGHT] = salle_courante;
                    //Lier les dimensions
                    if(salle_courante->id_salle == salle_courante->portes[LEFT]->id_salle)
                    {
                        liee++;
                        salle_courante->dimensions = salle_courante->portes[LEFT]->dimensions;
                        if(j > salle_courante->dimensions->j + salle_courante->dimensions->largeur - 1)
                            (salle_courante->dimensions->largeur)++;
                    }
                }
                
                if( !liee )
                {
                   salle_courante->dimensions = creerDimensions(i, j);
                   if(salle_courante->dimensions == NULL)
                   {
                       printf("La liaison des salles a échoué\n");
                       return -1;
                   }
                } 
                else
                    (salle_courante->dimensions->nombre)++;

                liee = 0;
            }
        }
    }
    return 0;
}


/**
 * \brief Génère une structure salle et mets les pointeurs de porte à NULL.
 * 
 * \param id_salle L'identifiant de la salle
 * 
 * \return Le pointeur de la salle créée, NULL si échec.
 */
static t_salle * creerSalle(int id_salle)
{
    t_salle * salle = malloc(sizeof(t_salle));
    if(salle == NULL)
    {
        printf("Impossible d'allouer la mémoire d'une salle.\n");
        return NULL;
    }

    for(int i = 0; i < NOMBRE_DE_PORTES; i++)
        salle->portes[i] = NULL;

    salle->complete = 0;
    salle->id_salle = id_salle;
    salle->dimensions = NULL;

    return salle;
}


/**
 * \brief Libère la mémoire allouée pour une salle et mets son pointeur à NULL. 
 * 
 * \param salle L'adresse du pointeur de la salle
 */
static void detruireSalle(t_salle ** salle)
{
    if(*salle != NULL)
    {
        ((*salle)->dimensions->nombre)--; //Nombre vaut ainsi 0 si c'est la dernière salle
        detruireDimensions(&(*salle)->dimensions);
        free((*salle)->dimensions);
        free(*salle);
    }
    *salle = NULL;
}


/**
 * \brief Charge le niveau dans une structure exploitable pour le jeu et retourne à
 * travers les paramètres les couleurs du thème du niveau.
 * 
 * \param fichier Fichier depuis lequel charger le niveau (flux)
 * \param r Nuance de rouge du rendu du niveau
 * \param g Nuance de vert du rendu du niveau
 * \param b Nuance de bleu du rendu du niveau
 * 
 * \return Le pointeur du niveau chargé, NULL si echec du chargement.
 */
t_niveau * chargerNiveau(FILE * fichier, int * r, int * g, int * b)
{
    //Dimensions du niveau
    int largeur;
    int hauteur;

    //Identifiant de salle
    int id_salle;

    t_salle * salleCourante = NULL;
    t_niveau * niveau = malloc(sizeof(t_niveau));

    if(niveau == NULL)
    {
        printf("Impossible d'allouer la mémoire d'un niveau.\n");
        return NULL;
    }

    //Lecture des couleurs du niveau
    fscanf(fichier, "%i %i %i", r, g, b);

    //Lecture de la taille du niveau
    fscanf(fichier, "%i %i", &largeur, &hauteur);
    niveau->l = largeur;
    niveau->h = hauteur;

    niveau->salle_chargee = NULL;

    niveau->salles = malloc(sizeof(t_salle*)*hauteur*largeur); //Allouer l'array de pointeurs
    if(niveau->salles == NULL)
    {
        printf("Impossible d'allouer la mémoire pour la matrice de salle.\n");
        return NULL;
    }

    for(int i = 0; i < hauteur; i++)
    {
        for(int j = 0; j < largeur; j++)
        {
            fscanf(fichier, "%i", &id_salle);

            if(feof(fichier)) //Si on est déjà à la fin du fichier, ne rien charger de particulier
                id_salle = 0;

            if(id_salle == 0) //S'il n'y a pas de salle
               niveau->salles[i*largeur + j] = NULL;
            else
            {
                salleCourante = creerSalle(id_salle);
                if(salleCourante == NULL)
                {
                    printf("Impossible de charger le niveau.\n");
                    return NULL;
                }
                //chargerMonstres();
                //chargerObstacles();
                
                if(id_salle == -1 && niveau->salle_chargee == NULL) //Si c'est la salle où l'on commence
                    niveau->salle_chargee = salleCourante;

                niveau->salles[i*largeur + j] = salleCourante;
                salleCourante = NULL;
            }
        }
    }

    if(niveau->salle_chargee == NULL)
    {
        printf("Impossible de trouver le départ du niveau.\n");
        return NULL;
    }
    
    lierSalles(niveau);
    niveau->i_charge = niveau->salle_chargee->dimensions->i;
    niveau->j_charge = niveau->salle_chargee->dimensions->j;

    niveau->collisions = NULL;
    niveau->taille_collisions = 0;

    return niveau;
}

/**
 * \brief Libère la mémoire allouée pour un niveau et mets son pointeur à NULL.
 * 
 * \param niveau L'adresse du pointeur du niveau
 */
void detruireNiveau(t_niveau ** niveau)
{
    if(*niveau != NULL)
    {
        for(int i = 0; i < (*niveau)->h; i++)
            for(int j = 0; j < (*niveau)->l; j++)
                if((*niveau)->salles[i*(*niveau)->l + j] != NULL)
                    detruireSalle(&(*niveau)->salles[i*(*niveau)->l + j]);
        free((*niveau)->salles);
        free(*niveau);
    }

    *niveau = NULL;
}

/**
 * \brief Lance un niveau
 * 
 * Les couleurs du niveau sont aussi chargées
 * 
 * 
 */
int lancerNiveau(FILE * fichier, t_moteur * moteur)
{
    int r, g, b;

    t_niveau * niveau = chargerNiveau(fichier, &r, &g, &b);

    if(niveau == NULL)
    {
        printf("Le niveau n'a pas pu être lancé\n");
        return -1;
    }

    if(SDL_SetTextureColorMod(moteur->textures->map, r, g, b) != 0)
        printf("Note : la couleur du niveau n'a pas pu être chargé\n");

    moteur->niveau_charge = niveau;

    return 0;
}

/**
 * \brief Libère la mémoire allouée pour le niveau. Actuellement cette fonction est identique à void detruireNiveau(t_niveau **niveau).
 * 
 * Opération à réaliser lorsque l'on quitte un niveau.
 * Des opérations supplémentaires (notamment animations) peuvent être réalisées avant la destruction.
 * 
 * \param niveau Le niveau à fermer
 */
void arreterNiveau(t_niveau ** niveau)
{
    //D'autres opérations ici si nécéssaire


    detruireNiveau(niveau);
}

/**
 * \brief Actualise la salle chargée du niveau selon l'activité du joueur
 * (lorsqu'il change de salle par exemple).
 * 
 * Calcule les coordonnées des bords de la salle et change la salle courante du niveau si le joueur
 * dépasse ces limites.
 * 
 * \param niveau Le niveau chargé
 * \param joueur Le joueur
 * \param echelle L'échelle du rendu
 */
void updateNiveau(t_niveau * niveau, float j_x, float j_y, int echelle)
{
    int limite_cote_gauche = niveau->j_charge*echelle*NB_TILE_LARGEUR;
    int limite_cote_droit = niveau->j_charge*echelle*NB_TILE_LARGEUR + NB_TILE_LARGEUR*echelle;
    int limite_cote_haut = niveau->i_charge*echelle*NB_TILE_HAUTEUR;
    int limite_cote_bas = niveau->i_charge*echelle*NB_TILE_HAUTEUR + NB_TILE_HAUTEUR*echelle;

    if(j_x*echelle > limite_cote_droit) //Dépassement à droite avec un demi bloc de marge
    {

        if(niveau->salle_chargee->portes[RIGHT] != NULL)
        {
            niveau->salle_chargee = niveau->salle_chargee->portes[RIGHT];
            (niveau->j_charge)++;
        }
    }

    else if(j_x*echelle < limite_cote_gauche) //Dépassement à gauche avec un demi bloc de marge
    {

        if(niveau->salle_chargee->portes[LEFT] != NULL)
        {
            niveau->salle_chargee = niveau->salle_chargee->portes[LEFT];
            (niveau->j_charge)--;
        }
    }

    if(j_y*echelle > limite_cote_bas) //Dépassement en bas avec un demi bloc de marge
    {
        if(niveau->salle_chargee->portes[DOWN] != NULL)
        {
            niveau->salle_chargee = niveau->salle_chargee->portes[DOWN];
            (niveau->i_charge)++;
        }
    }

    else if(j_y*echelle < limite_cote_haut) //Dépassement en haut avec un demi bloc de marge
    {
        if(niveau->salle_chargee->portes[UP] != NULL)
        {
            niveau->salle_chargee = niveau->salle_chargee->portes[UP];
            (niveau->i_charge)--;
        }
    }      
}