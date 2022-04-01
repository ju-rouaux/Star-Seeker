/**
 * \file generation_entites.h
 * 
 * \brief Module générant les entités des salles d'un niveau.
 * 
 * \author Julien Rouaux & Guillaume Richard
 */

#ifndef _JEU_GENERATION_ENTITES_
#define _JEU_GENERATION_ENTITES_

#include <entite.h>

/**
 * \struct t_info_entites
 * \brief Liste des entités présentes dans une salle
 */
typedef struct
{
    int id_salle; /**< Id de la salle propriétaire de ces données */
    int nb_entites; /**< Le nombre d'entités de la liste */
    t_entite ** entites; /**< La liste des entités */
} t_info_entites;

int genererEntites(int indice_difficulte, int * matrice_n, int h_mat, int l_mat, t_info_entites *** infos_entites, int * nombre_infos, int id_salle_dep);
void detruireInfosEntites(t_info_entites ** infos);

#endif //_JEU_GENERATION_ENTITES_