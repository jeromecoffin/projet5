#ifndef SDLPART_H_INCLUDED
#define SDLPART_H_INCLUDED

#include "Structures.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>        //Bibliothèque SDL
#include <SDL_image.h>  //Bibliothèque permettant d'afficher des images pour la SDL
#include <SDL_ttf.h>    //Bibliothèque permettant d'écrire du texte avec la SDL
#undef main

char ecrire(char buffer[20], SDL_Surface *ecran, SDL_Surface *fond, int x, int y, int xFond, int yFond, int taille);
char ecrireChiffre(char chiffre[10], SDL_Surface *ecran, SDL_Surface *fond, int x, int y, int xFond, int yFond, int taille);
char ecrireDate(char chiffre[10], SDL_Surface *ecran, SDL_Surface *fond, int x, int y, int xFond, int yFond, int taille);
int dansZone(SDL_Event event, int x, int y, int x2, int y2);
int saisieType(SDL_Event event, SDL_Surface *ecran);
People personne(SDL_Surface *ecran, SDL_Surface *fond, People humain);
int saisieNbActeurs(SDL_Event event, SDL_Surface *ecran);
Film ajouterFilm(Film film);
void afficherFilm(Film film);
int menuPrincipal();
void afficherListe(int nbFilms, char listeFilms[10][20]);
void recherche();




#endif // SDLPART_H_INCLUDED
