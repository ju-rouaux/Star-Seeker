#include <sauvegarde.h>

static FILE * openFile_create_write(char *filename){

    FILE * outfile;

    outfile = fopen (filename, "ab+");
    if (outfile == NULL)
        return;

    return outfile;
}


static FILE * openFile_read(char *filename){

    FILE * outfile;

    outfile = fopen (filename, "rb");
    if (outfile == NULL)
        return;
    return outfile;
}

/**
 * \brief Ecrit dans un fichier en binaire l'etat des la structure t_salle
 *
 * \param filename nom de fichier de sauvegarde
 * \param input strcuture a sauvegarder
 * \param size taille a allouer(sizeof)
 */
void save_current_game(char * filename, void * input,size_t size){
    FILE * outfile = openFile_create_write(filename);

    // write struct to file
    if(fwrite (input, size, 1, outfile) == 1 )//&& fwrite (input->flags, sizeof(t_joueur_flags), 1, outfile) == 1 && fwrite (input->animation, sizeof(t_animation), 1, outfile) == 1) // && fwrite (input->animation, sizeof(t_joueur), 1, outfile) == 1
        printf("contents to file written successfully !\n");
    else
        printf("error writing file !\n");


    // close file
    fclose (outfile);
}

/**
 * \brief Lis dans un fichier en binaire l'etat des la structure t_salle
 *
 * \param filename nom de fichier de sauvegarde
 * \return t_salle* la structure lu dans le fichier
 */
int read_file_player(char * filename, t_joueur * joueur){
    FILE *infile = openFile_read(filename);

    t_joueur * tmp = malloc(sizeof(t_joueur));


    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file Player\n");
        return -1;
    }
    // read file contents till end of file
    while(fread(tmp, sizeof(t_joueur), 1, infile))
    // while(fread(tmp->flags, sizeof(t_joueur_flags), 1, infile))
    // while(fread(tmp->animation, sizeof(t_animation), 1, infile))

    joueur->x = tmp->x;
    joueur->y = tmp->y;
    joueur->direction_vx = tmp->direction_vx;
    joueur-> direction_vy = tmp->direction_vy;
    joueur->vitesse = tmp->vitesse;

    fclose (infile);
    return 0;

}


int read_file_niveau(char * filename, niveau_informations_t * niveau){
    FILE *infile;

    niveau_informations_t * tmp = malloc(sizeof(niveau_informations_t));

    infile = fopen (filename, "rb");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file Level\n");
        return -1;
    }
    // read file contents till end of file
    while(fread(tmp , sizeof(niveau_informations_t), 1, infile))
    // while(fread(tmp->flags, sizeof(t_joueur_flags), 1, infile))
    // while(fread(tmp->animation, sizeof(t_animation), 1, infile))

    niveau->longueur = tmp->longueur;
    niveau->hauteur = tmp->hauteur;
    **niveau->matrice = **tmp->matrice;

    fclose (infile);
    return 0;

}


/**
 * \brief Affiche toutes les informations de la strcuture joueur
 *
 * \param tmp joueur
 */
void print_struct_player(const t_joueur * tmp){
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

void print_struct_niveau(const niveau_informations_t * tmp){
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

/**
 * \brief Verifie si le fichier existe et s'il est pas vide
 *
 * \param filename nom du fichier
 * \return int boolen 0 : si vide ou n'existe pas, >1 s'il existe
 */
int file_empty(const char* filename)
{
    FILE *file = fopen(filename, "r");

    if(file == NULL)
        return 0;

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    return size;
}
