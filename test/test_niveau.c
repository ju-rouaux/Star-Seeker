/**
 * \file
 * \brief Fichier de test de chargement de niveau en l'affichant dans le terminal
 * 
 * \author Julien
 */

#include <stdio.h>
#include <niveau.h>

//gcc .\src\niveau.c .\test\test_niveau.c -o .\bin\test_niveau -Iinclude

void afficher(const t_niveau * niveau)
{
    t_salle * salle_courante;
    for(int i = 0; i < (niveau->h)*2; i++)
    {
        for(int j = 0; j < niveau->l; j++)
        {
            salle_courante = niveau->salles[(i/2)*niveau->l + j];
            if(!(i % 2)) //Affichage salle
            {
                if(salle_courante != NULL)
                {
                    printf("%02d", salle_courante->id_salle);
                    if(salle_courante->portes[RIGHT] != NULL) //Si liaison à droite
                        if(salle_courante->portes[RIGHT]->id_salle == salle_courante->id_salle)
                            printf("#");
                        else
                            printf("-");
                    else
                        printf(" ");
                }  
                else
                    printf(".. ");
            }
            else //Affichage portes horizontales
            {
                if(salle_courante != NULL)
                {
                    if(salle_courante->portes[DOWN] != NULL) //Si liaison en bas
                        if(salle_courante->portes[DOWN]->id_salle == salle_courante->id_salle)
                            printf("#  ");
                        else
                            printf("|  ");
                    else
                        printf("   ");
                }  
                else
                    printf("   ");
            }
        }
        printf("\n");
    }
}

int main(void)
{
    FILE * fichier = fopen("./test/allure_d'un_niveau.txt", "r");
    if(fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    t_niveau * niveau = chargerNiveau(fichier);
    if(niveau == NULL)
        printf("Niveau non récupéré");
    else
    {
        printf("affichage...\n");
        afficher(niveau);
        detruireNiveau(&niveau);
    }

    fclose(fichier);

    return 0;
}