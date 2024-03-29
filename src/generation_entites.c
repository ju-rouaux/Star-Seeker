/**
 * \file generation_entites.c
 * 
 * \brief Module générant les entités des salles d'un niveau.
 * 
 * \author Julien Rouaux & Guillaume Richard
 */


#include <entite.h>
#include <monstre.h>
#include <generation_niveau.h>
#include <interaction.h>
#include <generation_entites.h>
#include <outils.h>


/**
 * \brief Genere les entités, les objets au sol (armes et vie)
 * 
 * \param indice_difficulte Xp faisant varier la quantité et la difficulté des monstres par salles
 * \param x_orig_salle origine x de la salle
 * \param y_orig_salle origine y de la salle
 * \param liste_entites adresse de la structure
 * \param nb_entites nombre d'entités
 * \return booleen, 0 si succes, negatif si echec
 */
static int genererEntitesSalle(int indice_difficulte, int x_orig_salle, int y_orig_salle, t_entite *** liste_entites, int * nb_entites)
{
    int i = 0;

    //générer un nombre d'entité selon difficulté
    *nb_entites = indice_difficulte * 0.6;
    if(*nb_entites < 1)
        *nb_entites = 1;
    else if(*nb_entites >= 4)
        *nb_entites = 4;
    
    //allouer liste les entites
    *liste_entites = malloc(sizeof(t_entite*) * (*nb_entites));
    if(*liste_entites == NULL)
    {
        printf("Erreur d'allocation de la liste des entités\n");
        return -1;
    }
    
    e_nom_attaque attaque_alea;
    data_inter data;
    float x_alea;
    float y_alea;

    //generation aleatoire de la vie
    if(de(10) == 1){
        x_alea = rand() % (NB_TILE_LARGEUR - 1) + x_orig_salle + 1;
        y_alea = rand() % (NB_TILE_HAUTEUR - 1) + y_orig_salle + 1;

        data.nb_pv = de(2) * 2;
        (*liste_entites)[i] = (t_entite*) creerInteraction(VIE, x_alea, y_alea, data);
        i++;
    }

    //generation aleatoire d'une arme
    if(de(20) == 1 && i < *nb_entites)
    {
        x_alea = rand() % (NB_TILE_LARGEUR - 1) + x_orig_salle + 1;
        y_alea = rand() % (NB_TILE_HAUTEUR - 1) + y_orig_salle + 1;

        do
        {
            data.attaque = de(NB_ATTAQUE)-1;
        }while(data.attaque == A_TOURNER); //attaque a exclure pour le joueur

        (*liste_entites)[i] = (t_entite*) creerInteraction(ARME, x_alea, y_alea, data);
        i++;
    }

    //générer monstres
    for(; i < *nb_entites; i++){
        x_alea = rand() % (NB_TILE_LARGEUR - 3) + x_orig_salle + 2;
        y_alea = rand() % (NB_TILE_HAUTEUR - 2) + y_orig_salle + 2;
        attaque_alea = rand() % (NB_ATTAQUE - 1);

        //Selon les attaques, la taille du monstre change
        switch(attaque_alea){
            case A_DEFAUT :(*liste_entites)[i] = (t_entite*) creerMonstre(x_alea, y_alea, 2, 1 + (indice_difficulte * 0.6), 1, attaque_alea, de(2)-1);break;
            case A_DEFAUT_LARGE : (*liste_entites)[i] = (t_entite*) creerMonstre(x_alea, y_alea, 2, 2 + (indice_difficulte * 0.6), 1.1, attaque_alea, de(2)-1);break;
            case A_FEU_SIMPLE : (*liste_entites)[i] = (t_entite*) creerMonstre(x_alea, y_alea, 2, 1 + (indice_difficulte * 0.6), 1.3, attaque_alea, de(2)-1);break;
            case A_FEU : (*liste_entites)[i] = (t_entite*) creerMonstre(x_alea, y_alea, 2, 1 + (indice_difficulte * 0.6), 1.4, attaque_alea, de(2)-1);break;
            case A_SNIPER : (*liste_entites)[i] = (t_entite*) creerMonstre(x_alea, y_alea, 2, 1 + (indice_difficulte * 0.6), 0.8, attaque_alea, de(2)-1);break;
            case A_SNIPER_3 : (*liste_entites)[i] = (t_entite*) creerMonstre(x_alea, y_alea, 2, 1 + (indice_difficulte * 0.6), 0.9, attaque_alea, de(2)-1);break;
            case A_360 : (*liste_entites)[i] = (t_entite*) creerMonstre(x_alea, y_alea, 2, 2 + (indice_difficulte * 0.6), 1.1, attaque_alea, de(2)-1);break;
            case A_360_MORE : (*liste_entites)[i] = (t_entite*) creerMonstre(x_alea, y_alea, 2, 2 + (indice_difficulte * 0.6), 1.3, attaque_alea, de(2)-1);break;
            case A_TOURNER : (*liste_entites)[i] = (t_entite*) creerMonstre(x_alea, y_alea, 2, 3 + (indice_difficulte * 0.6), 1.5, attaque_alea, de(2)-1);break;
            default : printf("Erreur de l'attaque d'un monstre, attaque_alea : %d\n",attaque_alea);return -1;
        }
    }
    return 0;
}


/**
 * \brief Libère la mémoire allouée aux infos sur les entités d'une salle en détruisant les entités contenues.
 * 
 * \param infos L'adresse de la structure
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
                    (*infos)->entites[i]->detruire(&((*infos)->entites[i]));
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
 * \brief A partir de l'indice de diffuculté, et de la matrice du niveau, générer une structure infos_entites par salle, contenant la liste.
 * des entités de la salle.
 * 
 * \param indice_difficulte Calculée a partir de l'xp du joueur, faisant varier la quantité et la difficulté des monstres par salles
 * \param matrice_n Matrice du niveau
 * \param h_mat Hauteur de la matrice
 * \param l_mat Largeur de la matrice
 * \param infos_entites Retour de la liste des infos_entites
 * \param nombre_infos Retour du nombre d'éléments dans la liste des infos_entites
 * \param id_salle_dep Id de la salle de départ
 * 
 * \return 0 si succès, valeur négative si échec.
 */
int genererEntites(int indice_difficulte, int * matrice_n, int h_mat, int l_mat, t_info_entites *** infos_entites, int * nombre_infos, int id_salle_dep)
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
            if(matrice_n[i*l_mat + j] != 0 && matrice_n[i*l_mat + j] != id_salle_dep) //Si salle, et éviter salle où l'on apparait
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