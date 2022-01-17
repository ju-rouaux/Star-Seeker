#include <stdio.h>
#include <stdlib.h>
#include <niveau.h>

//En cours d'ecriture
int chargerNiveau(FILE * fichier)
{
    int largeur;
    int hauteur;
    int id_salle;
    int id_max;
    t_niveau * niveau;

    //Lecture de la taille du niveau
    fscanf(fichier, "%i %i", &largeur, &hauteur);
    
    niveau = malloc(sizeof(t_niveau) * largeur * hauteur);
    niveau->l = largeur;
    niveau->h = hauteur;

    for(int i = 0; i < hauteur; i++)
    {
        for(int j = 0; j < largeur; j++)
        {
            fscanf(fichier, "%i", id_salle);
            if(id_salle == 0)
                niveau->salles[i][j] = NULL;
            else
            {
                if(id_salle > id_max) //Nouvelle salle
                {
                    id_max = id_salle;
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