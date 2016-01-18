#ifndef DEF_DEF
#define DEF_DEF

#include "definitions.h"

#endif

//Affichage du menu
void afficheBouton1(COULEUR C, Plateau P);
void afficheBouton2(COULEUR C, Plateau P);
void afficheBouton3(COULEUR C, Plateau P);
void afficheMenu(Plateau P);

//Affichage des bouttons du jeu
POINT coordJoueur(POINT indiceJoueur, Plateau P);
void afficheBoutonBACK(COULEUR C, Plateau P);
void afficheBoutonSAVE(COULEUR C, Plateau P);
void afficheBoutonQUIT(COULEUR C, Plateau P);
void afficheBoutonQUITSolo(COULEUR C, Plateau P);
void annonceSAVE(Plateau P);
void annonceLOAD(Plateau P);

//Affichage d'un etat de jeu
void afficheJeuMulti(int gagne, int cases[9][9], Joueur J, Mur M, Plateau P);
void afficheJeuSolo(int gagne, int cases[9][9], Joueur J, Mur M, Plateau P);

//Affichage a la fin d'une parite
void afficheVictoire(int aQuiLeTour, Plateau P);


