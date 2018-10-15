//
//  Structures.h
//  miseenplace
//
//  Created by Jérôme COFFIN on 13/10/2018.
//  Copyright © 2018 Jérôme COFFIN. All rights reserved.
//

#ifndef Structures_h
#define Structures_h

typedef struct Film Film;       //Structure film
typedef struct People People;   //Structure personne

/* Sauf exception, toutes les variables sont des tableaux de char. La SDL ne permet pas d'afficher autre chose que des char avec SDL_TTF*/

struct People
{
    char nom[20];       //Nom d'une personne
    char prenom[20];    //Prenom d'une personne
    char ville[20];     //Ville de naissance
    char jour[10];      //Jour de la date de naissance
    char mois[10];      //Mois de la date de naissance
    char annee[10];     //Annee de naissance
};


struct Film
{
    char titre[20];     //titre du film
    char date[10];      //Date de sortie du film
    char duree[10];     //Duree du film
    //char buffer[6];
    int nbActeur;       //Nombre d'acteurs principaux
    People acteurs[4];  //Tableau de personnes pour les acteurs
    int type;           //Genre du film
    People realisateur; //Realisateur du film (qui utilise la structure People)
};

#endif /* Structures_h */
