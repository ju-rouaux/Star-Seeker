/**
 * \file partie.h
 * 
 * \brief Module de gestion d'une partie : appel de sauvegarde
 * et appel des différents niveaux.
 * 
 * \author Julien Rouaux
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <camera.h>
#include <event.h>
#include <niveau.h>
#include <joueur.h>
#include <rendu_niveau.h>
#include <entite.h>
#include <liste.h>
#include <sauvegarde.h>
#include <generation_niveau.h>
#include <overlay.h>


/**
 * \brief Phase de gameplay principale.
 * 
 * \param moteur Moteur du jeu
 * \param joueur Le joueur
 * 
 * \return L'action ayant mis fin au niveau.
 */
static int jouerNiveau(t_moteur * moteur, t_joueur * joueur, niveau_informations_t * infos_niveau)
{
    t_niveau * niveau = moteur->niveau_charge;
    t_liste * liste_entites = moteur->liste_entites;
    t_entite * entite_courante;

    int tempsEcoule;
    int id_salle_courante;

    //t_projectile * proj = creerProjectile(BALLE, 0, 0, 0, 0, E_MONSTRE, moteur->textures->projectiles);
    //ajout_droit(liste_entites, (t_entite*) proj);
    //printf("cible : %i, x : %f, y : %f, vx : %f, vy : %f, dureevie : %i, vitesse : %f", proj->cible, proj->x, proj->y, proj->direction_vx, proj->direction_vy, proj->duree_de_vie, proj->vitesse);
    //detruireProjectile(&proj);
    int sortie = 0;
    updateCamera(moteur, niveau->salle_chargee->dimensions->largeur, niveau->salle_chargee->dimensions->hauteur, niveau->salle_chargee->dimensions->j, niveau->salle_chargee->dimensions->i, joueur->x, joueur->y);
    while((sortie = handleEvents(joueur)) == 0)
    {
        moteur->temps_precedent = moteur->temps;
        moteur->temps = SDL_GetTicks();
        SDL_RenderClear(moteur->renderer);
        updateEchelle(moteur);

        //Actualiser l'état des entités
        en_tete(liste_entites);
        joueur->update(moteur, (t_entite*) joueur); //Joueur
        if(!liste_vide(liste_entites)) //Liste
        {
            while(!hors_liste(liste_entites))
            {
                valeur_elt(liste_entites, &entite_courante);
                if(entite_courante != NULL)
                {
                    if(entite_courante->update(moteur, entite_courante) == -1)
                    {
                        entite_courante->detruire((t_entite**) &entite_courante);
                        oter_elt(liste_entites);
                    }
                }
                else
                    oter_elt(liste_entites);
                suivant(liste_entites);
                entite_courante = NULL;
            }
        }

        //Faire subir les dégâts
        ///...



        //Actualiser niveau
        id_salle_courante = niveau->salle_chargee->id_salle;
        updateNiveau(niveau, joueur->x, joueur->y, moteur->echelle);

        //Si on change de niveau -> animation
        if(id_salle_courante != niveau->salle_chargee->id_salle) //Animation changement de salle à mettre dans une fonction à l'avenir
        {
            int direction_x, direction_y;

            //Actualiser la liste des entités vivantes
            en_queue(liste_entites);
            while(!liste_vide(liste_entites))    //Destruction
                oter_elt(liste_entites);

            //Chargement des nouvelles
            en_tete(liste_entites);
            for(int i = 0; i < niveau->salle_chargee->nb_entite; i++)
                if(niveau->salle_chargee->entites[i] != NULL)
                    ajout_droit(liste_entites, niveau->salle_chargee->entites[i]);

            //Detruire anciennes collisions
            if(moteur->niveau_charge->collisions != NULL)
            {
                free(moteur->niveau_charge->collisions);
                moteur->niveau_charge->collisions = NULL;
                moteur->niveau_charge->taille_collisions = 0;
            }

            //Caluler future position
            updateFutureCamera(moteur, niveau->salle_chargee->dimensions->largeur, niveau->salle_chargee->dimensions->hauteur, niveau->salle_chargee->dimensions->j, niveau->salle_chargee->dimensions->i, joueur->x, joueur->y);

            //Animer
            while(moteur->camera->x != moteur->camera->futur_x || moteur->camera->y != moteur->camera->futur_y)
            {
                moteur->temps = SDL_GetTicks();

                //Calcul position caméra
                direction_x = moteur->camera->x == moteur->camera->futur_x ? 0 : (moteur->camera->x < moteur->camera->futur_x ? 1 : -1); //Sens où se diriger
                direction_y = moteur->camera->y == moteur->camera->futur_y ? 0 : (moteur->camera->y < moteur->camera->futur_y ? 1 : -1);

                //C'est ici qu'on peut changer la vitesse
                moteur->camera->x += 0.85 * direction_x; //Environ deux fois plus rapide car une salle est environ 2 fois plus grande en largeur qu'en hauteur
                moteur->camera->y += 0.5 * direction_y;

                if(abs(moteur->camera->futur_x - moteur->camera->x) <= 0.5)
                    moteur->camera->x = moteur->camera->futur_x;

                if(abs(moteur->camera->futur_y - moteur->camera->y) <= 0.5)
                    moteur->camera->y = moteur->camera->futur_y;


                //Rafraichir rendu
                SDL_RenderClear(moteur->renderer);
                afficherNiveau(moteur, joueur->x, joueur->y);

                //Dessiner entités
                dessinerEntite(moteur, (t_entite*) joueur);
                if(!liste_vide(liste_entites))
                {
                    en_tete(liste_entites);
                    while(!hors_liste(liste_entites))
                    {
                        valeur_elt(liste_entites, &entite_courante);
                        if(entite_courante != NULL)
                            dessinerEntite(moteur, entite_courante);
                        else
                            oter_elt(liste_entites);
                        suivant(liste_entites);
                        entite_courante = NULL;
                    }
                }

                if(joueur->flags->map_showing == 1){
                    dessiner_map(moteur, infos_niveau, niveau->salle_chargee->id_salle);
                }

                SDL_RenderPresent(moteur->renderer);

                //Réguler FPS
                tempsEcoule = SDL_GetTicks() - moteur->temps;
                if(TEMPS_POUR_CHAQUE_SECONDE > tempsEcoule)
                    SDL_Delay(TEMPS_POUR_CHAQUE_SECONDE - tempsEcoule);
            }

            //Reset la future position
            moteur->camera->futur_x = 0;
            moteur->camera->futur_y = 0;
        }
        //Actualiser caméra
        updateCamera(moteur, niveau->salle_chargee->dimensions->largeur, niveau->salle_chargee->dimensions->hauteur, niveau->salle_chargee->dimensions->j, niveau->salle_chargee->dimensions->i, joueur->x, joueur->y);
        //Rendu niveau
        afficherNiveau(moteur, joueur->x, joueur->y);

        //Afficher collisions DEBUG
        /*
        if(moteur->niveau_charge->collisions!=NULL)
            for(int b = 0; b < moteur->niveau_charge->taille_collisions; b++)
                SDL_RenderDrawRect(moteur->renderer, &(moteur->niveau_charge->collisions[b]));
        */

        //rendu joueur
        dessinerEntite(moteur, (t_entite*) joueur);
        //Dessiner entités
        if(!liste_vide(liste_entites))
        {
            en_tete(liste_entites);
            while(!hors_liste(liste_entites))
            {
                valeur_elt(liste_entites, &entite_courante);
                if(entite_courante != NULL)
                    dessinerEntite(moteur, entite_courante);
                else
                    oter_elt(liste_entites);
                suivant(liste_entites);
                entite_courante = NULL;
            }
        }

  
        if(joueur->flags->map_showing == 1){
            dessiner_map(moteur, infos_niveau, niveau->salle_chargee->id_salle);
        }


        //Afficher frame
        SDL_RenderPresent(moteur->renderer);

        //Réguler FPS
        tempsEcoule = SDL_GetTicks() - moteur->temps;
        if(TEMPS_POUR_CHAQUE_SECONDE > tempsEcoule)
            SDL_Delay(TEMPS_POUR_CHAQUE_SECONDE - tempsEcoule);
    }


    return sortie;
}


/**
 * \brief Sélection et lancement de niveau.
 * 
 * \param moteur Le moteur du jeu
 * \param joueur Le joueur
 * \param infos_niveaux Les informations sur la structure d'un niveau
 * \param nb_niveaux Le nombre de niveaux contenus dans la matrice des informations
 * \param indice_niveau_charge Le niveau actuellement joué
 * 
 *  \return 0 si la fin d'une partie s'est bien passée, sinon une valeur négative.
 */
static int jouerPartie(t_moteur * moteur, t_joueur * joueur, niveau_informations_t ** infos_niveaux, int nb_niveaux, int indice_niveau_charge)
{

    if(chargerNiveau(moteur, infos_niveaux[indice_niveau_charge]) != 0)
    {
        printf("Erreur lors du chargement du niveau\n");
        return -1;
    }
    t_niveau * niveau = moteur->niveau_charge;
    if(joueur->x == 0 && joueur->y == 0) //Si la sauvegarde du joueur est vierge, placer le joueur sur la map
    {
        joueur->x = niveau->salle_chargee->dimensions->j*NB_TILE_LARGEUR + NB_TILE_LARGEUR / 2; 
        joueur->y = niveau->salle_chargee->dimensions->i*NB_TILE_HAUTEUR + NB_TILE_HAUTEUR / 2;
    }
    
    //Jeu en cours
    int sortie = 0;
    while(sortie != -1)
    {
        sortie = jouerNiveau(moteur, joueur, infos_niveaux[indice_niveau_charge]);
        if(sortie == -88 && indice_niveau_charge > 0)
        {
            infos_niveaux[indice_niveau_charge]->i_dep = niveau->i_charge;
            infos_niveaux[indice_niveau_charge]->j_dep = niveau->j_charge;
            detruireNiveau(&niveau);
            indice_niveau_charge--;
            if(chargerNiveau(moteur, infos_niveaux[indice_niveau_charge]) != 0)
            {
                printf("Erreur lors du chargement du niveau\n");
                return -1;
            }
            niveau = moteur->niveau_charge;
            joueur->x = niveau->salle_chargee->dimensions->j*NB_TILE_LARGEUR + NB_TILE_LARGEUR / 2; 
            joueur->y = niveau->salle_chargee->dimensions->i*NB_TILE_HAUTEUR + NB_TILE_HAUTEUR / 2;
        }

        if(sortie == -99 && indice_niveau_charge < nb_niveaux-1)
        {
            infos_niveaux[indice_niveau_charge]->i_dep = niveau->i_charge;
            infos_niveaux[indice_niveau_charge]->j_dep = niveau->j_charge;
            detruireNiveau(&niveau);
            indice_niveau_charge++;
            if(chargerNiveau(moteur, infos_niveaux[indice_niveau_charge]) != 0)
            {
                printf("Erreur lors du chargement du niveau\n");
                return -1;
            }
            niveau = moteur->niveau_charge;
            joueur->x = niveau->salle_chargee->dimensions->j*NB_TILE_LARGEUR + NB_TILE_LARGEUR / 2; 
            joueur->y = niveau->salle_chargee->dimensions->i*NB_TILE_HAUTEUR + NB_TILE_HAUTEUR / 2;
        }
    }

    //Fin de du jeu
    infos_niveaux[indice_niveau_charge]->i_dep = niveau->i_charge;
    infos_niveaux[indice_niveau_charge]->j_dep = niveau->j_charge;
    sauvegarderJoueur(joueur);
    sauvegarderPartie(infos_niveaux, nb_niveaux, indice_niveau_charge);

    for(int i = 0; i < nb_niveaux; i++)
        detruire_niveau_info(&infos_niveaux[i]);
    free(infos_niveaux);
    detruireJoueur(&joueur);
    arreterNiveau(&moteur->niveau_charge);

    return 0;
}


/**
 * \brief Fonction générant une nouvelle partie.
 * 
 * Sont chargés :
 *  - La quête de la partie (soon) ; 
 *  - Les structures du niveau ; 
 *  - Les monstres et leur emplacement (soon) ; 
 * 
 * \param nb_niveaux Le nombre de niveaux désiré
 * \param adr_infos L'adresse de la matrice des infos sur la structure des niveaux, à NULL de préférance
 * 
 * \return 0 si succès, une valeur négative si echec.
 */
static int genererPartie(int nb_niveaux, niveau_informations_t *** adr_infos)
{
    int i;
    niveau_informations_t ** infos = malloc(sizeof(niveau_informations_t*)*nb_niveaux);
    if(infos == NULL)
    {
        printf("Impossible d'allouer la mémoire pour les infos du niveau\n");
        return -1;
    }
    
    for(i = 0; i < nb_niveaux; i++)
    {
        //Générer un nom de niveau ici

        infos[i] = creer_niveau_info("kikikoukou");
        if(infos[i] == NULL)
        {
            printf("NULL\n");
        }
        
        if(infos[i] == NULL)
        {
            printf("Echec lors de la génération d'un niveau.\n");
            //Nettoyage mémoire
            i--;
            while(i >= 0)
            {
                detruire_niveau_info(&infos[i]);
                i--;
            }
            return -1;
        }
    }
    
    (*adr_infos) = infos;

    return 0;
}


/**
 * \brief Ecrase la sauvegarde pour générer une nouvelle partie.
 * 
 * Dans l'idéal cette fonction devra calculer le nombre de niveaux.
 * 
 * \param moteur Le moteur du jeu
 * \param nb_niveaux !! TEMPORAIRE le nombre de niveaux désiré pour la nouvelle partie
 * 
 * \return 0 si succès, valeur négative si echec.
 */
int nouvellePartie(t_moteur * moteur, int nb_niveaux)
{
    niveau_informations_t ** infos;
    t_joueur * joueur = NULL;
    int retour;

    //S'occuper du niveau
    retour = genererPartie(nb_niveaux, &infos);
    if(retour != 0)
    {
        printf("Impossible de générer une nouvelle partie\n");
        return -1;
    }

    //S'occuper du joueur
    joueur = creerJoueur(0, 0, moteur->textures->player);
    if(joueur == NULL)
    {
        printf("Le niveau n'a pas pu être chargé\n");
        for(int i = 0; i < nb_niveaux; i++)
            detruire_niveau_info(&infos[i]);
        free(infos);
        return -1;
    }
    if(moteur->parametres.reset_sauvegarde_joueur == VRAI)
    {   //Ecraser joueur
        sauvegarderJoueur(joueur);
        printf("Sauvegarde joueur écrasée.\n");
        moteur->parametres.reset_sauvegarde_joueur = FAUX;
    }
    else
    {   //Charger joueur
        if(chargerSaveJoueur(joueur) != 0)
        {
            printf("Le niveau n'a pas pu être chargé car le joueur n'a pas pu etre chargé\n");
            for(int i = 0; i < nb_niveaux; i++)
                detruire_niveau_info(&infos[i]);
            free(infos);
            detruireJoueur(&joueur);
            return -1;
        }
        joueur->x = 0;
        joueur->y = 0;
    }

    //Sauvegarde de la partie générée
    sauvegarderPartie(infos, nb_niveaux, 0);
    return jouerPartie(moteur, joueur, infos, nb_niveaux, 0);
}

/**
 * \brief Charge la partie si le fichier de sauvegarde existe.
 * 
 * \param moteur Le moteur du jeu
 * 
 * \return 0 si succès, valeur négative si echec.
 */
int chargerPartie(t_moteur * moteur)
{
    t_joueur * joueur = NULL;
    niveau_informations_t ** infos = NULL;
    int nb_niveaux;
    int indice_niveau_charge;

    if(moteur->parametres.reset_sauvegarde_joueur == VRAI)
    {
        printf("Le joueur a demandé d'écraser sa sauvegarde, mais relance sa partie. Suppression de sauvegarde annulée.\n");
        moteur->parametres.reset_sauvegarde_joueur = FAUX;
    }
    
    //Créer le joueur
    joueur = creerJoueur(0, 0, moteur->textures->player);
    if(joueur == NULL)
    {
        printf("Le niveau n'a pas pu être chargé\n");
        return -1;
    }

    //Charger joueur
    if(chargerSaveJoueur(joueur) != 0)
    {
        printf("Le niveau n'a pas pu être chargé car le joueur n'a pas pu etre chargé\n");
        detruireJoueur(&joueur);
        return -1;
    }

    //Charger partie
    if(chargerSavePartie(&infos, &nb_niveaux, &indice_niveau_charge) != 0)
    {
        printf("Le niveau n'a pas pu être chargé car la sauvegarde de la partie n'a pas pu être chargé\n");
        detruireJoueur(&joueur);
        return -1;
    }
    
    return jouerPartie(moteur, joueur, infos, nb_niveaux, indice_niveau_charge);
}