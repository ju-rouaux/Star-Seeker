/**
 * \file
 * \brief Module de chargement d'un niveau en structure interprétable pour notre moteur de rendu. 
 * (Des optimisations doivent être faites)
 * \author Julien
 */

#include <stdio.h>
#include <stdlib.h>
#include <niveau.h>

void lierSalles(t_niveau * niveau)
{
    int hauteur, largeur, id_courant;
    for(int i = 0; i < niveau->h; i++)
    {
        for(int j = 0; j < niveau->l; j++)
        {
            hauteur = i * niveau->l;
            largeur = j;
            id_courant = niveau->salles[hauteur + largeur]->id_salle;
            
            if((hauteur-l) > 0 ) //Vérification des limites
            {
                if(niveau->salles[hauteur-l + largeur]->id_salle == id_courant) //Vérifier si la salle du dessus a le même id
                {

                }
            }
            if((largeur-1) > 0)
            {
                if(niveau->salles[hauteur + largeur-1]) //Vérifier si la salle d'à gauche a le même id
                {

                }
                else
                    niveau->salles
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
t_salle * creerSalle(int id_salle)
{
    t_salle * salle = malloc(sizeof(t_salle));
    if(salle == NULL)
    {
        printf("Impossible d'allouer la mémoire d'une salle.\n");
        return NULL;
    }

    for(int i = 0; i < NOMBRE_DE_PORTES; i++)
    {
        salle->portes[i] = NULL;
    }
    salle->complete = 0;
    salle->id_salle = id_salle;
}

/**
 * Libère la mémoire allouée pour une salle et mets son
 * pointeur à NULL
 * 
 * \param salle L'adresse du pointeur de la salle
 */
void detruireSalle(t_salle ** salle)
{
    free(*salle);
    salle = NULL;
}

//En cours d'ecriture
int chargerNiveau(FILE * fichier)
{
    //Dimensions
    int largeur;
    int hauteur;
    //Identifiant de la salle
    int id_salle;
    //Dernier identifiant le plus élevé
    int id_max;
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

    for(int i = 0; i < hauteur; i++)
    {
        for(int j = 0; j < largeur; j++)
        {
            fscanf(fichier, "%i", &id_salle);

            if(id_salle == 0) //S'il n'y a pas de salle
                niveau->salles[i*largeur + j] = NULL;
            
            else
            {
                if(id_salle > id_max) //Nouvelle salle
                {
                    id_max = id_salle;
                    salleCourante = malloc(sizeof(t_salle));
                    
                }
                else //Groupe de salle
                {

                }
            }
        }
    }
}

void detruireNiveau(t_niveau * niveau)
{

}