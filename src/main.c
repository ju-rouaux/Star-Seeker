#include <sauvegarde.h>

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

    return 0;

}
