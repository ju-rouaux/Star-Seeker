/**
 * \file sauvegarde.c
 * 
 * \brief Sauvegarde des structures du jeu pour permettre au joueur de continuer sa partie.
 * 
 * \author Guillaume Richard & Julien Rouaux
 */


#include <sauvegarde.h>

// OUTILS ---------------------------------------------------------------------------------------------

/**
 * \brief Verifie si le fichier existe et s'il n'est pas vide.
 *
 * \param file flux du fichier
 * 
 * \return la taille du fichier, donc 0 si vide ou inexistant
 */
static int file_empty(FILE * file)
{
    if(file == NULL)
        return 0;

    fseek(file, 0, SEEK_END);

    return ftell(file);
}

// SAUVEGARDE JOUEUR ---------------------------------------------------------------------------------------------

/**
 * \brief Charge le joueur de ses données de sauvegarde.
 * 
 * Lis la sauvegarde dans le fichier binaire et met a jour la structure t_joueur
 * 
 * \param joueur structure du joueur a charger depuis la sauvegarde
 * 
 * \return 0 si succès, valeur négative si echec.
 */
int chargerJoueur(t_joueur * joueur)
{
    FILE * fichier = fopen(filename_joueur, "rb");
    if (fichier == NULL)
    {
        fprintf(stderr, "Error opening file for player\n");
        return -1;
    }
    if(file_empty(fichier) == 0)
    {
        printf("Fichier de sauvegarde du joueur vide\n");
        fclose(fichier);
        return -1;
    }

    t_joueur * tmp = malloc(sizeof(t_joueur));
    if(tmp == NULL)
    {
        printf("L'allocation de mémoire temporaire pour le chargement du joueur a échoué\n");
        fclose(fichier);
        return -1;
    }

    if(fread(tmp, sizeof(t_joueur), 1, fichier) != 1)
    {
        printf("Erreur lors de la lecture du fichier du joueur\n");
        free(tmp);
        fclose(fichier);
        return -1;
    }

    joueur->x = tmp->x;
    joueur->y = tmp->y;
    joueur->direction_vx = tmp->direction_vx;
    joueur-> direction_vy = tmp->direction_vy;
    joueur->vitesse = tmp->vitesse;

    free(tmp);
    fclose (fichier);

    return 0;
}

/**
 * 
 * 
 * 
 * 
 */
int sauvegarderJoueur(t_joueur * joueur)
{
    FILE * fichier = fopen(filename_joueur, "wb");
    if(fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde du joueur\n");
        return -1;
    }

    if(fwrite(joueur, sizeof(t_joueur), 1, fichier) != 1)
    {
        printf("Erreur lors de l'écriture des donnees du joueur\n");
        fclose(fichier);
        return -1;
    }

    fclose(fichier);
}

// SAUVEGARDE PARTIE ---------------------------------------------------------------------------------------------

/**
 *
 * Remplie les champs en param
 * 
 */
static int chargerInfosNiveaux(FILE * fichier, niveau_informations_t *** infos_niveaux, int * nb_niveaux)
{
    niveau_informations_t ** tmp = NULL;
    if(fread(nb_niveaux, sizeof(int), 1, fichier) != 1)
    {
        printf("Erreur lors de la lecture de la sauvegarde\n");
        return -1;
    }

    tmp  = malloc(sizeof(niveau_informations_t)*(*nb_niveaux));
    if(tmp == NULL)
    {
        printf("Impossible d'allouer la mémoire pour le chargement de la sauvegarde\n");
        return -1;
    }
    for(int i = 0; i < (*nb_niveaux); i++)
    {
        if(fread(tmp[i] , sizeof(niveau_informations_t), 1, fichier) != 1)
        {
            printf("Erreur lors de la lecture de la sauvegarde\n");
            free(tmp);
            return -1;
        }
    }

    (*infos_niveaux) = tmp;

    return 0;
}


/**
 * 
 * 
 * 
 */
static int sauvegarderInfosNiveaux(FILE * fichier, niveau_informations_t ** niveaux, int nb_niveaux)
{
    if(fwrite(&nb_niveaux, sizeof(int), 1, fichier) != 1)
    {
        printf("Erreur lors de la sauvegarde des informations sur les niveaux\n");
        return -1;
    }
    for(int i = 0; i < nb_niveaux; i++)
        if(fwrite(niveaux[i], sizeof(niveau_informations_t), 1, fichier) != 1)
        {
            printf("Erreur lors de la sauvegarde des informations sur les niveaux\n");
            return -2;
        }
    return 0;
}


/**
 * 
 * 
 * 
 * 
 */
int sauvegarderPartie(niveau_informations_t ** infos_niveaux, int nb_niveaux)
{
    FILE * fichier = fopen(filename_niveau, "wb");
    if(fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde de la partie\n");
        return -1;
    }

    if(sauvegarderInfosNiveaux(fichier, infos_niveaux, nb_niveaux) != 0)
    {
        fclose(fichier);
        return -2;
    }

    //Ici sauvegarder entités des salles

    fclose(fichier);
    return 0;
}

int chargerPartie(niveau_informations_t *** infos_niveaux, int * nb_niveaux)
{
    FILE * fichier = fopen(filename_niveau, "rb");
    if(chargerInfosNiveaux(fichier, infos_niveaux, nb_niveaux) != 0)
    {
        printf("Erreur lors du chargement\n");
        return -1;
    }

    return 0;
}


// DEBUG ---------------------------------------------------------------------------------------------

/**
 * \brief Affiche toutes les informations de la strcuture joueur
 *
 * \param tmp joueur
 */
/*
static void print_struct_player(const t_joueur * tmp){
    printf("\n\nAffichage de la structure joueur\n\n");
    printf("\npos x : %f , pos y : %f",tmp->x,tmp->y);
    printf("\npv : %d",tmp->pv);
    printf("\nfloat direction_vy : %f , float direction_vx : %f",tmp->direction_vy,tmp->direction_vx);
    printf("\nvitesse : %f",tmp->vitesse);
    printf("\nType entite : %d",tmp->type);
    printf("\nTaille du joueur : %f",tmp->taille);

    printf("\nId animation : %d",tmp->id_animation);

    printf("\n\n Partie Flags \n\n");
    printf("\nflags : \ndown : %d, \nup : %d, \nleft : %d, \nright : %d",tmp->flags->to_down,tmp->flags->to_up,tmp->flags->to_left,tmp->flags->to_right);

    printf("\n\n Partie Animation \n\n");

    printf("\nDernier update : %ud",tmp->animation->dernier_update);
    printf("\nid_max : %d",tmp->animation->id_max);
    printf("\nIndice tetxure : %d",tmp->animation->indice_texture);
    printf("\nNb texture : %d ",tmp->animation->nb_textures);
    printf("\nVitesse : %d\n",tmp->animation->vitesse);

}
*/

/**
 * \brief Affiche toutes les informations de la strcuture du niveau
 * 
 * \param tmp niveau
 */
/*
static void print_struct_niveau(const niveau_informations_t * tmp){
    printf("\n\nAffichage de la structure joueur\n\n");
    printf("\nhauteur %d, longueur %d",tmp->hauteur,tmp->longueur);

    printf("\n\n Affichage Matrice \n\n");

    for(int i = 0; i < HAUTEUR_NIVEAU_MAX; i++ ){
        for(int j = 0; j < LONGUEUR_NIVEAU_MAX; j ++){
            printf("%d\t", tmp->matrice[i][j]);
        }
        printf("\n");
    }

}
*/