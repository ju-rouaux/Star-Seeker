#ifndef _JEU_MAIN_
#define _JEU_MAIN_

/**
 * \enum e_code_appel
 * \brief Codes d'appel des différents modules par le main.
 */
typedef enum {
    ERROR_MENU_TEXTURE = -12, ERROR_MENU = -11, //Erreurs menu
    M_PRINCIPAL = 1, M_JEU, M_NIVEAU, M_CHARGER, M_OPTIONS, M_KEYMAP, //Lancements modules
    JEU_QUITTER = 0, 
    NIVEAU_CONTINUER = 10, NIVEAU_CHANGER, JOUEUR_MORT
} e_code_main;

#endif //_JEU_MAIN_