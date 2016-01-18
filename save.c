#include "definitions.h"

//Fonctions liees a la sauvegarde et a la restauration

void destruction(Etats E)
{
    if (E != NULL)
    destruction(E->suiv);
    free(E);
}


Etats ajoutDebut(Etats E, int cases[9][9], Joueur J, Mur M)
{	//Sauvegarde le tout dernier etat de jeu au debut de la liste des Etats
    Etat* nouv = malloc(sizeof(Etat)) ;

	int i, j;
	
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			nouv->cases[j][i] = cases[j][i];
		}
	}
    nouv->J = J;
    nouv->M = M;
    nouv->suiv = E;
    
    return nouv;
}

Etats suppDebut(Etats E, int cases[9][9], Joueur* J, Mur* M)
{	//Restaure le tout dernier etat de jeu aux variables de jeu et le supprime de la liste
	if (E == NULL || E->suiv == NULL)
		return E;

	Etat* aSupp = E;
	E = E->suiv;
	
	int i, j;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
			cases[j][i] = E->cases[j][i];
	}
    *J = E->J;
    *M = E->M;
    
    J->aQuiLeTour = (J->aQuiLeTour == 1 ? 2 : 1); //On inverse le tour de jeu pour le retour

    free(aSupp);
    return E;
}


void save(Etats E)
{
	printf("saving...\n");
	
	FILE* F;
	F = fopen("save","w");			//mode ecriture seule, pas besoin de tester si le fichier n'exsite pas car il sera cree sinon
	fwrite(E, sizeof(Etat), 1, F);
	fclose(F);
	
	printf("save complete\n");
}

Etats load(Etats E, Joueur* J, Mur* M)
{
	printf("loading...\n");
	
	FILE* F;
	F = fopen("save","r");			//mode leture seule, le fichier doit etre cree au prealable sinon erreur
	
	if (F == NULL){
		printf("no saved games\n");
		return E;
	}
	
	E = malloc(sizeof(Etat));
	
	fread(E, sizeof(Etat), 1, F);
	fclose(F);
	E->suiv = NULL;
	
    *J = E->J;
    *M = E->M;
	
	printf("load complete\n");
	return E;
}
