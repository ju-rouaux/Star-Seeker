/**
 * \file sauvegarde.c
 * 
 * \brief Sauvegarde des structures du jeu pour permettre au joueur de continuer sa partie.
 * 
 * \author Guillaume Richard & Julien Rouaux
 */


#include <sauvegarde.h>


/**
 * \brief Verifie si le fichier existe et s'il est pas vide
 *
 * \param filename nom du fichier
 * \return int boolen 0 : si vide ou n'existe pas, la taille du ficheir s'il existe
 */
static int file_empty(const char* filename)
{
    FILE *file = fopen(filename, "r");

    if(file == NULL)
        return 0;

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    return size;
}

/**
 * \brief Lis la sauvegarde dans le fichier binaire et met a jour la strcture t_joueur
 * 
 * \param filename nom du fichier
 * \param joueur structure du joueur a charger depuis la sauvegarde
 * \return int boolen
 */
static int chargerJoueur(t_joueur * joueur)
{
    FILE * fichier = fopen(filename_joueur, "rb");
    if (fichier == NULL)
    {
        fprintf(stderr, "Error opening file for player\n");
        return -1;
    }

    t_joueur * tmp = malloc(sizeof(t_joueur));
    if(tmp == NULL)
    {
        printf("Une allocation de mémoire temporaire pour le chargement du joueur a échoué\n");
        return -1;
    }

    if(fread(tmp, sizeof(t_joueur), 1, fichier) != 1)
    {
        printf("Erreur lors de la lecture du fichier du joueur\n");
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
 * \brief  Lis la sauvegarde dans le fichier binaire et met a jour la strcture niveau_informations_t
 * 
 * \param filename nom du fichier
 * \param niveau structure du niveau a charger depuis la sauvegarde
 * \return niveau_informations_t* la strcture du niveau remplie par la sauvegarde
 */
static niveau_informations_t * chargerInfosNiveaux(FILE * fichier)
{
    int nb_niveaux;
    niveau_informations_t ** tmp = NULL;
    if(fread(&nb_niveaux, sizeof(int), 1, fichier) != 1)
    {
        printf("Erreur lors de la lecture de la sauvegarde\n");
        return NULL;
    }

    tmp  = malloc(sizeof(niveau_informations_t)*nb_niveaux);
    if(tmp == NULL)
    {
        printf("Impossible d'allouer la mémoire pour le chargement de la sauvegarde\n");
        return NULL;
    }
    for(int i = 0; i < nb_niveaux; i++)
    {
        if(fread(tmp[i] , sizeof(niveau_informations_t), 1, fichier) != 1)
        {
            printf("Erreur lors de la lecture de la sauvegarde\n");
            free(tmp);
            return NULL;
        }
    }

    return tmp;
}


/**
 * 
 * 
 * 
 */
int sauvegarderInfosNiveaux(FILE * fichier, niveau_informations_t ** niveaux, int nb_niveaux)
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
int sauvegarderPartie(niveau_informations_t ** niveaux, int nb_niveaux)
{
    FILE * fichier = fopen(filename_niveau, "wb");
    if(fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde de la partie\n");
        return -1;
    }

    if(sauvegarderInfosNiveaux(fichier, niveaux, nb_niveaux) != 0)
    {
        return -2;
    }

    //Ici sauvegarder entités des salles
}



int sauvegarderJoueur(t_joueur * joueur)
{
    FILE * fichier = fopen(filename_joueur, "wb");
    if(fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde du joueur\n");
        return -1;
    }

}


int sauvegarder(t_joueur * joueur, niveau_informations_t * niveau){

    if(save_current_game(filename_joueur,joueur, sizeof(t_joueur)) != 0){
        printf("Erreur de sauvegarde du joueur\n");
        return -1;
    }

    if(save_current_game(filename_niveau,niveau, sizeof(niveau_informations_t))){ 
        printf("Erreur de sauvegarde du joueur\n");
        return -1;
    }

    return 0;
}


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