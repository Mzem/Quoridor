#ifndef DEF_DEF
#define DEF_DEF

#include "definitions.h"

#endif

//Test clic boutons menu
int clicBouton1(POINT clic, Plateau P);
int clicBouton2(POINT clic, Plateau P);
int clicBouton3(POINT clic, Plateau P);

//Initialisation des elements du jeu
void initJeu(Joueur* J, Mur* M, Plateau* P);

//Fonctions de jeu
void jouerMulti(Etats E, Joueur J, Mur M, Plateau P);
void jouerSolo(Joueur J, Mur M, Plateau P);
