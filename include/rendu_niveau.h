#ifndef _JEU_RENDU_NIVEAU_
#define _JEU_RENDU_NIVEAU_

#define NB_TILE_LARGEUR 15
#define NB_TILE_HAUTEUR 9

int dessinerTile(t_moteur * moteur, t_tile_type type, int x, int y, int scale);
int getScale(SDL_Window * window);
int afficherNiveau(t_moteur * moteur, t_niveau * niveau);
#endif

