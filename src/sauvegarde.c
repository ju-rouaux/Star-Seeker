/**
 * \file sauvegarde.c
 * 
 * \brief Sauvegarde des structures du jeu pour permettre au joueur de continuer sa partie.
 * 
 * \author Guillaume Richard & Julien Rouaux
 */


#include <sauvegarde.h>

#define filename_joueur "./save/save_joueur.save"
#define filename_niveau "./save/save_niveau.save"
#define filename_param  "./save/save_parametres.save"

// OUTILS ---------------------------------------------------------------------------------------------

/**
 * \brief Retourne la taille d'un fichier, utile pour savoir s'il est vide ou s'il existe.
 *
 * \param filename nom du fichier
 * 
 * \return La taille du fichier.
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
err_save chargerSaveJoueur(t_joueur * joueur)
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
    joueur->xp = tmp->xp;

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
    niveau_informations_t * tmp = NULL;
    niveau_informations_t ** infos = NULL;

    e_type_entite type_c; //type entité courante;
    t_monstre * monstre_temp;

    if(fread(indice_niveau_charge, sizeof(int), 1, fichier) != 1)
        return READ_OR_WRITE_FAIL;

    if(fread(nb_niveaux, sizeof(int), 1, fichier) != 1)
        return READ_OR_WRITE_FAIL;

    infos  = malloc(sizeof(niveau_informations_t*)*(*nb_niveaux));
    if(infos == NULL)
        return MALLOC_FAIL;

    for(int i = 0; i < (*nb_niveaux); i++)
    {
        tmp  = malloc(sizeof(niveau_informations_t));
        if(fread(tmp, sizeof(niveau_informations_t), 1, fichier) != 1) //Lecture infos niveaux
            return READ_OR_WRITE_FAIL;

        tmp->liste_infos_entites = malloc(sizeof(t_info_entites*) * tmp->nb_infos_entite);
        if(tmp->liste_infos_entites == NULL)
            return MALLOC_FAIL;

        for(int j = 0; j < tmp->nb_infos_entite; j++)
        {
            tmp->liste_infos_entites[j] = malloc(sizeof(t_info_entites));
            if(tmp->liste_infos_entites[j] == NULL)
                return MALLOC_FAIL;

            if(fread(tmp->liste_infos_entites[j], sizeof(t_info_entites), 1, fichier) != 1) //Lecture liste entité
                return READ_OR_WRITE_FAIL;

            tmp->liste_infos_entites[j]->entites = malloc(sizeof(t_entite*) *  tmp->liste_infos_entites[j]->nb_entites);
            if(tmp->liste_infos_entites[j]->entites == NULL)
                return MALLOC_FAIL;

            for(int k = 0; k < tmp->liste_infos_entites[j]->nb_entites; k++)
            {
                if(fread(&type_c, sizeof(e_type_entite), 1, fichier) != 1) //Lecture type entité
                    return READ_OR_WRITE_FAIL;

                switch (type_c)
                {
                case E_MONSTRE:
                    monstre_temp = malloc(sizeof(t_monstre));
                    if(fread(monstre_temp, sizeof(t_monstre), 1, fichier) != 1) //Lecture infos niveaux
                        return READ_OR_WRITE_FAIL;
                    tmp->liste_infos_entites[j]->entites[k] = (t_entite*) creerMonstre(monstre_temp->x, monstre_temp->y, monstre_temp->vitesse, monstre_temp->pv, monstre_temp->taille, monstre_temp->nom_attaque, monstre_temp->deplacement);
                    free(monstre_temp);
                    break;
                
                default:
                    break;
                }
            }
        }

        infos[i] = tmp;
    }

    (*infos_niveaux) = infos;

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
    {
        if(fwrite(niveaux[i], sizeof(niveau_informations_t), 1, fichier) != 1) //Ecriture structure
            return READ_OR_WRITE_FAIL;

        for(int j = 0; j < niveaux[i]->nb_infos_entite; j++)
        {
            if(fwrite(niveaux[i]->liste_infos_entites[j], sizeof(t_info_entites), 1, fichier) != 1) //Ecriture des données sur les entités d'une salle
                return READ_OR_WRITE_FAIL;

            for(int k = 0; k < niveaux[i]->liste_infos_entites[j]->nb_entites; k++)
            {
                if(niveaux[i]->liste_infos_entites[j]->entites[k] != NULL)
                {
                    if(fwrite(&niveaux[i]->liste_infos_entites[j]->entites[k]->type, sizeof(e_type_entite), 1, fichier) != 1) //Ecriture du type de l'entité
                        return READ_OR_WRITE_FAIL;
                    
                    switch (niveaux[i]->liste_infos_entites[j]->entites[k]->type) //Ecriture de l'entité
                    {
                    case E_MONSTRE:
                        if(fwrite((t_monstre*) niveaux[i]->liste_infos_entites[j]->entites[k], sizeof(t_monstre), 1, fichier) != 1)
                            return READ_OR_WRITE_FAIL;
                        break;
                    
                    default:
                        break;
                    }
                }
                
            }

        }
    }

    return SUCCESS;
}


/**
 * \brief Sauvegarde les informations relatives à la partie
 * 
 * D'autres paramètres viendront s'ajouter lorsque ce sera nécessaire.
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
 * D'autres paramètres viendront s'ajouter lorsque ce sera nécessaire.
 * 
 * \param infos_niveaux L'adresse de la matrice des structures de donnée de niveau
 * \param nb_niveaux L'adresse du nombre de structures contenues dans la matrice
 * \param indice_niveau_charge L'adresse de l'indice du niveau qui est actuellement chargé
 * 
 * \return SUCCESS ou la nature de l'erreur.
 */
err_save chargerSavePartie(niveau_informations_t *** infos_niveaux, int * nb_niveaux, int * indice_niveau_charge)
{
    err_save retour = SAVE_ERROR;
    FILE * fichier = fopen(filename_niveau, "rb");
    if(fichier == NULL)
        return FOPEN_FAIL;

    retour = chargerInfosNiveaux(fichier, infos_niveaux, nb_niveaux, indice_niveau_charge);
    if(retour != SUCCESS)
    {
        printf("code %i", retour);
        return retour;
    }

    //Ici traitements futurs

    fclose(fichier);

    return SUCCESS;
}

// SAUVEGARDE PARAMETRES ---------------------------------------------------------------------------------------------

/**
 * \brief Sauvegarde des paramètres du joueur
 * 
 * \param parametres La structure des paramètres à sauvegarder
 * 
 * \return SUCCESS ou la nature de l'erreur.
 */
err_save sauvegarderParametres(t_parametres * parametres)
{
    FILE * fichier = fopen(filename_param, "wb");
    if(fichier == NULL)
        return FOPEN_FAIL;

    if(fwrite(parametres, sizeof(t_parametres), 1, fichier) != 1)
        return READ_OR_WRITE_FAIL;

    fclose(fichier);
    return SUCCESS;
}

/**
 * \brief Charge les paramètres du joueur
 * 
 * \param parametres La structure des paramètres à sauvegarder
 * 
 * \return SUCCESS ou la nature de l'erreur.
 */
err_save chargerSaveParametres(t_parametres * parametres)
{
    FILE * fichier = fopen(filename_param, "rb");
    if(fichier == NULL)
        return FOPEN_FAIL;

    if(fread(parametres, sizeof(t_parametres), 1, fichier) != 1)
        return READ_OR_WRITE_FAIL;

    fclose(fichier);
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