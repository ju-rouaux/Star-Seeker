/**
 * \file
 * \brief Module de chargement d'un niveau en structure interprétable pour notre moteur de rendu. 
 * 
 * \author Julien
 */

#include <stdio.h>
#include <stdlib.h>
#include <niveau.h>


/**
 * Remplie la matrice t_salle * portes[] du pointeur des salles voisines de chaque salles. 
 * Fonctionnement : 
 *      Pour chaque salle, si une voisine existe, il faut lier les portes des salles. 
 *      Sinon ne rien faire, pour que les portes pointent toujours vers NULL.
 *      Deux salles liées et ayant un même identifiant ne formeront qu'une salle.
 * 
 *  \param niveau Le niveau dont il faut lier les salles
 */
static void lierSalles(t_niveau * niveau)
{   
    for(int i = 0; i < niveau->h; i++)
    {
        for(int j = 0; j < niveau->l; j++)
        {
            if(niveau->salles[i*niveau->l + j] != NULL) //Si la salle courante existe
            {
                if( i > 0 && //Pour éviter de sortir du haut de la matrice
                    niveau->salles[(i-1)*niveau->l + j] != NULL) //Si la salle du dessus existe
                {
                    //Lier porte haut salle courante à celle du bas salle du dessus
                    niveau->salles[i*niveau->l + j]->portes[UP] = niveau->salles[(i-1)*niveau->l + j];
                    niveau->salles[(i-1)*niveau->l + j]->portes[DOWN] = niveau->salles[i*niveau->l + j];
                }

                if( j > 0 && //Pour éviter de sortir d'à gauche de la matrice
                    niveau->salles[i*niveau->l + (j-1)] != NULL) //Si la salle de gauche existe
                {
                    //Lier porte gauche salle courante à celle de droite salle de gauche
                    niveau->salles[i*niveau->l + j]->portes[LEFT] = niveau->salles[i*niveau->l + (j-1)];
                    niveau->salles[i*niveau->l + (j-1)]->portes[RIGHT] = niveau->salles[i*niveau->l + j];
                }
            }
        }
    }
}


/**
 * Génère une structure salle et mets les pointeurs de son groupe 
 * à NULL.
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

    return salle;
}


/**
 * Libère la mémoire allouée pour une salle et mets son 
 * pointeur à NULL. 
 * 
 * \param salle L'adresse du pointeur de la salle
 */
static void detruireSalle(t_salle ** salle)
{
    if(*salle != NULL)
        free(*salle);
    salle = NULL;
}

//A faire
//static void chargerMonstres();
//static void chargerObstacles();
//static void chargerSalle(); //Appelle les 2 précédentes


/**
 * Charge le niveau dans une structure exploitable pour le jeu.
 * 
 * \param fichier Fichier depuis lequel charger le niveau
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

    t_niveau * niveau = malloc(sizeof(t_niveau));
    t_salle * salleCourante = NULL;

    if(niveau == NULL)
    {
        printf("Impossible d'allouer la mémoire d'un niveau.\n");
        return NULL;
    }

    //Lecture de la taille du niveau
    fscanf(fichier, "%i %i", &largeur, &hauteur);
    printf("l : %i / h : %i\n", largeur, hauteur);

    niveau->l = largeur;
    niveau->h = hauteur;
    niveau->salles = malloc(sizeof(t_salle*)*hauteur*largeur); //Allouer l'array de pointeurs

    for(int i = 0; i < hauteur; i++)
    {
        for(int j = 0; j < largeur; j++)
        {
            fscanf(fichier, "%i", &id_salle);

            if(feof(fichier)) //En cas d'erreur du fichier, ne rien charger de particulier
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
 * Libère la mémoire allouée pour un niveau et mets son 
 * pointeur à NULL
 * 
 * \param niveau L'adresse du pointeur du niveau
 */
void detruireNiveau(t_niveau ** niveau)
{
    if(*niveau != NULL)
    {
        for(int i = 0; i < (*niveau)->h; i++)
            for(int j = 0; j < (*niveau)->l; j++)
                detruireSalle(&(*niveau)->salles[i*(*niveau)->l + j]); //La fonction appelée se charge de vérifier si le pointeur n'est pas NULL
        free((*niveau)->salles);
        free(*niveau);
    }
    niveau = NULL;
}