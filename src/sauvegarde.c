#include <sauvegarde.h>


/**
 * \brief Ecrit dans un fichier en binaire l'etat des la structure t_salle
 *
 * \param filename nom de fichier de sauvegarde
 * \param input strcuture a sauvegarder
 */
void write_file_player(const char * filename, t_joueur * input){

    FILE *outfile;
    t_joueur tmp;
    tmp.x =input->x;
    tmp.y = input->y;
    tmp.direction_vx = input->direction_vx;
    tmp.direction_vy = input->direction_vy;
    tmp.vitesse = input->vitesse;
    tmp.pv = input->pv;

    outfile = fopen (filename, "wb");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opened file\n");
        fprintf(stderr,"Program stopping ...");
        exit (1);
    }

    // write struct to file
    fwrite (&tmp, sizeof(t_joueur), 1, outfile);
    printf("pos x = %f, pos y = %f",tmp.x,tmp.y);

    if(fwrite != 0)
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
t_joueur *  read_file_player(const char * filename, t_joueur * joueur){
    FILE *infile;

    t_joueur * tmp =malloc(sizeof(t_joueur));


    // Open person.dat for reading
    infile = fopen (filename, "rb");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }
    // read file contents till end of file
    while(fread(tmp, sizeof(t_joueur), 1, infile))
    
    (joueur)->x =tmp->x;
    (joueur)->y = tmp->y;
    (joueur)->direction_vx = tmp->direction_vx;
    (joueur)->direction_vy = tmp->direction_vy;
    (joueur)->vitesse = tmp->vitesse;
    (joueur)->pv = tmp->pv;
        printf("pos x = %f, pos y = %f",tmp->x,tmp->y);

    fclose (infile);
    return joueur;

}

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
