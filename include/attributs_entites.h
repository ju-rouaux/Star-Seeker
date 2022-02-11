float x;
float y;
float vitesse;
t_type_entite type; //t_type_entite
SDL_Texture * texture;
float taille; //1 = taille d'un bloc
int partie_texture_courrante;
int nb_textures; //Nombre de texture max sur une ligne du tileset
t_animation * animation;
void (*update)(t_entite *, unsigned int); //Fonction appelée à chaque frame
