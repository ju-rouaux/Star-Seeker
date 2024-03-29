/**
 * \file generation_noms.c
 * 
 * \brief Générateur de nom de planète et de galaxie aléatoire
 *
 * \author Camille Remoué
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <outils.h>
#include <generation_noms.h>
#include <generation_niveau.h>
#include <string.h>



/**
 * \brief Prend une lettre en entrée, et renvoie une autre lettre qui "sonne bien" pour former un mot.
 * 
 * \param chances la matrice de fréquences de chaque lettre après chaque autre dans le dictionnaire
 * \param c1 la lettre précédente
 * 
 * \return la lettre qui va suivre c1.
 */
static char lettre_suivante(int chances[26][26], char c1)
{
    int cptTotal = 0;

    //Comptage du nombre total d'occurences de la lettre c1 (donc en position "caractère précédent") dans la matrice chance
    for (int i = 0; i < 26; i++)
        cptTotal += chances[c1 - 'a'][i];


    int suiv = rand() % cptTotal;

    char c2 = 'a';  //caractère suivant 
    suiv -= chances[c1 - 'a'][0];

    while(suiv > 0){
        c2++;
        suiv -= chances[c1 - 'a'][c2 - 'a'];    
    }

    return c2;
}


/**
 * \brief Crée un nom semblable au français et à l'anglais aléatoirement.
 * 
 * \param taille_mot Nombre de lettres du nom généré
 * 
 * \return le nom généré
 */
char * creer_nom(int taille_mot)
{

     int chances[26][26] = {

    /*A*/    {3,   7971,  10835,   5022,     41,   3528,  10019,    515,  65407,    664,    125,  20461,   8648,  33377,    283,   9251,   1950,  23247,  54297,  18253,   8613,   4921,     63,    671,   1919,    731},

    /*B*/    {8390,    100,      9,    164,   3023,      2,      0,     39,   6344,    283,      6,   5926,     47,     45,   9167,      0,      0,   7069,    784,    182,   2351,    200,      0,      0,     88,      0},

    /*C*/    {15368,      2,   3011,     10,   8371,      7,      1,  22394,   8838,      0,    407,   5045,      9,     20,  24942,      2,    511,   7651,    186,   6459,   5742,      0,      0,      0,    553,      9},

    /*D*/     {6513,     10,      4,     84,   9920,      0,    183,     86,  13483,    258,      2,     87,    309,     57,   5182,      0,      0,   4200,    524,      0,   2535,     41,     45,      0,    260,      7},

    /*E*/    {3551,   1311,   7071,   1097,     68,   1926,    888,     62,   3008,    236,      9,   8902,  13472,  66762,    794,   2632,    192,  90016,  64761,   8403,  10638,   2761,     53,   4947,    224,  33127},

    /*F*/    {4820,      0,      0,      0,   3729,   6172,      4,      3,  10292,      4,      4,   4241,      0,      2,   5504,      0,      0,   5035,    487,    144,   1888,      0,      0,      0,      0,      0},

    /*G*/     {5596,      4,      0,     16,  11893,      2,    264,     58,   4294,      0,      0,   2691,    488,   4960,   4804,      0,      0,   8049,    160,     99,   6632,      0,      2,      0,    103,     38},

    /*H*/    {11163,      4,      0,      2,   7348,      0,      0,      0,   5432,      0,      2,    354,    110,    245,   5047,      3,      0,   1175,     94,    163,   1586,      0,      2,      0,   1437,      2},

    /*I*/    {8279,   2829,   8780,   4699,  49346,   8559,   7828,     60,    596,     63,     49,  21912,   7585,  30417,  31379,   2968,   6329,  12789,  58833,  27604,    317,   5175,      4,    376,      0,    175},

    /*J*/    {1371,      0,      0,      0,   1051,      0,      0,      0,     18,      0,      1,      0,      0,      0,   1814,      0,      0,      0,      0,      0,   1620,      0,      0,      0,      0,      0},

    /*K*/     {290,     41,      2,      0,    283,      8,      3,     63,    343,      0,      8,     59,      6,     10,     65,      4,      0,     29,     86,      4,     15,      3,      1,      0,     85,      0},

    /*L*/   {25036,    218,    875,    188,  25084,    533,    424,     67,  24959,      0,     84,  21536,    632,     26,  13268,    744,    219,      0,   1288,   1912,   4844,    381,      5,      0,   1042,     14},

    /*M*/   {15446,   6143,      0,      4,  21598,      0,      1,      4,   9675,      0,      2,      4,   4010,    425,   8950,   8920,      2,      2,    358,     18,   3136,     24,      2,      0,    347,      0},

    /*N*/   {17450,     15,  11673,  10336,  19638,   3684,   7220,    356,  13807,    774,     97,    551,     38,  17997,   6647,     52,   1011,    938,  44489,  74231,   2086,   2488,      0,     15,    113,    211},

    /*O*/     {414,   2680,   5447,   2796,    473,    972,   4162,    198,   6922,     64,    105,  10304,   9604,  79092,    486,   4900,   1860,  16346,   6730,   9990,  28704,   1046,     46,    652,   1985,    151},

    /*P*/   {14209,      0,      4,      0,   9218,      3,      0,   4416,   8621,      0,      0,   6568,      2,    102,  11184,   4014,      0,  10324,    789,   2231,   2644,      0,      0,      0,    250,      0},

    /*Q*/       {0,      0,      0,      0,      0,      0,      0,      0,      4,      0,      0,      0,      0,      0,      0,      0,      0,      0,      1,      0,  17040,      0,      0,      0,      0,      0},

    /*R*/   {75564,   2642,   4600,   6718,  54543,   1046,   4079,    481,  42329,    242,    109,   1265,   4455,   3804,  32818,   1892,    913,   6047,   5586,   5940,   4111,   1510,     12,     50,    406,     29},

    /*S*/   {23214,    213,   5141,     12,  47291,    309,    100,    875,  26021,     85,    110,    360,   2223,    107,  11188,   3539,   1161,     10,  53656,  14872,   8088,     97,     58,      0,   1159,      0},

    /*T*/   {23612,     11,    267,     43,  38008,      2,      6,   2722,  30851,      0,      0,     38,     31,     20,  10964,     43,      0,  21839,   4208,   8036,   6429,      1,     46,      0,    810,     31},

    /*U*/    {7287,   2953,   4856,   2996,  14656,   2115,   2200,     51,  10698,    106,     39,  11007,   3885,   2160,    657,   3674,    433,  21792,  11408,   8885,     14,   2601,      2,   1750,    230,     55},

    /*V*/    {6862,      0,      0,      0,   9279,      0,      0,      0,   8038,      0,      2,      1,      0,      2,   3750,      0,      0,   1675,      1,      0,    510,      0,      0,      0,      1,      2},

    /*W*/     {174,      2,      0,      0,     60,      0,      0,     13,    162,      0,      2,     46,      0,     12,     24,      0,      0,      6,     11,      0,      6,      0,      0,      0,      2,      0},

    /*X*/     {788,      0,    697,      2,    623,     46,      0,    267,   1007,      0,      0,      0,      4,      0,    290,   1166,      6,      0,     47,    965,    230,      0,      2,      0,    385,      0},

    /*Y*/    {1884,     62,    706,    702,   1054,      4,    212,      2,    250,      2,      0,    778,    578,    838,    545,    931,      6,    517,   1020,    429,     22,      4,      4,     60,      0,     12},

    /*Z*/     {349,      1,      0,      1,    247,      0,      0,      0,    558,      0,      0,     10,      2,      2,    823,      0,      0,      0,      4,      2,    111,      0,      4,      0,     41,     75}};

    
    char * mot = malloc(sizeof(char) * (taille_mot+1));
    
    if(mot == NULL)
    {
        printf("Fail allocation mémoire pour générer un nom\n");
        return NULL;
    }

    char c1 = rand() % 26 + 'a';
    char c2;

    *(mot) = c1;

    int i;
    for (i = 1; i < taille_mot; i++){

        c2 = lettre_suivante(chances, c1);
        c1 = c2;
        
        *(mot + i) = c2;
    }

    *(mot + i) = '\0';

    return mot;
}


/**
 * \brief Détruit la mémoire allouée pour le tableau de chaines de noms de planètes.
 * 
 * \param noms_planetes L'adresse du tableau de chaines à libérer
 * \param nombre Le nombre de chaines du tableau
 */
void detruireNomsPlanetes(char *** noms_planetes, int nombre)
{
    if(*noms_planetes != NULL)
    {
        for(int i = 0; i < nombre; i++)
        {
            free((*noms_planetes)[i]);
            (*noms_planetes)[i] = NULL;
        }
        free(*noms_planetes);
    }
    *noms_planetes = NULL;
}


/**
 * \brief Crée des noms de planètes à partir d'une seed (nom de galaxie)
 * 
 * \param nombre le nombre de noms à générer
 * \param nom_galaxie nom qui va générer la seed
 * \return char** tableau de chaines de caractères contenant les noms de planètes
 */
char ** creer_noms_planetes(char * nom_galaxie, int nombre)
{
    if(nom_galaxie == NULL)
    {
        printf("Nom de galaxie inexistante\n");
        return NULL;
    }

    char ** noms_planetes = malloc(sizeof(char*) * nombre);
    if(noms_planetes == NULL)
    {
        printf("Erreur allocation nom_planètes\n");
        return NULL;
    }

    srand(seed_depuis_mot(nom_galaxie));

    for (int i = 0; i < nombre; i++)
    {
        noms_planetes[i] = creer_nom(de(7) + 2);
        if(noms_planetes[i] == NULL)
        {
            printf("Noms planètes non générés\n");
            i--;
            while(i >= 0)
            {
                free(noms_planetes[i]);
                i--;
            }
            return NULL;
        }
    }

    return noms_planetes;
}