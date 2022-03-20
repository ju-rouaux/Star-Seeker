/**
 * 
 * 
 */

#include <entite.h>
#include <monstre.h>

int genererEntites(float indice_difficulte, int x_orig_salle, int y_orig_salle, t_entite *** liste_entites, int * nb_entites)
{   
    //générer un nombre d'entité selon difficulté
    *nb_entites = 3;

    //allouer liste les entites
    *liste_entites = malloc(sizeof(t_entite*) * (*nb_entites));

    //générer entités
    for(int i = 0; i < *nb_entites; i++)
        (*liste_entites)[i] = (t_entite*) creerMonstre(x_orig_salle + 6, y_orig_salle + 4, 0, 2, 1.5, DEMO, STATIQUE);

    return 0;
}