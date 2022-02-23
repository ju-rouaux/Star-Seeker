#include "sauvegarde.h"


/**
 * \brief Ecrit dans un fichier en binaire l'etat des la structure t_salle
 *
 * \param filename nom de fichier de sauvegarde
 * \param input strcuture a sauvegarder
 */
void write_file_struct_salle(char * filename, t_salle * input){

    FILE *outfile;
    char tmp;

    outfile = fopen (filename, "wb");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opened file\n");
        fprintf(stderr,"Program stopping ...");
        exit (1);
    }

    // write struct to file
    fwrite (input, sizeof(t_salle), 1, outfile);

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
t_salle * read_file_struct_salle(char * filename){
    FILE *infile;

    t_salle * tmp = malloc(sizeof(t_salle));
    t_dimensions_salle * dimension_tmp = malloc(sizeof(t_dimensions_salle));

    tmp->dimensions = dimension_tmp;

    // Open person.dat for reading
    infile = fopen (filename, "rb");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }
    // read file contents till end of file
    while(fread(tmp, sizeof(t_salle), 1, infile))
        while(fread(tmp->dimensions, sizeof(t_salle), 1, infile))

    fclose (infile);

    return tmp;

}


/**
 * \brief Ecrit dans un fichier en binaire l'etat des la structure t_salle
 *
 * \param filename nom de fichier de sauvegarde
 * \param input strcuture a sauvegarder
 */
void write_file_struct_salle(char * filename, t_salle * input){

    FILE *outfile;
    char tmp;

    outfile = fopen (filename, "wb");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opened file\n");
        fprintf(stderr,"Program stopping ...");
        exit (1);
    }

    // write struct to file
    fwrite (input, sizeof(t_salle), 1, outfile);

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
t_salle * read_file_struct_salle(char * filename){
    FILE *infile;

    t_salle * tmp = malloc(sizeof(t_salle));
    t_dimensions_salle * dimension_tmp = malloc(sizeof(t_dimensions_salle));

    tmp->dimensions = dimension_tmp;

    // Open person.dat for reading
    infile = fopen (filename, "rb");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }
    // read file contents till end of file
    while(fread(tmp, sizeof(t_salle), 1, infile))
        while(fread(tmp->dimensions, sizeof(t_salle), 1, infile))

    fclose (infile);

    return tmp;

}

