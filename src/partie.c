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
#include <time.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <camera.h>
#include <event.h>
#include <niveau.h>
#include <joueur.h>
#include <monstre.h>
#include <rendu_niveau.h>
#include <entite.h>
#include <liste.h>
#include <sauvegarde.h>
#include <generation_niveau.h>
#include <noms_generateur.h>
#include <outils.h>
#include <generation_entites.h>
#include <overlay.h>
#include <particules.h>
#include <main.h>
#include <menu_niveau.h>




/* ################################ Fonctions principales du jeu ################################ */


/**
 * \brief Vide la liste de ses entités et note dans info_entites les entités qui doivent être sauvegardées.
 * 
 * \param liste_entites La liste à vider
 * \param info_entites La liste des informations sur les entités par salles
 * \param nb_info_entites Le nombre d'éléments dans la liste info_entites
 * \param id_ancienne_salle L'identifiant de l'ancienne salle où sauvegarder les entités vidées
 */
static void viderEntitesDeListe(t_liste * liste_entites, t_info_entites ** info_entites, int nb_info_entites, int id_ancienne_salle)
{
    t_entite * entite_courante;

    //Sauvegarde des entités qui importent
    for(int i = 0; i < nb_info_entites; i++)
    {
        //Chercher la matrice d'entité de l'ancienne salle
        if(info_entites[i]->id_salle == id_ancienne_salle)
        {
            int cpt = 0; //Compteur des entités restantes
            en_tete(liste_entites);
            while(!hors_liste(liste_entites) && cpt < info_entites[i]->nb_entites) //Si jamais il y a plus d'entités que prévu à la base, on ne note pas l'info
            {
                valeur_elt(liste_entites, &entite_courante);
                if(entite_courante != NULL && (entite_courante->type == E_MONSTRE || entite_courante->type == E_INTERACTION)) //Ne sauvegarder que les monstres ou les interactions
                    info_entites[i]->entites[cpt++] = entite_courante;

                entite_courante = NULL;
                suivant(liste_entites);
            }
            info_entites[i]->nb_entites = cpt; //On ne devrait jamais dépasser le nombre d'entités qui étaient alloués de base
        }
    }

    //Vider la liste et détruire les entités qui n'importent pas
    en_queue(liste_entites);
    while(!liste_vide(liste_entites))
    {
        valeur_elt(liste_entites, &entite_courante);

        if(entite_courante != NULL && (entite_courante->type == E_PROJECTILE || entite_courante->type == E_PARTICULE))
            entite_courante->detruire((t_entite**) &entite_courante); //Détruire les projectiles et particules

        //Enlever les entités de la liste
        oter_elt(liste_entites); 

        entite_courante = NULL;
    }
}


/**
 * \brief Charge les entités associées à la salle dans la liste
 * 
 * \param liste_entites La liste à charger
 * \param info_entites La liste des informations sur les entités par salles
 * \param nb_info_entites Le nombre d'éléments dans la liste info_entites
 * \param id_salle_courante L'identifiant de la nouvelle salle d'où charger les entités
 */
static void chargerEntitesVersListe(t_liste * liste_entites, t_info_entites ** info_entites, int nb_info_entites, int id_salle_courante)
{
    en_tete(liste_entites);
    for(int i = 0; i < nb_info_entites; i++)
        if(info_entites[i]->id_salle == id_salle_courante)
            for(int j = 0; j < info_entites[i]->nb_entites; j++)
                ajouterEntiteListe(liste_entites, info_entites[i]->entites[j]);
}


/**
 * \brief Affiche les entités chargées dans la liste du moteur sur l'écran.
 * 
 * \param moteur Le moteur
 */
static void renduEntites(t_moteur * moteur)
{
    t_entite * entite_courante;
    en_tete(moteur->liste_entites);
    while(!hors_liste(moteur->liste_entites))
    {
        valeur_elt(moteur->liste_entites, &entite_courante);
        if(entite_courante != NULL && entite_courante->dessiner != NULL)
            entite_courante->dessiner(moteur, entite_courante);
        else
            oter_elt(moteur->liste_entites);
        
        //Si on a ôté le premier élément de la liste, replacer la tête de la liste au début
        if(hors_liste(moteur->liste_entites))
            en_tete(moteur->liste_entites);
        else
            suivant(moteur->liste_entites);

        entite_courante = NULL;
    }
}


/**
 * \brief Libère et charge les entités 
 * 
 */
void transitionChangementSalle(t_moteur * moteur, t_joueur * joueur, niveau_informations_t * infos_niveau, int id_ancienne_salle)
{
    t_niveau * niveau = moteur->niveau_charge;
    t_liste * liste_entites = moteur->liste_entites;
    int direction_x, direction_y;

    //Sauver les entités de l'ancienne salle
    viderEntitesDeListe(liste_entites, infos_niveau->liste_infos_entites, infos_niveau->nb_infos_entite, id_ancienne_salle);

    //Charger les entités de la nouvelle salle
    chargerEntitesVersListe(liste_entites, infos_niveau->liste_infos_entites, infos_niveau->nb_infos_entite, niveau->salle_chargee->id_salle);

    //Detruire anciennes collisions
    if(niveau->collisions != NULL)
    {
        free(niveau->collisions);
        niveau->collisions = NULL;
        niveau->taille_collisions = 0;
    }

    //Caluler future position de la caméra
    updateFutureCamera(moteur, niveau->salle_chargee->dimensions->largeur, niveau->salle_chargee->dimensions->hauteur, niveau->salle_chargee->dimensions->j, niveau->salle_chargee->dimensions->i, joueur->x, joueur->y);

    //Animer tant que la caméra n'atteint pas son objectif
    while(moteur->camera->x != moteur->camera->futur_x || moteur->camera->y != moteur->camera->futur_y)
    {
        regulerFPS(moteur);

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
        renduEntites(moteur);

        if(joueur->flags->map_showing == 1)
            dessiner_map(moteur, infos_niveau, niveau->salle_chargee->id_salle);

        SDL_RenderPresent(moteur->renderer);
    }

    //Reset la future position
    moteur->camera->futur_x = 0;
    moteur->camera->futur_y = 0;
}


/**
 * \brief Phase de gameplay principale. Lance un niveau
 * 
 * \param moteur Moteur du jeu
 * \param joueur Le joueur
 * 
 * \return L'action ayant mis fin au niveau.
 */
static int jouerNiveau(t_moteur * moteur, t_joueur * joueur, niveau_informations_t * infos_niveau)
{
    //Variables pour faciliter les appels
    t_niveau * niveau = moteur->niveau_charge;
    t_liste * liste_entites = moteur->liste_entites;


    t_entite * entite_courante;
    int id_ancienne_salle = 0;
    int code_sortie = 0;

    
    //Charger les entités de la salle
    chargerEntitesVersListe(liste_entites, infos_niveau->liste_infos_entites, infos_niveau->nb_infos_entite, niveau->salle_chargee->id_salle);
    
    //Traiter les événements
    while((code_sortie = handleEvents(joueur, &moteur->parametres)) == NIVEAU_CONTINUER)
    {
        regulerFPS(moteur);
        updateEchelle(moteur);

    // ~~~ LOGIQUE

        // --- Actualiser l'état du joueur ---
        en_tete(liste_entites);
        joueur->update(moteur, (t_entite*) joueur, joueur->x, joueur->y); //Joueur

        // --- Actualiser l'état des entités ---
        en_tete(liste_entites);
        if(!liste_vide(liste_entites)) //Liste
        {
            while(!hors_liste(liste_entites))
            {
                valeur_elt(liste_entites, &entite_courante);
                if(entite_courante != NULL && entite_courante->update != NULL)
                {
                    if(entite_courante->update(moteur, entite_courante, joueur->x, joueur->y) == -1)
                    {
                        if(entite_courante->type == E_MONSTRE)
                        {
                            //Particule pour indiquer la mort du monstre
                            ajouterEntiteListe(liste_entites, (t_entite*) creerParticule(P_MORT, entite_courante->x, entite_courante->y, moteur->textures->particules));
                            //Ajouter l'xp gagné au joueur
                            int xp_lache = de(5);
                            for(int xp = 0; xp < xp_lache; xp++)
                                ajouterEntiteListe(liste_entites, (t_entite*) creerParticule(P_XP, entite_courante->x, entite_courante->y, moteur->textures->particules));
                            joueur->xp += xp_lache;
                        }

                        entite_courante->detruire((t_entite**) &entite_courante);
                        oter_elt(liste_entites);
                    }
                }
                if(hors_liste(liste_entites))
                    en_tete(liste_entites);
                else
                    suivant(liste_entites);
                entite_courante = NULL;
            }
        }

        // --- Faire subir les dégâts par les projectiles ou réaliser une interaction ---
        en_tete(liste_entites);
        if(!liste_vide(liste_entites))
        {
            while(!hors_liste(liste_entites))
            {
                //Dégâts projectiles
                valeur_elt(liste_entites, &entite_courante);
                if(entite_courante != NULL && entite_courante->type == E_PROJECTILE)
                {
                    if(faireDegats((t_projectile*) entite_courante, joueur, liste_entites) == -1)
                    {
                        ajouterEntiteListe(liste_entites, (t_entite*) creerParticule(P_TOUCHE, entite_courante->x, entite_courante->y, moteur->textures->particules));
                        entite_courante->detruire((t_entite**) &entite_courante);
                        oter_elt(liste_entites);
                    }
                }
                
                //Interactions
                if(entite_courante != NULL && entite_courante->type == E_INTERACTION)
                {
                    int interact = interagir((t_interaction*) entite_courante, joueur);
                    if(interact != 0) //Si une interaction a eu lieu
                    {
                        //Lancer un feedback au joueur
                        ajouterEntiteListe(liste_entites, (t_entite*) creerParticule(P_MORT, entite_courante->x, entite_courante->y, moteur->textures->particules));

                        //Si l'interaction est unique, la détruire
                        if(interact == -1)
                        {
                            entite_courante->detruire((t_entite**) &entite_courante);
                            oter_elt(liste_entites);
                        }
                    }
                }

                if(hors_liste(liste_entites))
                    en_tete(liste_entites);
                else
                    suivant(liste_entites);
                entite_courante = NULL;
            }
        }


        // --- Changement de salle si nécessaire ---
        id_ancienne_salle = niveau->salle_chargee->id_salle;
        updateNiveau(niveau, joueur->x, joueur->y, moteur->echelle);
        if(id_ancienne_salle != niveau->salle_chargee->id_salle)
            transitionChangementSalle(moteur, joueur, infos_niveau, id_ancienne_salle);


    // ~~~ RENDU

        //Actualiser caméra
        updateCamera(moteur, niveau->salle_chargee->dimensions->largeur, niveau->salle_chargee->dimensions->hauteur, niveau->salle_chargee->dimensions->j, niveau->salle_chargee->dimensions->i, joueur->x, joueur->y);
        
        
        //Rendu niveau
        afficherNiveau(moteur, joueur->x, joueur->y);


        //Rendu joueur et entites
        dessinerEntite(moteur, (t_entite*) joueur);
        renduEntites(moteur);


        //Map
        if(joueur->flags->map_showing == 1)
            dessiner_map(moteur, infos_niveau, niveau->salle_chargee->id_salle);

        //Afficher frame
        SDL_RenderPresent(moteur->renderer);
        SDL_RenderClear(moteur->renderer);
    }

    //Sauver l'état des entités
    viderEntitesDeListe(liste_entites, infos_niveau->liste_infos_entites, infos_niveau->nb_infos_entite, niveau->salle_chargee->id_salle);

    return code_sortie;
}





/* ################################ Fonctions de lancement de niveau ################################ */


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
    t_niveau * niveau;
    e_code_main code_sortie;
    int ancien_indice_niveau_charge;

    do
    { 
        //Charger le niveau  
        if(chargerNiveau(moteur, infos_niveaux[indice_niveau_charge]) != 0)
        {
            printf("Erreur lors du chargement du niveau\n");
            return -1;
        }
        niveau = moteur->niveau_charge;
        if(joueur->x == 0 && joueur->y == 0) //Si la position du joueur est vierge, placer le joueur sur la map
        {
            joueur->x = niveau->salle_chargee->dimensions->j*NB_TILE_LARGEUR + NB_TILE_LARGEUR / 2; 
            joueur->y = niveau->salle_chargee->dimensions->i*NB_TILE_HAUTEUR + NB_TILE_HAUTEUR / 2;
        }

        //Jouer le niveau
        code_sortie = jouerNiveau(moteur, joueur, infos_niveaux[indice_niveau_charge]);
    
        //Fin du niveau
        infos_niveaux[indice_niveau_charge]->i_dep = niveau->i_charge;
        infos_niveaux[indice_niveau_charge]->j_dep = niveau->j_charge;
        detruireNiveau(&niveau);

        ancien_indice_niveau_charge = indice_niveau_charge;
        if(code_sortie == M_NIVEAU)
            code_sortie = afficherMenuNiveau(&indice_niveau_charge, moteur, infos_niveaux, nb_niveaux, ancien_indice_niveau_charge);

        //Changer de niveau si souhaité
        switch (code_sortie)
        {
        case NIVEAU_CHANGER:
            if(ancien_indice_niveau_charge != indice_niveau_charge)
            {
                joueur->x = 0;
                joueur->y = 0;
            }
            break;
 
        case JEU_QUITTER:
        case M_PRINCIPAL:
            break;

        default:
            printf("Code inconnu\n");
            code_sortie = M_PRINCIPAL;
            break;
        }


    }while(code_sortie != M_PRINCIPAL && code_sortie != JEU_QUITTER);

    //Fin de du jeu
    sauvegarderJoueur(joueur);
    sauvegarderPartie(moteur->galaxie, infos_niveaux, nb_niveaux, indice_niveau_charge);

    if(moteur->galaxie != NULL)
        free(moteur->galaxie);
    moteur->galaxie = NULL;

    for(int i = 0; i < nb_niveaux; i++)
        detruire_niveau_info(&infos_niveaux[i]);
        
    free(infos_niveaux);
    detruireJoueur(&joueur);

    return code_sortie;
}





/* ################################ Fonctions de lancement de partie  ################################ */


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
static int genererPartie(int nb_niveaux, niveau_informations_t *** adr_infos, char ** nom_galaxie)
{
    int i;
    
    niveau_informations_t ** infos = malloc(sizeof(niveau_informations_t*)*nb_niveaux);
    if(infos == NULL)
    {
        printf("Impossible d'allouer la mémoire pour les infos des niveaux\n");
        return -1;
    }

    
    //Générer un nom de partie et le nom des niveaux
    *nom_galaxie = creer_nom(5 + de(5));
    if(nom_galaxie == NULL)
        return -1;

    char ** noms_planetes = creer_noms_planetes(*nom_galaxie, nb_niveaux);
    if(noms_planetes == NULL)
    {
        printf("Impossible de générer une partie\n");
        free(*nom_galaxie);
        free(infos);
        return -1;
    }

    for(i = 0; i < nb_niveaux; i++)
    {
        infos[i] = creer_niveau_info(noms_planetes[i]);

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
            detruireNomsPlanetes(&noms_planetes, nb_niveaux);
            free(noms_planetes);
            free(*nom_galaxie);
            *nom_galaxie = NULL;
            free(infos);
            return -1;
        }
    }
    
    free(noms_planetes);
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
    srand(time(NULL));
    retour = genererPartie(nb_niveaux, &infos, &moteur->galaxie);
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
        free(moteur->galaxie);
        moteur->galaxie = NULL;
        free(infos);
        return M_PRINCIPAL;
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
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Attention", "Impossible de charger la sauvegarde du joueur.\nVeuillez lancer une nouvelle partie avec RESET JOUEUR sélectionné.", moteur->window);
            for(int i = 0; i < nb_niveaux; i++)
                detruire_niveau_info(&infos[i]);
            free(moteur->galaxie);
            moteur->galaxie = NULL;
            free(infos);
            detruireJoueur(&joueur);
            return M_PRINCIPAL;
        }
        joueur->x = 0;
        joueur->y = 0;
    }

    //Sauvegarde de la partie générée
    sauvegarderPartie(moteur->galaxie, infos, nb_niveaux, 0);
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
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Attention", "Impossible de charger la sauvegarde du joueur.\nVeuillez lancer une nouvelle partie avec RESET JOUEUR sélectionné.", moteur->window);
        detruireJoueur(&joueur);
        return M_PRINCIPAL;
    }

    //Charger partie
    if(chargerSavePartie(&moteur->galaxie, &infos, &nb_niveaux, &indice_niveau_charge) != 0)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Attention", "Impossible de charger la sauvegarde de la partie.\nVeuillez lancer une nouvelle partie.", moteur->window);
        detruireJoueur(&joueur);
        return M_PRINCIPAL;
    }
    
    return jouerPartie(moteur, joueur, infos, nb_niveaux, indice_niveau_charge);
}