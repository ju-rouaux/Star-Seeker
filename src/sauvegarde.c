/**
 * \file sauvegarde.c
 * 
 * \brief Sauvegarde des structures du jeu pour permettre au joueur de continuer sa partie.
 * 
 * \author Julien Rouaux & Guillaume Richard
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
    joueur->pv = tmp->pv;
    joueur->nom_attaque = tmp->nom_attaque;
    chargerAttaqueTir(&joueur->attaque_tir_equipee, joueur->nom_attaque);

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
    int taille_chaine_nom;

    niveau_informations_t * tmp = NULL;
    niveau_informations_t ** infos = NULL;

    e_type_entite type_c; //type entité courante;
    t_monstre * monstre_temp;
    t_interaction * inter_temp;

    if(fread(indice_niveau_charge, sizeof(int), 1, fichier) != 1)
        return READ_OR_WRITE_FAIL;

    if(fread(nb_niveaux, sizeof(int), 1, fichier) != 1)
        return READ_OR_WRITE_FAIL;

    infos  = malloc(sizeof(niveau_informations_t*)*(*nb_niveaux));
    if(infos == NULL)
        return MALLOC_FAIL;

    for(int i = 0; i < (*nb_niveaux); i++)
    {
        tmp = malloc(sizeof(niveau_informations_t));
        if(fread(tmp, sizeof(niveau_informations_t), 1, fichier) != 1) //Lecture infos niveaux
            return READ_OR_WRITE_FAIL;

        tmp->matrice = malloc(sizeof(int) * tmp->hauteur * tmp->longueur);
        if(fread(tmp->matrice, sizeof(int) * tmp->hauteur * tmp->longueur, 1, fichier) != 1) //Lecture matrice
            return READ_OR_WRITE_FAIL;

        if(fread(&taille_chaine_nom, sizeof(int), 1, fichier) != 1) //Lecture taille de la chaine du nom du niveau
            return READ_OR_WRITE_FAIL;

        tmp->nom_planete = malloc(sizeof(char)*taille_chaine_nom);
        if(fread(tmp->nom_planete, sizeof(char)*taille_chaine_nom, 1, fichier) != 1) //Lecture du nom du niveau
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
                    if(fread(monstre_temp, sizeof(t_monstre), 1, fichier) != 1)
                        return READ_OR_WRITE_FAIL;
                    tmp->liste_infos_entites[j]->entites[k] = (t_entite*) creerMonstre(monstre_temp->x, monstre_temp->y, monstre_temp->vitesse, monstre_temp->pv, monstre_temp->taille, monstre_temp->nom_attaque, monstre_temp->deplacement);
                    free(monstre_temp);
                    break;

                case E_INTERACTION:
                    inter_temp = malloc(sizeof(t_interaction));
                    if(fread(inter_temp, sizeof(t_interaction), 1, fichier) != 1)
                        return READ_OR_WRITE_FAIL;
                    tmp->liste_infos_entites[j]->entites[k] = (t_entite*) creerInteraction(inter_temp->type_inter, inter_temp->x, inter_temp->y, inter_temp->data);
                    free(inter_temp);
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
    int taille_chaine_nom;

    if(fwrite(&indice_niveau_charge, sizeof(int), 1, fichier) != 1)
        return READ_OR_WRITE_FAIL;

    if(fwrite(&nb_niveaux, sizeof(int), 1, fichier) != 1)
        return READ_OR_WRITE_FAIL;

    for(int i = 0; i < nb_niveaux; i++)
    {
        if(fwrite(niveaux[i], sizeof(niveau_informations_t), 1, fichier) != 1) //Ecriture structure
            return READ_OR_WRITE_FAIL;

        if(fwrite(niveaux[i]->matrice, sizeof(int) * niveaux[i]->hauteur * niveaux[i]->longueur, 1, fichier) != 1) //Ecriture matrice
            return READ_OR_WRITE_FAIL;
        
        taille_chaine_nom = strlen(niveaux[i]->nom_planete) + 1;

        if(fwrite(&taille_chaine_nom, sizeof(int), 1, fichier) != 1) //Ecriture taille chaine
            return READ_OR_WRITE_FAIL;

        if(fwrite(niveaux[i]->nom_planete, sizeof(char)*taille_chaine_nom, 1, fichier) != 1) //Ecriture nom du niveau chaine
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
                        
                    case E_INTERACTION:
                        if(fwrite((t_interaction*) niveaux[i]->liste_infos_entites[j]->entites[k], sizeof(t_interaction), 1, fichier) != 1)
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
err_save sauvegarderPartie(char * nom_galaxie, niveau_informations_t ** infos_niveaux, int nb_niveaux, int indice_niveau_charge)
{
    err_save retour = SAVE_ERROR;
    FILE * fichier = fopen(filename_niveau, "wb");
    if(fichier == NULL)
        return FOPEN_FAIL;

    //Sauvegarder nom galaxie (nom de la partie)
    int taille_chaine_nom = strlen(nom_galaxie) + 1;
    if(fwrite(&taille_chaine_nom, sizeof(int), 1, fichier) != 1) //Ecriture taille nom de la partie
    {
        fclose(fichier);
        return READ_OR_WRITE_FAIL;
    }
    if(fwrite(nom_galaxie, sizeof(char)*taille_chaine_nom, 1, fichier) != 1) //Ecriture nom de la partie
    {
        fclose(fichier);
        return READ_OR_WRITE_FAIL;
    }

    //Sauvegarde de la structure du niveau
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
err_save chargerSavePartie(char ** nom_galaxie, niveau_informations_t *** infos_niveaux, int * nb_niveaux, int * indice_niveau_charge)
{
    err_save retour = SAVE_ERROR;
    FILE * fichier = fopen(filename_niveau, "rb");
    if(fichier == NULL)
        return FOPEN_FAIL;

    //Charger nom galaxie (nom de la partie)
    int taille_chaine_nom;
    if(fread(&taille_chaine_nom, sizeof(int), 1, fichier) != 1) //Lecture taille nom de la partie
    {
        fclose(fichier);
        return READ_OR_WRITE_FAIL;
    }
    *nom_galaxie = malloc(sizeof(char)*taille_chaine_nom);
    if(fread(*nom_galaxie, sizeof(char)*taille_chaine_nom, 1, fichier) != 1) //Lecture nom de la partie
    {
        free(*nom_galaxie);
        *nom_galaxie = NULL;
        fclose(fichier);
        return READ_OR_WRITE_FAIL;
    }

    //Charger la structure du niveau
    retour = chargerInfosNiveaux(fichier, infos_niveaux, nb_niveaux, indice_niveau_charge);
    if(retour != SUCCESS)
    {
        free(*nom_galaxie);
        *nom_galaxie = NULL;
        fclose(fichier);
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