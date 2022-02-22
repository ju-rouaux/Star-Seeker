/**
 * \file
 * \brief Module de chargement d'un niveau en structure interprétable pour le jeu.
 * 
 * \author Julien
 */

#include <stdio.h>
#include <stdlib.h>
#include <niveau.h>


//A faire
//static void chargerMonstres();
//static void chargerObstacles();
//static void chargerSalle(); //Appelle les 2 précédentes


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
 * \brief Charge le niveau dans une structure exploitable pour le jeu.
 * 
 * \param fichier Fichier depuis lequel charger le niveau (flux)
 * 
 * \return Le pointeur du niveau chargé, NULL si echec du chargement.
 */
t_niveau * chargerNiveau(FILE * fichier)
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

    //Lecture de la taille du niveau
    fscanf(fichier, "%i %i", &largeur, &hauteur);
    niveau->l = largeur;
    niveau->h = hauteur;

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

                niveau->salles[i*largeur + j] = salleCourante;
                salleCourante = NULL;
            }
        }
    }

    lierSalles(niveau);

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
