#include "SDLPart.h"

/**La fonction ci-dessous permet d'écrire dans une zone de texte. Elle renvoie un tableau de char. En paramètre nous avons un tableau de char,
L'ecran qui permet d'avoir une fenêtre, des coordonées et la taille de la police**/

char ecrire(char buffer[20], SDL_Surface *ecran, SDL_Surface *fond, int x, int y, int xFond, int yFond, int taille)
{
    int i = 0;          //C'est un compteur

/* Les 3 lignes ci-dessous sont récurentes. Je vais les expliquer une fois ici et ne plus le faire. Elles permettent de caractériser une écriture*/

    SDL_Color noir = {0, 0, 0};             //On initialise la couleur de la police (ici noir)
    TTF_Font *police = NULL;                //On crée une variable police
    police = TTF_OpenFont("Angelina.ttf", taille);  //On ouvre la police qui porte le nom entre "" et qui se trouve dans le dossier du projet

    SDL_Surface *texte = NULL, *fleche = NULL;          //Ce sont des variables qui vont permettre d'afficher le texte et d'afficher une flèche de saisie
    SDL_Rect position, positionFond, positionFleche;    //Ce sont des variables qui vont permettre de contenir les coordonnées de chaque surface

    fleche = SDL_LoadBMP("fleche.bmp");                 //On charge l'image portant le nom entre ""
    SDL_SetColorKey(fleche, SDL_SRCCOLORKEY, SDL_MapRGB(fleche->format, 255, 255, 255));    //Les .bmp ne gère pas la transparence. Cette fonction le permet

    position.x = x;     //position de l'écriture
    position.y = y;

    positionFond.x = xFond;     //position du fond de saisie
    positionFond.y = yFond;

    positionFleche.x = x- 50;       //position de la flèche de saisie
    positionFleche.y = y + 20 ;

    SDL_BlitSurface(fleche, NULL, ecran, &positionFleche);      //On affiche la flèche sur l'écran
    SDL_Flip(ecran);                                            //On rafraichit l'ecran pour voir les changements

    SDL_Event event;        //Cette variable permet de gérer les évènements

    i=0;
    while(i < 20)       //On dit de faire les actions ci-dessous jusqu'à que le tableau soit rempli
    {
/* Les actions ci-dessous sont récurentes. Je vais les expliquer une fois de façon détaillée et le faire de façon plus souple par la suite*/

        SDL_WaitEvent(&event);    //On attend un évènement de la part de l'utilisateur
        switch(event.type)      //Ce switch nous permet de traiter les différents évènements qui peuvent arriver
        {
            case SDL_KEYUP:     //Si l'utilisateur appuie sur une touche
                           if((event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) || (event.key.keysym.sym == SDLK_SEMICOLON)) //On vérifie qu'il s'agisse d'une touche "lettre" ou ;
                           {
                               switch(event.key.keysym.sym) //Cette fonction sert de convertisseur car TTF ne gère pas l'azerty mais seulement le qwerty
                               {
                                   case SDLK_q : buffer[i] = 'a';           //Les lignes sont les différences entre azerty et qwerty
                                                 break;

                                   case SDLK_w : buffer[i] = 'z';
                                                 break;

                                   case SDLK_a : buffer[i] = 'q';
                                                 break;

                                   case SDLK_SEMICOLON : buffer[i] = 'm';
                                                         break;

                                   case SDLK_z : buffer[i] = 'w';
                                                 break;

                                   case SDLK_m : buffer[i] = ';';
                                                 break;

                                    default : buffer[i] = event.key.keysym.sym; //On rentre la lettre tapée dans le tableau par défaut
                                              break;
                               }

                                i++;      //On ajoute 1 pour continuer à remplir le tableau

                                if(i <= 20)
                                {
                                    //i++;
                                    buffer[i]='\0'; //On oublie pas de mettre un \0 à la fin, sinon on risque d'afficher ce qu'il y a en mémoire
                                }

                            }
                            else if(event.key.keysym.sym == SDLK_SPACE && i > 0)    //L'espace est autorisé
                            {
                                buffer[i] = ' ';
                                i++;

                                if(i < 20)
                                {
                                    buffer[i] = '\0';
                                }
                            }
                            else if(event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)   //Les chiffres sont également autorisés
                            {
                                buffer[i] = event.key.keysym.sym;
                                i++;
                                if(i < 20)
                                {
                                    buffer[i] = '\0';
                                }
                            }
                            else if(event.key.keysym.sym == SDLK_ESCAPE)    //Si l'utilisateur appuie sur échape, il arrête d'écrire
                            {
                                buffer[i] = '\0';
                                i = 21;

                                exit(0);
                            }
                            else if(event.key.keysym.sym == SDLK_BACKSPACE && i>0)  //L'utilisateur peut également effacer s'il a écrit quelque chose
                            {
                                buffer[--i]='\0';   //On enlève la dernière lettre
                            }
                            else if(event.key.keysym.sym == SDLK_RETURN)        //S'il appuie sur entrée, cela valide la saisie
                            {
                                buffer[i] = '\0';

                                SDL_FreeSurface(texte);     //Nous n'oublions pas de libérer la mémoire
                                SDL_FreeSurface(ecran);
                                SDL_Flip(ecran);

                                return buffer[20];  //Nous retournon le mot saisie s'il appuie sur echap
                            }

                            texte = TTF_RenderText_Blended(police, buffer, noir);   //Nous mettons le texte saisie dans une variable avec les parametres de la police

                            position.x = x;     //On initialise la position avec les paramètres de la fonction
                            position.y = y;

                            SDL_BlitSurface(fond, NULL, ecran, &positionFond);    //On affiche le fond d'écran
                            SDL_BlitSurface(texte, NULL, ecran, &position);         //On affiche le texte


                            SDL_FreeSurface(texte);     //On libère la mémoire qu'on a alloué
                            SDL_FreeSurface(ecran);
                            SDL_Flip(ecran);            //On rafraichit l'écran
                            break;

                case SDL_MOUSEBUTTONUP :            //Si l'utilisateur appuie n'importe où
                    {
                            buffer[i] = '\0';      //On oublie pas de terminer le mot

                            texte = TTF_RenderText_Blended(police, buffer, noir);  //On met le texte saisie dans une variable

                            position.x = x; //On initialise la position
                            position.y = y;

                            SDL_BlitSurface(fond, NULL, ecran, &positionFond);  //On initialise le fond d'écran
                            SDL_BlitSurface(texte, NULL, ecran, &position);     //On initialise le texte

                            SDL_FreeSurface(texte);     //On libère la mémoire alloué
                            SDL_FreeSurface(fleche);
                            SDL_Flip(ecran);            //On rafraichit l'écran

                            return buffer[20];      //On retourne le mot saisie
                            break;
                    }
                default : break;

            }   //fin switch

    } //Fin boucle while

}//Fin fontion

/**La fonction ci dessous a exactement la même fonction que celle d'au dessus mais en plus restreinte, elle ne permet que de taper des chiffres**/

char ecrireChiffre(char chiffre[10], SDL_Surface *ecran, SDL_Surface *fond, int x, int y, int xFond, int yFond, int taille)
{
    int i = 0;

    SDL_Event event;
/*Les lignes suivantes sont expliquée dans la fonction "Ecrire"*/
    SDL_Color noir = {0, 0, 0};
    TTF_Font *police = NULL;
    police = TTF_OpenFont("Angelina.ttf", taille);

    SDL_Surface *texte = NULL, *fleche = NULL;
    SDL_Rect position, positionFond, positionFleche;

    fleche = SDL_LoadBMP("fleche.bmp");
    SDL_SetColorKey(fleche, SDL_SRCCOLORKEY, SDL_MapRGB(fleche->format, 255, 255, 255));

    position.x = x;
    position.y = y;

    positionFond.x = xFond;
    positionFond.y = yFond;

    positionFleche.x = x - 50;
    positionFleche.y = y + 5;


    SDL_BlitSurface(fleche, NULL, ecran, &positionFleche);
    SDL_Flip(ecran);

    i=0;
    while(i <= 4)
    {
        SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_KEYUP :
                            if(event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)    //On s'assure que l'utilisateur rentre bien que des chiffres
                            {
                                chiffre[i] = event.key.keysym.sym;
                                i++;
                                if(i <= 5)
                                {
                                    chiffre[i] = '\0';
                                }

                            }
                            else if(event.key.keysym.sym == SDLK_BACKSPACE && i>0)      //On gère l'effacement
                            {
                                chiffre[--i]='\0';
                            }
                            else if(event.key.keysym.sym == SDLK_ESCAPE)        //On gère la touche echap
                            {
                                chiffre[i] = '\0';

                                texte = TTF_RenderText_Blended(police, chiffre, noir);

                                position.x = x;
                                position.y = y;


                                SDL_BlitSurface(fond, NULL, ecran, &positionFond);
                                SDL_BlitSurface(fleche, NULL, ecran, &positionFleche);
                                SDL_BlitSurface(texte, NULL, ecran, &position);

                                SDL_FreeSurface(texte);
                                SDL_FreeSurface(fond);
                                SDL_FreeSurface(ecran);

                                SDL_Flip(ecran);    //On rafraichit l'écran

                                return chiffre[10]; //On retourne le nombre saisie

                            }
                            else if(event.key.keysym.sym == SDLK_RETURN)        //On gère la touche entrée qui permet de valider la saisie
                            {
                                chiffre[i] = '\0';


                                SDL_FreeSurface(texte);
                                SDL_FreeSurface(ecran);
                                SDL_Flip(ecran);

                                return chiffre[10];     //On retourne la saisie
                            }

                            texte = TTF_RenderText_Blended(police, chiffre, noir);

                            position.x = x;
                            position.y = y;

                            SDL_BlitSurface(fond, NULL, ecran, &positionFond);
                            SDL_BlitSurface(fleche, NULL, ecran, &positionFleche);
                            SDL_BlitSurface(texte, NULL, ecran, &position);

                            SDL_FreeSurface(texte);
                            SDL_FreeSurface(ecran);

                            SDL_Flip(ecran);        //On rafraichit l'écran

                            break;

                case SDL_MOUSEBUTTONUP :        //Idem que la fonction précédent si l'utilisateur clique quelque part
                    {
                            chiffre[i] = '\0';

                            texte = TTF_RenderText_Blended(police, chiffre, noir);  //On copie la saisie dans une variable pour le texte

                            position.x = x;
                            position.y = y;

                            SDL_BlitSurface(fond, NULL, ecran, &positionFond);  //On affiche les images
                            SDL_BlitSurface(texte, NULL, ecran, &position);

                            SDL_FreeSurface(texte);
                            SDL_FreeSurface(ecran);
                            SDL_Flip(ecran);

                            return chiffre[10];     //On retourne la saisie
                            break;
                    }

                    default : break;
        }
    }

    return chiffre[10];
}

/**La fonction ci-dessous permet de saisir une date (2 chiffres) elle repose sur le même principe que les 2 fonctions ci-dessus**/
char ecrireDate(char chiffre[10], SDL_Surface *ecran, SDL_Surface *fond, int x, int y, int xFond, int yFond, int taille)
{
    int i = 0;

    SDL_Event event;

    SDL_Color noir = {0, 0, 0};
    TTF_Font *police = NULL;
    police = TTF_OpenFont("Angelina.ttf", taille);

    SDL_Surface *texte = NULL, *fleche = NULL;
    SDL_Rect position, positionFond, positionFleche;

    fleche = SDL_LoadBMP("fleche.bmp");
    SDL_SetColorKey(fleche, SDL_SRCCOLORKEY, SDL_MapRGB(fleche->format, 255, 255, 255));

    position.x = x;
    position.y = y;

    positionFond.x = xFond;
    positionFond.y = yFond;

    positionFleche.x = x - 50;
    positionFleche.y = y + 5;


    SDL_BlitSurface(fleche, NULL, ecran, &positionFleche);
    SDL_Flip(ecran);

    i=0;
    while(i < 2)        //L'unique différence avec la fonction du dessus est que l'utilisateur ne peut rentrer que 2 chiffres
    {
        SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_KEYUP :
                            if(event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)
                            {
                                chiffre[i] = event.key.keysym.sym;
                                i++;
                                if(i <= 2)
                                {
                                    chiffre[i] = '\0';
                                }
                            }
                            else if(event.key.keysym.sym == SDLK_BACKSPACE && i>0)
                            {
                                chiffre[--i]='\0';
                            }
                            else if(event.key.keysym.sym == SDLK_ESCAPE)
                            {
                                chiffre[i] = '\0';

                                texte = TTF_RenderText_Blended(police, chiffre, noir);

                                position.x = x;
                                position.y = y;

                                SDL_BlitSurface(fond, NULL, ecran, &positionFond);
                                SDL_BlitSurface(fleche, NULL, ecran, &positionFleche);
                                SDL_BlitSurface(texte, NULL, ecran, &position);

                                SDL_FreeSurface(texte);
                                SDL_FreeSurface(ecran);

                                SDL_Flip(ecran);

                                return chiffre[10];
                            }
                            else if(event.key.keysym.sym == SDLK_RETURN)
                            {
                                chiffre[i] = '\0';

                                SDL_FreeSurface(texte);
                                SDL_FreeSurface(ecran);
                                SDL_Flip(ecran);

                                return chiffre[10];
                            }

                            texte = TTF_RenderText_Blended(police, chiffre, noir);

                            position.x = x;
                            position.y = y;

                            SDL_BlitSurface(fond, NULL, ecran, &positionFond);
                            SDL_BlitSurface(fleche, NULL, ecran, &positionFleche);
                            SDL_BlitSurface(texte, NULL, ecran, &position);

                            SDL_FreeSurface(texte);
                            SDL_FreeSurface(ecran);

                            SDL_Flip(ecran);
                            break;

                    case SDL_MOUSEBUTTONUP :        //On gère les clic de souris
                    {
                            chiffre[i] = '\0';

                            texte = TTF_RenderText_Blended(police, chiffre, noir);

                            position.x = x;
                            position.y = y;

                            SDL_BlitSurface(fond, NULL, ecran, &positionFond);
                            SDL_BlitSurface(texte, NULL, ecran, &position);

                            SDL_FreeSurface(texte);
                            SDL_Flip(ecran);

                            return chiffre[10]; //On retourne les chiffres
                            break;
                    }

                    default : break;
        }
    }

    return chiffre[10]; //On retourne le chifre
}

/**La fonction ci dessous permet de vérifier que un évènement se passe dans une certaine zone grâce à des coordonnées en paramètre**/
int dansZone(SDL_Event event, int x, int y, int x2, int y2)
{
    if(event.button.x >= x && event.button.x <= x2 && event.button.y >= y && event.button.y <= y2) //On vérifie que le clic est dans une zone précise
    {
        return 1;   //Si oui, on retourne 1
    }
    else
    {
        return 0;   //Si non, on retourne 0
    }
}

/*La fonction d'en dessous permet de rentrer le genre du film. Elle se fait sous la forme d'un cochage*/
int saisieType(SDL_Event event, SDL_Surface *ecran)
{
    SDL_Surface *tick = NULL, *typeFilm = NULL, *next = NULL;     //On a donc tick = savoir quelle case est coché, typeFilm = le fond d'écran et le next = pour passer à l'écran suivant
    SDL_Rect positionTick, position, positionnext;

    typeFilm = SDL_LoadBMP("typeFilm.bmp");     //Pour les 3 prochaines lignes, on charges les images
    tick = SDL_LoadBMP("tick.bmp");
    next = SDL_LoadBMP("next.bmp");

    SDL_SetColorKey(tick, SDL_SRCCOLORKEY, SDL_MapRGB(tick->format, 255, 255, 255));    //Ici on gère la transparence de 2 images
    SDL_SetColorKey(next, SDL_SRCCOLORKEY, SDL_MapRGB(next->format, 255, 255, 255));

    position.x = 0;
    position.y = 0;

    positionTick.x = event.button.x - 15;
    positionTick.y = event.button.y - 15;

    positionnext.x = 945;
    positionnext.y = 540;

    SDL_BlitSurface(typeFilm, NULL, ecran, &position);  //On affiche le fond d'écran et on rafraichit l'écran
    SDL_Flip(ecran);

/*Pour tous les if qui suivent, nous vérifions seulement si l'utilisateur a cliqué dans une certaine zone et nous retournons un integer
Chaque integer correspond à un genre de film*/
        if(dansZone(event, 198, 128, 214, 233) == 1)
        {
            SDL_BlitSurface(tick, NULL, ecran, &positionTick);  //On affiche une image pour confirmer qu'une case est bien cochée
            SDL_BlitSurface(next, NULL, ecran, &positionnext);
            SDL_Flip(ecran);
            return 1;   //On retourne un nombre en fonction de l'endroit où c'est coché
        }
        else if(dansZone(event, 197, 177, 214, 292) == 1)
        {
            SDL_BlitSurface(tick, NULL, ecran, &positionTick);
            SDL_BlitSurface(next, NULL, ecran, &positionnext);
            SDL_Flip(ecran);
            return 2;
        }
        else if(dansZone(event, 198, 335, 214, 350) == 1)
        {
            SDL_BlitSurface(tick, NULL, ecran, &positionTick);
            SDL_BlitSurface(next, NULL, ecran, &positionnext);
            SDL_Flip(ecran);
            return 3;
        }
        else if(dansZone(event, 197, 388, 214, 402) == 1)
        {
            SDL_BlitSurface(tick, NULL, ecran, &positionTick);
            SDL_BlitSurface(next, NULL, ecran, &positionnext);
            SDL_Flip(ecran);
            return 4;
        }
        else if(dansZone(event, 631, 244, 649, 258) == 1)
        {
            SDL_BlitSurface(tick, NULL, ecran, &positionTick);
            SDL_BlitSurface(next, NULL, ecran, &positionnext);
            SDL_Flip(ecran);
            return 5;
        }
        else if(dansZone(event, 631, 308, 648, 322) == 1)
        {
            SDL_BlitSurface(tick, NULL, ecran, &positionTick);
            SDL_BlitSurface(next, NULL, ecran, &positionnext);
            SDL_Flip(ecran);
            return 6;
        }
        else if(dansZone(event, 631, 314, 648, 385) == 1)
        {
            SDL_BlitSurface(tick, NULL, ecran, &positionTick);
            SDL_BlitSurface(next, NULL, ecran, &positionnext);
            SDL_Flip(ecran);
            return 7;
        }
}

/*La fonction suivante nous permet de remplir les infos du realisateur*/
People personne(SDL_Surface *ecran, SDL_Surface *fond, People humain)  //On met en paramètre un fond d'écran et une personne
{
    SDL_Surface *caseNom = NULL, *caseDate = NULL, *caseAnnee = NULL, *lieuDeNaissance = NULL; //Ce sont toutes les surfaces pour afficher quelque chose

    SDL_Rect position;      //Position pour afficher

    SDL_Event event;
    int continuer = 1;
    int nomOK = 0, prenomOK = 0, lieuOK = 0, jourOK = 0, moisOK = 0, anneeOK = 0;   //Ces variables vont permettre de valider que toutes les infos sont bien rentrées

    caseNom = SDL_LoadBMP("caseRealisateur.bmp");       //On charge toutes les images
    lieuDeNaissance = SDL_LoadBMP("caseLieu.bmp");
    caseDate = SDL_LoadBMP("caseDate.bmp");
    caseAnnee = SDL_LoadBMP("annee.bmp");

    position.x = 0;
    position.y = 0;

    SDL_BlitSurface(fond, NULL, ecran, &position);  //On affiche le fond d'écran
    SDL_Flip(ecran);                    //On rafraichit l'écran

    while(continuer)        //On crée une boucle infinie pour que l'utilisateur puisse faire autant de changements qu'il veut
    {
        SDL_WaitEvent(&event);      //On attend un évènement

        switch(event.type)
        {
            case SDL_QUIT : exit(0);
                            break;

            case SDL_MOUSEBUTTONUP :
                            if(dansZone(event, 109, 270, 349, 336) == 1)    //Si le user clique dans une certaine zone
                            {
                                humain.prenom[20] = ecrire(humain.prenom, ecran, caseNom, 113, 273, 109, 270, 60);  //Il saisit le prenom du realisateur
                                prenomOK = 1;       //On dit que le prenom a bien été rentré
                            }
                            else if(dansZone(event, 623, 268, 868, 324) == 1)
                            {
                                humain.nom[20] = ecrire(humain.nom, ecran, caseNom, 628, 273, 623, 268, 60);    //le user saisit le nom du realisateur
                                nomOK = 1;      //Nom bien saisie
                            }
                            else if(dansZone(event, 299, 388, 658, 454) == 1)
                            {
                                humain.ville[20] = ecrire(humain.ville, ecran, lieuDeNaissance, 303, 394, 299, 388, 60);    //Saisie de la ville natale
                                lieuOK = 1;     //Ville bien saisie
                            }
                            else if(dansZone(event, 280, 499, 352, 552) == 1)
                            {
                                humain.jour[10] = ecrireDate(humain.jour, ecran, caseDate, 284, 504, 280, 499, 60);     //Saisie du jour de naissance
                                jourOK = 1;     //jour bien saisie
                            }
                            else if(dansZone(event, 417, 498, 490, 552) == 1)
                            {
                                humain.mois[10] = ecrireDate(humain.mois, ecran, caseDate, 423, 504, 417, 498, 60);     //Saisie du mois de naissance
                                moisOK = 1;         //mois bien saisie
                            }
                            else if(dansZone(event, 551, 497, 681, 551) == 1)
                            {
                                humain.annee[10] = ecrireChiffre(humain.annee, ecran, caseAnnee, 556, 504, 551, 497, 60);       //aSAisie de l'annee de naissance
                                anneeOK = 1;        //année saisie
                            }

                            if(nomOK == 1 && prenomOK == 1 && lieuOK == 1 && jourOK == 1 && moisOK == 1 && anneeOK == 1)    //Si tout a bien été siasie
                            {
                                return humain;      //On retourne la personne

                            }
                            break;

                    default : break;
            }//fin switch
        }//fin while

}

/** Cette fonction permet de saisir le nombre d'acteurs principaux. L'utilisateur va cocher une case.
Cette fonction est identique à celle qui permet de saisir le genre**/
int saisieNbActeurs(SDL_Event event, SDL_Surface *ecran)
{
    SDL_Surface *tick = NULL, *fond = NULL, *next = NULL;
    SDL_Rect positionTick, position, positionnext;

    fond = SDL_LoadBMP("nb_acteurs.bmp");       //Chargement des images
    tick = SDL_LoadBMP("tick.bmp");
    next = SDL_LoadBMP("next.bmp");

    SDL_SetColorKey(tick, SDL_SRCCOLORKEY, SDL_MapRGB(tick->format, 255, 255, 255));  //On gère la transparence
    SDL_SetColorKey(next, SDL_SRCCOLORKEY, SDL_MapRGB(next->format, 255, 255, 255));

/*On définit les positions*/
    position.x = 0;
    position.y = 0;

    positionTick.x = event.button.x - 15;
    positionTick.y = event.button.y - 15;

    positionnext.x = 945;
    positionnext.y = 540;

    SDL_BlitSurface(fond, NULL, ecran, &position);  //On affiche le fond d'écran
    SDL_Flip(ecran);                        //On rafraichit l'écran

        if(dansZone(event, 223, 336, 241, 350) == 1)        //Si le user clique dans une certaine zone
        {
            SDL_BlitSurface(tick, NULL, ecran, &positionTick);      //On confirme que la case est cochée
            SDL_BlitSurface(next, NULL, ecran, &positionnext);
            SDL_Flip(ecran);
            return 1;                        //On retourne 1 (pour 1 acteur principal)
        }
        else if(dansZone(event, 400, 336, 416, 350) == 1)
        {
            SDL_BlitSurface(tick, NULL, ecran, &positionTick);
            SDL_BlitSurface(next, NULL, ecran, &positionnext);
            SDL_Flip(ecran);
            return 2;       //2 acteurs principaux
        }
        else if(dansZone(event, 557, 335, 572, 350) == 1)
        {
            SDL_BlitSurface(tick, NULL, ecran, &positionTick);
            SDL_BlitSurface(next, NULL, ecran, &positionnext);
            SDL_Flip(ecran);
            return 3;           //3 acteurs principaux
        }
        else if(dansZone(event, 703, 335, 717, 350) == 1)
        {
            SDL_BlitSurface(tick, NULL, ecran, &positionTick);
            SDL_BlitSurface(next, NULL, ecran, &positionnext);
            SDL_Flip(ecran);
            return 4;           //4 acteurs principaux
        }
        else if(dansZone(event, 465, 435, 481, 448) == 1)
        {
            SDL_BlitSurface(tick, NULL, ecran, &positionTick);
            SDL_BlitSurface(next, NULL, ecran, &positionnext);
            SDL_Flip(ecran);
            return 0;       //Il n'y a pas d'acteur
        }

    return -1;
}

/**La fonction ci-dessous permet d'ajouter un nouveau film**/
Film ajouterFilm(Film film) //Il y a un Film en paramètre
{
    film.type = 0;      //On initialise d'abbord le genre et le nombre d'acteurs à 0
    film.nbActeur = 0;
    int continuer = 1, continuer1 = 1, continuer2 = 1, continuer3 = 1, continuer4 = 1;  //ces variables nous permettent de créer les boucles infinies
    int i = 0; //compteur pour les acteurs

        int titreOK = 0, dateOK = 0, dureeOK = 0, nomOK = 0, prenomOK = 0, reaOK = 0, nbOK = 0; //Ces variables nous permettent de faire les vérifications comme quoi tout est bien saisis

        SDL_Surface *ecran = NULL, *ajouterFilm = NULL, *typeFilm = NULL, *next = NULL, *acteur = NULL, *caseNom = NULL; //Surface pour afficher quelque chose
        SDL_Surface *rectangle = NULL, *casePage1 = NULL;       //idem
        SDL_Surface *fondRea = NULL;
        SDL_Rect position, positionnext;        //Les différentes positions dont on a besoin
        TTF_Init();                                     //on initialise la SDL qui permet d'afficher du text

/*On initialise les différentes position nécessaires*/
        position.x = 0;
        position.y = 0;

        positionnext.x = 945;
        positionnext.y = 540;

        SDL_Event event, event2, event3, event4, event5;        //LEs différents évènement dont nous avont besoin

        TTF_Font *police = NULL;                //On initialise la police
        police = TTF_OpenFont("Angelina.ttf", 50);

        ecran = SDL_SetVideoMode(1024, 576, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);     //On crée une surface
        next = SDL_LoadBMP("next.bmp");             //On charge toute les images dont on a besoin
        typeFilm = SDL_LoadBMP("typeFilm.bmp");
        rectangle = SDL_LoadBMP("titre.bmp");
        casePage1 = SDL_LoadBMP("case.bmp");
        acteur = SDL_LoadBMP("acteur.bmp");
        caseNom = SDL_LoadBMP("caseRealisateur.bmp");
        ajouterFilm = SDL_LoadBMP("ajouter.bmp");
        fondRea = SDL_LoadBMP("rea.bmp");

        SDL_SetColorKey(next, SDL_SRCCOLORKEY, SDL_MapRGB(next->format, 255, 255, 255));    //On gère la transparence d'une certaine image

        if(ecran == NULL) //On v�rifie que la SDL s'ouver bien
        {
                printf("Erreur dans le chargement de la SDL : %s \n", SDL_GetError()); //On affiche le code erreur en cas d'erreur

                exit(EXIT_FAILURE);
        }

        SDL_WM_SetCaption("BEST PROGRAM EVER", NULL);   //Nom de la fenêtre

        /* On blitte par-dessus l'�cran */

        SDL_BlitSurface(ajouterFilm, NULL, ecran, &position);   //On affiche l'image
        SDL_Flip(ecran);        //On rafraichit l'écran

        while(continuer)    //Boucle infinie pour que l'utilisateur fasse ce dont il a envie
        {
            SDL_WaitEvent(&event);  //On attend une action

            switch(event.type)
            {
                case SDL_QUIT: exit(0);
                                break;

                case SDL_MOUSEBUTTONUP:
                                        if(dansZone(event, 222, 111, 800, 280) == 1)    //Si il clique dans cette zone
                                        {
                                            film.titre[20] = ecrire(film.titre, ecran, rectangle, 236, 210, 222, 212, 70);  //Il saisit le titre du film
                                            titreOK = 1;        //Le titre est bien saisie
                                        }
                                        else if(dansZone(event, 67, 371, 352, 425) == 1)
                                        {
                                            film.date[10] = ecrireChiffre(film.date, ecran, casePage1, 76, 377, 67, 371, 60);   //Saisie de la date de sortie
                                            dateOK = 1;         //Date bien saisie
                                        }
                                        else if(dansZone(event, 621, 373, 906, 426) == 1)
                                        {
                                            film.duree[10] = ecrireChiffre(film.duree, ecran, casePage1, 630, 379, 621, 373, 60);   //Saisie de la durée du film
                                            dureeOK = 1;        //durée bien saisie
                                        }

                                        if(titreOK == 1 && dateOK == 1 && dureeOK == 1) //Si toutes les infos sont bien saisies
                                        {
                                            SDL_BlitSurface(next, NULL, ecran, &positionnext);  //On affiche une flèche pour passer à l'écran suivant
                                            SDL_Flip(ecran);

                                            if(dansZone(event, 932, 545, 1021, 573) == 1)   //Si il clique sur la flèche
                                            {
                                                continuer = 0;  //On sort de la première boucle
                                            }

                                        }
                                    break;

                   case SDL_KEYUP : if(event.key.keysym.sym == SDLK_ESCAPE) //s'il appuie sur echap
                                    {
                                        exit(0);    //On quitte la fonction
                                    }
                                    break;
                default: break;

                }

        }   // accolade du premier while


        while(continuer1)   //2e boucle infini pour le 2e ecranà&
        {
            SDL_WaitEvent(&event2);

            switch(event2.type)
            {
                case SDL_QUIT : exit(0);
                                break;

                case SDL_MOUSEBUTTONUP :
                                if(film.type != 0 && dansZone(event2, 932, 545, 1021, 573) == 1)
                                {
                                    continuer1 = 0;
                                }
                                else
                                {
                                    film.type = saisieType(event2, ecran);
                                }


                            break;

            }   //accolade du switch

        }

        film.realisateur = personne(ecran, fondRea, film.realisateur);   //On saisie les infos pour le réalisateur
        reaOK = 1;  //La saisie s'est bien déroulée
        SDL_BlitSurface(next, NULL, ecran, &positionnext);  //On affiche le bouton pour passer à l'étape suivante
        SDL_Flip(ecran);

        while(continuer2)   //3e boucle infinie
        {
            SDL_WaitEvent(&event3);

            switch(event3.type)
            {
                case SDL_QUIT : continuer2 = 0;
                                break;

                case SDL_MOUSEBUTTONUP :
                                    if(reaOK == 1)
                                    {
                                        if(dansZone(event3, 932, 545, 1021, 573) == 1)
                                        {

                                            continuer2 = 0;
                                        }
                                    }


                                break;

            }

        }

        if(film.type != 6)  //On vérifie que ce n'est pas un film d'animation
        {
            while(continuer3)   //4e boucle infinie
            {
                SDL_WaitEvent(&event4);

                switch(event4.type)
                {
                    case SDL_QUIT : exit(0);
                                    break;

                    case SDL_MOUSEBUTTONUP :
                                if( nbOK != 0 &&dansZone(event4, 932, 545, 1021, 573) == 1) //Si le nombre est bien rentré et qu'il clique sur next
                                {
                                    continuer3 = 0; //On sort de la boucle
                                }
                                else
                                {
                                    film.nbActeur = saisieNbActeurs(event4, ecran); //Le user choisit le nombre d'acteur
                                    nbOK = 1;   //Le nombre a bien été coché
                                }
                                    break;

                }   //accolade du switch
             }//fin while 1
        } //fin if


        if(film.nbActeur != 0)  //Si le nombre d'acteurs est différent de 0
        {
            while(i < film.nbActeur)    //On remplit le tableau d'acteur autant qu'il y a d'acteur
            {
                film.acteurs[i] = personne(ecran, acteur, film.acteurs[i]);
                SDL_BlitSurface(next, NULL, ecran, &positionnext);  //On affiche le bouton pour passer à la fenêtre suivante
                SDL_Flip(ecran);

                continuer4 = 1;

                while(continuer4)
                {
                    SDL_WaitEvent(&event5);

                    switch(event5.type)
                    {
                        case SDL_QUIT : exit(0);
                                break;

                        case SDL_MOUSEBUTTONUP :
                                if(dansZone(event5, 932, 545, 1021, 573) == 1)  //Si le user appuie sur le bouton suivant
                                {
                                    i++;            //On augmente le compteur
                                    continuer4 = 0;
                                }
                    }//Fin switch
                }

            }//Fin while 2


            //}//fin while 1
        }
        SDL_FreeSurface(ajouterFilm);   //On libère toute la mémoire
        SDL_FreeSurface(typeFilm);
        TTF_CloseFont(police);
        TTF_Quit();
        SDL_Quit(); //On ferme la SDL

        return film;    //On retourne le film
}

/**La fonction ci-dessous sert à afficher les infos d'un film**/
void afficherFilm(Film film)
{
    SDL_Surface *ecran = NULL, *fond = NULL;    //On initialise toutes les surfaces sont nous avons besoins (image, textes...)
    SDL_Surface *titre = NULL, *duree = NULL, *date = NULL;     //Si nous l'avons mis sur plusisuers lignes, c'est pour que ce soit plus lisible et structuré
    SDL_Surface *reaNom = NULL, *reaPrenom = NULL, *reaVille = NULL, *reaJour = NULL, *reaMois = NULL, *reaAnnee = NULL;
    SDL_Surface *type = NULL;
    SDL_Surface *acteurNom = NULL, *acteurPrenom = NULL;

    SDL_Rect position, positionTitre, positionDuree, positionDate;      //Initialisation de toutes les positions
    SDL_Rect positionreaNom, positionreaPrenom, positionreaVille, positionreaJour, positionreaMois, positionreaAnnee;
    SDL_Rect positionType;
    SDL_Rect positionActeurNom, positionActeurPrenom;

    TTF_Init();     //initialisation de la police
    SDL_Color noir = {0, 0, 0};
    TTF_Font *police = NULL;
    police = TTF_OpenFont("Angelina.ttf", 60);
    int i = 0;

    ecran = SDL_SetVideoMode(1024, 576, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //Initialisation de la fenêtre graphique
    fond = SDL_LoadBMP("affichage.bmp");

//On définit toutes les position
    position.x = 0;
    position.y = 0;

    positionTitre.x = 380;
    positionTitre.y = 151;

    positionDuree.x = 500;
    positionDuree.y = 263;

    positionDate.x = 65;
    positionDate.y = 263;

    positionreaNom.x = 88;
    positionreaNom.y = 395;

    positionreaPrenom.x = 80;
    positionreaPrenom.y = 360;

    positionreaVille.x = 770;
    positionreaVille.y = 373;

    positionreaJour.x = 459;
    positionreaJour.y = 370;

    positionreaMois.x = 544;
    positionreaMois.y = 370;

    positionreaAnnee.x = 635;
    positionreaAnnee.y = 370;

    positionType.x = 769;
    positionType.y = 263;

//On rentre tous les textes saisis par le user dans les variables correspondantes
    titre = TTF_RenderText_Blended(police, film.titre, noir);
    duree = TTF_RenderText_Blended(police, film.duree, noir);
    date = TTF_RenderText_Blended(police, film.date, noir);
    reaNom = TTF_RenderText_Blended(police, film.realisateur.nom, noir);
    reaPrenom = TTF_RenderText_Blended(police, film.realisateur.prenom, noir);
    reaVille = TTF_RenderText_Blended(police, film.realisateur.ville, noir);
    reaJour = TTF_RenderText_Blended(police, film.realisateur.jour, noir);
    reaMois = TTF_RenderText_Blended(police, film.realisateur.mois, noir);
    reaAnnee = TTF_RenderText_Blended(police, film.realisateur.annee, noir);

    SDL_BlitSurface(fond, NULL, ecran, &position);  //On initialise le fond

    switch(film.type)   //On définit les différents types en fonction de la case cochéé par le user
    {
        case 1 : type = TTF_RenderText_Blended(police, "action", noir);
                 break;
        case 2 : type = TTF_RenderText_Blended(police, "horreur", noir);
                 break;
        case 3 : type = TTF_RenderText_Blended(police, "documentaire", noir);
                 break;
        case 4 : type = TTF_RenderText_Blended(police, "policier", noir);
                 break;
        case 5 : type = TTF_RenderText_Blended(police, "drama", noir);
                 break;
        case 6 : type = TTF_RenderText_Blended(police, "animation", noir);
                 break;
        case 7 : type = TTF_RenderText_Blended(police, "Science-fiction", noir);
                 break;
        default : break;
    }

    if(film.nbActeur > 0)   //Si le nombre d'acteurs n'est pas nul
    {
        for(i = 0; i < film.nbActeur; i++)  //On les affiche
        {
            switch(i)
            {
                case 0 : positionActeurPrenom.x = 11;
                         positionActeurPrenom.y = 477;

                         positionActeurNom.x = 11;
                         positionActeurNom.y = 529;

                         acteurPrenom = TTF_RenderText_Blended(police, film.acteurs[i].prenom, noir);   //On rentre les données dans les variables
                         acteurNom = TTF_RenderText_Blended(police, film.acteurs[i].nom, noir);
                         break;

                case 1 : positionActeurPrenom.x = 326;
                         positionActeurPrenom.y = 477;

                         positionActeurNom.x = 326;
                         positionActeurNom.y = 529;

                         acteurPrenom = TTF_RenderText_Blended(police, film.acteurs[i].prenom, noir);
                         acteurNom = TTF_RenderText_Blended(police, film.acteurs[i].nom, noir);
                         break;

                case 2 : positionActeurPrenom.x = 541;
                         positionActeurPrenom.y = 477;

                         positionActeurNom.x = 541;
                         positionActeurNom.y = 529;

                         acteurPrenom = TTF_RenderText_Blended(police, film.acteurs[i].prenom, noir);
                         acteurNom = TTF_RenderText_Blended(police, film.acteurs[i].nom, noir);
                         break;

                case 3 : positionActeurPrenom.x = 800;
                         positionActeurPrenom.y = 477;

                         positionActeurNom.x = 800;
                         positionActeurNom.y = 531;

                         acteurPrenom = TTF_RenderText_Blended(police, film.acteurs[i].prenom, noir);
                         acteurNom = TTF_RenderText_Blended(police, film.acteurs[i].nom, noir);
                         break;

                default : break;
            }
            SDL_BlitSurface(acteurPrenom, NULL, ecran, &positionActeurPrenom);  //on affiches les variables
            SDL_BlitSurface(acteurNom, NULL, ecran, &positionActeurNom);
        }

    }

    SDL_BlitSurface(titre, NULL, ecran, &positionTitre);    //On affiche toutes les infos saisies
    SDL_BlitSurface(duree, NULL, ecran, &positionDuree);
    SDL_BlitSurface(date, NULL, ecran, &positionDate);
    SDL_BlitSurface(reaPrenom, NULL, ecran, &positionreaPrenom);
    SDL_BlitSurface(reaNom, NULL, ecran, &positionreaNom);
    SDL_BlitSurface(reaVille, NULL, ecran, &positionreaVille);
    SDL_BlitSurface(reaJour, NULL, ecran, &positionreaJour);
    SDL_BlitSurface(reaMois, NULL, ecran, &positionreaMois);
    SDL_BlitSurface(reaAnnee, NULL, ecran, &positionreaAnnee);
    SDL_BlitSurface(type, NULL, ecran, &positionType);

    SDL_Flip(ecran);        //On rafraichit l'écran
}

int menuPrincipal()
{
    SDL_Surface *ecran = NULL, *fond = NULL;    //On initialise toutes les surfaces sont nous avons besoins (image, textes...)

    SDL_Rect position;  //Position des images

    SDL_Event event;        //Variable évènement
    int continuer = 1;

    ecran = SDL_SetVideoMode(1024, 576, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //Initialisation de la fenêtre graphique
    fond = SDL_LoadBMP("menuPrincipal.bmp");

    position.x = 0;
    position.y = 0;

    SDL_BlitSurface(fond, NULL, ecran, &position);  //On affiche les images
    SDL_Flip(ecran);

    while(continuer)
    {
        SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_QUIT : exit(0);
                            break;

            case SDL_MOUSEBUTTONUP :
                            if(dansZone(event, 309, 184, 654, 249) == 1)    // en fontion du clic de l'utilisateur, on renvoie un numéro
                            {
                                return 1;
                            }
                            else if(dansZone(event, 309, 290, 653, 353) == 1)
                            {
                                return 2;
                            }
                            else if(dansZone(event, 309, 396, 654, 461) == 1)
                            {
                                return 3;
                            }
                            else if(dansZone(event, 309, 501, 654, 568) == 1)
                            {
                                return 4;
                            }
                            break;
                default : break;

            }
    }
}

void afficherListe(int nbFilms, char listeFilms[10][20])
{
    SDL_Surface *ecran = NULL, *fond = NULL, *texte;    //On initialise toutes les surfaces sont nous avons besoins (image, textes...)

    SDL_Rect position, positionTexte;  //Position des images

    TTF_Init();     //initialisation de la police
    SDL_Color noir = {0, 0, 0};
    TTF_Font *police = NULL;
    police = TTF_OpenFont("Angelina.ttf", 60);

    SDL_Event event;        //Variable évènement
    int continuer = 1, i = 0;

    ecran = SDL_SetVideoMode(1024, 576, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //Initialisation de la fenêtre graphique
    fond = SDL_LoadBMP("liste.bmp");

    position.x = 0;
    position.y = 0;

    SDL_BlitSurface(fond, NULL, ecran, &position);  //On affiche les images
    SDL_Flip(ecran);

    for(i=0; i < nbFilms; i++)
    {
        if(i == 4)
        {
            positionTexte.x = 546;
            positionTexte.y = 166;

            texte = TTF_RenderText_Blended(police, listeFilms[i], noir);
            SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
            SDL_Flip(ecran);
        }
        else if(i > 4)
        {
            positionTexte.y += 70;

            texte = TTF_RenderText_Blended(police, listeFilms[i], noir);
            SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
            SDL_Flip(ecran);

        }
        else if(i == 0)
        {
            positionTexte.x = 22;
            positionTexte.y = 166;

            texte = TTF_RenderText_Blended(police, listeFilms[i], noir);
            SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
            SDL_Flip(ecran);
        }


        positionTexte.y += 70;

        texte = TTF_RenderText_Blended(police, listeFilms[i], noir);
        SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
        SDL_Flip(ecran);

    }
}
/*
void recherche()
{
    SDL_Surface *ecran = NULL, *fondChoix = NULL;    //On initialise toutes les surfaces sont nous avons besoins (image, textes...)

    SDL_Rect position;  //Position des images

    SDL_Event event;        //Variable évènement
    int continuer = 1, genre = 0;

    ecran = SDL_SetVideoMode(1024, 576, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //Initialisation de la fenêtre graphique
    fondChoix = SDL_LoadBMP("recherchePar.bmp");

    position.x = 0;
    position.y = 0;

    SDL_BlitSurface(fond, NULL, ecran, &position);  //On affiche les images
    SDL_Flip(ecran);

    while(continuer)
    {
        SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_QUIT : exit(0);
                            break;

            case SDL_MOUSEBUTTONUP :
                            if(dansZone(event, 309, 252, 654, 318) == 1)    // en fontion du clic de l'utilisateur, on renvoie un numéro
                            {
                                afficherListe();    //En paramètre : le nombre de réalisateur (différents) + le tableau de réalisateur
                            }
                            else if(dansZone(event, 309, 405, 653, 468) == 1)
                            {
                                genre = saisieType(event, ecran);

                                //Il faut que tu me sortes un tableau tous les films de ce genre et le nombre de films

                                afficherListe();    //Pareil, les paramètres

                            }

                default : break;

            }
    }
}

*/
