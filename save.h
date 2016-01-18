#ifndef DEF_DEF
#define DEF_DEF

#include "definitions.h"

#endif

void destruction(Etats E);

Etats ajoutDebut(Etats E, int cases[9][9], Joueur J, Mur M);

Etats suppDebut(Etats E, int cases[9][9], Joueur* J, Mur* M);

void save(Etats E);

Etats load(Etats E, Joueur* J, Mur* M);
