#include <stdio.h>
#include <monstre.h>
#include <type_deplacement.h>
#include <outils.h>

void rapide_aleatoire(t_monstre * monstre, float j_x, float j_y)
{
    monstre->vitesse = 6;
    monstre->direction_vx = de(10);
    monstre->direction_vy = de(10);
}

void vers_joueur(t_monstre * monstre, float j_x, float j_y)
{
    monstre->vitesse = 3;
    monstre->direction_vx = j_x - monstre->x;
    monstre->direction_vy = j_y - monstre->y;
}
