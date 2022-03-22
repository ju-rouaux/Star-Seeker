/**
 * 
 * 
 */

#include <entite.h>
#include <monstre.h>
#include <generation_niveau.h>

/**
 * 
 * 
 * 
 * 
 */
static int genererEntitesSalle(float indice_difficulte, int x_orig_salle, int y_orig_salle, t_entite *** liste_entites, int * nb_entites)
{   
    //générer un nombre d'entité selon difficulté
    *nb_entites = 1;

    //allouer liste les entites
    *liste_entites = malloc(sizeof(t_entite*) * (*nb_entites));

    //générer entités
    for(int i = 0; i < *nb_entites; i++)
        (*liste_entites)[i] = (t_entite*) creerMonstre(x_orig_salle + 6, y_orig_salle + 4, 2, 2, 1.5, DEMO, STATIQUE);

    return 0;
}

/**
 * 
 * 
 * 
 * 
 */
void detruireInfosEntites(t_info_entites ** infos)
{
    if(*infos != NULL)
    {
        if((*infos)->entites != NULL)
        {
            for(int i = 0; i < (*infos)->nb_entites; i++)
            {  
                if((*infos)->entites[i] != NULL)
                    detruireEntite(&((*infos)->entites[i]));
                (*infos)->entites[i] = NULL;
            }
            free((*infos)->entites);
            (*infos)->entites = NULL;
        }
        free(*infos);
    }
    *infos = NULL;
}

/**
 * 
 * 
 * 
 */
int genererEntites(int indice_difficulte, int * matrice_n, int h_mat, int l_mat, t_info_entites *** infos_entites, int * nombre_infos)
{
    int nb_infos = 0;

    //Dans le pire des cas, autant de salles que d'emplacements dispo
    t_info_entites ** infos = malloc(sizeof(t_info_entites*) * h_mat * l_mat);
    if(infos == NULL)
    {
        printf("Impossible d'allouer mémoire pour générer entites\n");
        return -1;
    }

    int k;
    for(int i = 0; i < h_mat; i++)
    {
        for(int j = 0; j < l_mat; j++)
        {
            if(matrice_n[i*l_mat + j] != 0) //Si salle
            {
                //Vérifier qu'on n'a pas déjà des données pour cet identifiant
                for(k = 0; k < nb_infos && infos[k]->id_salle != matrice_n[i*l_mat + j]; k++);
                if(k == nb_infos) //Non trouvé
                {
                    infos[k] = malloc(sizeof(t_info_entites)); //Générer les entites
                    if(infos[k] != NULL)
                    {
                        infos[k]->id_salle = matrice_n[i*l_mat + j];
                        if(genererEntitesSalle(indice_difficulte, j*NB_TILE_LARGEUR, i*NB_TILE_HAUTEUR, &infos[k]->entites, &infos[k]->nb_entites) == 0)
                            nb_infos++;
                        else
                        {
                            free(infos[k]);
                            infos[k] = NULL;
                        }
                    }
                }
                else //Trouvé
                {
                    t_info_entites temp;
                    if(genererEntitesSalle(indice_difficulte, j*NB_TILE_LARGEUR, i*NB_TILE_HAUTEUR, &temp.entites, &temp.nb_entites) == 0)
                    {
                        //Ajouter de la place pour les nouvelles entités
                        infos[k]->entites = realloc(infos[k]->entites, infos[k]->nb_entites*sizeof(t_entite*) + temp.nb_entites*sizeof(t_entite*));
                        
                        //Copier les entites
                        for(int l = 0; l < temp.nb_entites; l++)
                            infos[k]->entites[infos[k]->nb_entites + l] = temp.entites[l];

                        infos[k]->nb_entites += temp.nb_entites;
                    }
                }
            }
        }
    }

    infos = realloc(infos, sizeof(t_info_entites*) * nb_infos); //Virer les données innutiles
    *infos_entites = infos;
    *nombre_infos = nb_infos;

    return 0;
}