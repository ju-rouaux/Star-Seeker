#include "sauvegarde.h"

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

// Driver program
void main ()
{

    t_salle * sallein = malloc(sizeof(t_salle));
    t_dimensions_salle * dimension = malloc(sizeof(t_dimensions_salle));

    t_salle salleout;


    sallein->complete = 1;
    sallein->dimensions = dimension;
    sallein->dimensions->hauteur = 20;
    sallein->dimensions->i = 10;
    sallein->dimensions->j = 10;
    sallein->dimensions->largeur = 20;
    sallein->dimensions->nombre = 5;
    sallein->id_salle = 1;
//  sallein->portes[0].


    char * filename = "save.txt";


    write_file_struct_salle(filename,sallein);
    salleout = *read_file_struct_salle(filename);

    printf("\nsallein->complete = %d, \nsallein->dimensions->hauteur = %d, \nsallein->dimensions->i = %d, \nsallein->dimensions->j = %d, \nsallein->dimensions->largeur = %d, \nsallein->dimensions->nombre = %d, \nsallein->id_salle = %d",sallein->complete, sallein->dimensions->hauteur, sallein->dimensions->i, sallein->dimensions->j, sallein->dimensions->largeur, sallein->dimensions->nombre, sallein->id_salle);
    // printf("id_salle = %d, complete = %d, chaine = %s",salleout.id_salle,salleout.complete,salleout.str);



}


