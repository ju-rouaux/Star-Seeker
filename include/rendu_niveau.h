#ifndef _JEU_RENDU_NIVEAU_
#define _JEU_RENDU_NIVEAU_

#include <camera.h>

int dessinerTile(t_moteur * moteur, t_tile_type type, int x, int y, int scale);
int afficherNiveau(t_moteur * moteur, t_niveau * niveau, t_camera * camera);

#endif

