#ifndef MYSQLPART_H_INCLUDED
#define MYSQLPART_H_INCLUDED

#include "Structures.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <winsock.h>
#include <MYSQL/mysql.h>
#undef main

People addPeople(void);
void viderBuffer(void);
People InitNull(void);
Film addFilm(Film Film);
void entrer_Film_BDD(MYSQL mysql, Film Film);
void entrer_Realisateur_BDD(MYSQL mysql, People personne);
void afficherTable_Acteurs_Realisateurs(MYSQL mysql);
void afficherTable_Films(MYSQL mysql);
void supprimer_Film(MYSQL mysql, Film monFilm);
void supprimer_Acteurs_Realisateurs(MYSQL mysql, People personne);
void obtenir_titre(MYSQL mysql, char titre[][20]);




#endif // MYSQLPART_H_INCLUDED
