#ifndef DEF_GRAPH
#define DEF_GRAPH

#include "graphics.h"

#endif

//definition de la largeur et la hauteur de la fenetre
#define X 700
//#define X 1280
#define Y 500
//#define Y 750

typedef struct plateau
{//Contient les element qui composent le plateau. Chaque element a deux champs : une hauteur et une largeur
	POINT hautDroite;
	POINT basGauche;
	POINT tailleCase;
	POINT epaisseurMur;
} Plateau;

typedef struct joueur
{//Contient les indices des joueurs et une information sur le tour
	POINT indiceJoueur1;
	POINT indiceJoueur2;
	int aQuiLeTour;
} Joueur;

typedef struct mur
{//Contient tous les tableaux qui representent les murs verticaux et les murs horizontaux et leurs croisements respectifs
	int existeMurV[9][8];
	int croisementMurV[9][8];
	int existeMurH[8][9];
	int croisementMurH[8][9];
	int nbMursJoueur1;
	int nbMursJoueur2;
} Mur;

typedef struct etat		
{//Represente un etat de jeu
	int cases[9][9];
	Joueur J;
	Mur M;
	struct etat* suiv;
} Etat;

typedef Etat* Etats;	//Represente tous les etats du jeu (une liste d'etats de jeu)

