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
 * \brief Verifie si le fichier existe et s'il est pas vide
 *
 * \param filename nom du fichier
 * \return int boolen 0 : si vide ou n'existe pas, la taille du ficheir s'il existe
 */
static int tailleFichier(const char* filename)
{
    FILE *file = fopen(filename, "r");

    if(file == NULL)
        return 0;

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    return size;
}

// SAUVEGARDE JOUEUR ---------------------------------------------------------------------------------------------

/**
 * \brief Charge le joueur de ses données de sauvegarde.
 * 
 * Lis la sauvegarde dans le fichier binaire et met à jour la structure t_joueur.
 * 
 * \param joueur joueur à charger depuis la sauvegarde
 * 
 * \return SUCCESS ou la nature de l'erreur.
 */
err_save chargerJoueur(t_joueur * joueur)
{
    if(tailleFichier(filename_joueur) == 0)
        return NO_FILE;
    
    FILE * fichier = fopen(filename_joueur, "rb");
    if (fichier == NULL)
        return FOPEN_FAIL;

    t_joueur * tmp = malloc(sizeof(t_joueur));
    if(tmp == NULL)
    {
        fclose(fichier);
        return MALLOC_FAIL;
    }

    if(fread(tmp, sizeof(t_joueur), 1, fichier) != 1)
    {
        free(tmp);
        fclose(fichier);
        return READ_OR_WRITE_FAIL;
    }

    joueur->x = tmp->x;
    joueur->y = tmp->y;
    joueur->direction_vx = tmp->direction_vx;
    joueur-> direction_vy = tmp->direction_vy;
    joueur->vitesse = tmp->vitesse;

    free(tmp);
    fclose (fichier);

    return SUCCESS;
}

/**
 * \brief Sauverde le joueur dans son fichier.
 * 
 * \param joueur joueur à sauvegarder
 * 
 * \return SUCCESS ou la nature de l'erreur.
 */
err_save sauvegarderJoueur(t_joueur * joueur)
{
    FILE * fichier = fopen(filename_joueur, "wb");
    if(fichier == NULL)
        return FOPEN_FAIL;

    if(fwrite(joueur, sizeof(t_joueur), 1, fichier) != 1)
    {
        fclose(fichier);
        return READ_OR_WRITE_FAIL;
    }

    fclose(fichier);

    return SUCCESS;
}

// SAUVEGARDE PARTIE ---------------------------------------------------------------------------------------------

/**
 * \brief Charge les informations relatives à la structure des niveaux. Les données sont
 * remplies dans les pointeurs donnés en paramètre.
 * 
 * \param fichier Le fichier contenant les données
 * \param infos_niveaux Retour de la matrice des structures de donnée de niveau
 * \param nb_niveaux Retour du nombre de structures contenues dans la matrice
 * \param indice_niveau_charge Retour du niveau qui était chargé précédemment
 * 
 * \return SUCCESS ou la nature de l'erreur.
 */
static err_save chargerInfosNiveaux(FILE * fichier, niveau_informations_t *** infos_niveaux, int * nb_niveaux, int * indice_niveau_charge)
{
    niveau_informations_t ** tmp = NULL;

    if(fread(indice_niveau_charge, sizeof(int), 1, fichier) != 1)
        return READ_OR_WRITE_FAIL;

    if(fread(nb_niveaux, sizeof(int), 1, fichier) != 1)
        return READ_OR_WRITE_FAIL;

    tmp  = malloc(sizeof(niveau_informations_t)*(*nb_niveaux));
    if(tmp == NULL)
        return MALLOC_FAIL;

    for(int i = 0; i < (*nb_niveaux); i++)
    {
        if(fread(tmp[i] , sizeof(niveau_informations_t), 1, fichier) != 1)
        {
            free(tmp);
            return READ_OR_WRITE_FAIL;
        }
    }

    (*infos_niveaux) = tmp;

    return SUCCESS;
}


/**
 * \brief Sauvegarde les informations relatives à la structure des niveaux.
 * 
 * \param fichier Le fichier contenant les données
 * \param infos_niveaux La matrice des structures de donnée de niveau
 * \param nb_niveaux Le nombre de structures contenues dans la matrice
 * \param indice_niveau_charge L'indice du niveau qui est actuellement chargé
 * 
 * \return SUCCESS ou la nature de l'erreur.
 */
static err_save sauvegarderInfosNiveaux(FILE * fichier, niveau_informations_t ** niveaux, int nb_niveaux, int indice_niveau_charge)
{
    if(fwrite(&indice_niveau_charge, sizeof(int), 1, fichier) != 1)
        return READ_OR_WRITE_FAIL;

    if(fwrite(&nb_niveaux, sizeof(int), 1, fichier) != 1)
        return READ_OR_WRITE_FAIL;

    for(int i = 0; i < nb_niveaux; i++)
        if(fwrite(niveaux[i], sizeof(niveau_informations_t), 1, fichier) != 1)
            return READ_OR_WRITE_FAIL;

    return SUCCESS;
}


/**
 * \brief Sauvegarde les informations relatives à la partie
 * 
 * D'autres paramètres viendront s'ajouter lorsque ce sera nécéssaire.
 * 
 * \param infos_niveaux La matrice des structures de donnée de niveau
 * \param nb_niveaux Le nombre de structures contenues dans la matrice
 * \param indice_niveau_charge L'indice du niveau qui est actuellement chargé
 * 
 * \return SUCCESS ou la nature de l'erreur.
 */
err_save sauvegarderPartie(niveau_informations_t ** infos_niveaux, int nb_niveaux, int indice_niveau_charge)
{
    err_save retour = SAVE_ERROR;
    FILE * fichier = fopen(filename_niveau, "wb");
    if(fichier == NULL)
        return FOPEN_FAIL;

    retour = sauvegarderInfosNiveaux(fichier, infos_niveaux, nb_niveaux, indice_niveau_charge);
    if(retour != SUCCESS)
    {
        fclose(fichier);
        return retour;
    }

    //Ici traitements futurs

    fclose(fichier);
    return SUCCESS;
}

/**
 * \brief Charge les informations relatives à la partie
 * 
 * D'autres paramètres viendront s'ajouter lorsque ce sera nécéssaire.
 * 
 * \param infos_niveaux L'adresse de la matrice des structures de donnée de niveau
 * \param nb_niveaux L'adresse du nombre de structures contenues dans la matrice
 * \param indice_niveau_charge L'adresse de l'indice du niveau qui est actuellement chargé
 * 
 * \return SUCCESS ou la nature de l'erreur.
 */
err_save chargerPartie(niveau_informations_t *** infos_niveaux, int * nb_niveaux, int * indice_niveau_charge)
{
    err_save retour = SAVE_ERROR;
    FILE * fichier = fopen(filename_niveau, "rb");
    if(fichier == NULL)
        return FOPEN_FAIL;

    retour = chargerInfosNiveaux(fichier, infos_niveaux, nb_niveaux, indice_niveau_charge);
    if(retour != SUCCESS)
        return retour;

    //Ici traitements futurs

    return SUCCESS;
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