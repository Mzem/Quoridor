#include "deplace.h"

//Conditions relatives aux placement des murs

int tableauxDifferents(int t1[9][9], int t2[9][9]){
	int i, j;
	
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if( t1[j][i] != t2[j][i] )
				return 1;
		}
	}
	return 0;
}

void recopieTableau(int t1[9][9], int t2[9][9]){
	int i, j;
	
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			t2[j][i] = t1[j][i];
		}
	}
}


int murBloquantJoueurActuel(Joueur J, Mur M, Plateau P)
{	//Retourne 1 si le mur aux indices stockees dans M bloque la victoire au joueur actuel
	
	int i,j,k, modif = 1;
	int cases[9][9] = {{0}}, aux[9][9] = {{0}};
	
	//on initialise la case ou se trouve le joueur a 1
	if (J.aQuiLeTour == 1)
		cases[J.indiceJoueur1.y][J.indiceJoueur1.x] = 1; 
	else
		cases[J.indiceJoueur2.y][J.indiceJoueur2.x] = 1;
	
	while(modif)
	{	
		modif = 0;
		recopieTableau(cases,aux);		//on recopie le tableau cases dans aux;
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				if (cases[j][i] == 1) 	//des qu'on trouve une case a 1, on marque toutes les cases accessibles a partir de celle-ci
				{	
					if (J.aQuiLeTour == 1)
					{
						J.indiceJoueur1.x = i; 
						J.indiceJoueur1.y = j;
					}
					else
					{
						J.indiceJoueur2.x = i;
						J.indiceJoueur2.y = j;
					}
					casesAccessibles(cases, J, M, P);	//marquage dans le tableau cases
				}
				for (k = 0; k < 9; k++) //On test si on peut gagner, on sort des que c'est possible
				{	
					if (J.aQuiLeTour == 1 && cases[8][k] == 1)
						return 0;
					if (J.aQuiLeTour == 2 && cases[0][k] == 1)
						return 0;
				}		
			}
		}
		if (tableauxDifferents(cases,aux))	
			modif = 1;	//Si on a fait une modification dans cases, on refait une recherche
	}
	return 1;
}

int murBloquantAutreJoueur(Joueur J, Mur M, Plateau P)
{	//Retourne 1 si le mur aux indices stockees dans M bloque la victoire a l'autre joueur
	
	int i,j,k, modif = 1;
	int cases[9][9] = {{0}}, aux[9][9] = {{0}};
	
	//on initialise la case ou se trouve l'autre joueur a 1
	if (J.aQuiLeTour == 1)
	{
		cases[J.indiceJoueur2.y][J.indiceJoueur2.x] = 1; 
		J.aQuiLeTour = 2; //a qui le tour d'etre verifie en fait
	}
	else
	{
		cases[J.indiceJoueur1.y][J.indiceJoueur1.x] = 1;
		J.aQuiLeTour = 1;
	}
	
	while(modif)
	{	
		modif = 0;
		recopieTableau(cases,aux);		//on recopie le tableau cases dans aux;
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				if (cases[j][i] == 1) 	//des qu'on trouve une case a 1, on marque toutes les cases accessibles a partir de celle-ci
				{	
					if (J.aQuiLeTour == 1)
					{
						J.indiceJoueur1.x = i; 
						J.indiceJoueur1.y = j;
					}
					else
					{
						J.indiceJoueur2.x = i;
						J.indiceJoueur2.y = j;
					}
					casesAccessibles(cases, J, M, P);	//marquage dans le tableau cases
				}
				for (k = 0; k < 9; k++) //On test si on peut gagner, on sort des que c'est possible
				{	
					if (J.aQuiLeTour == 1 && cases[8][k] == 1)
						return 0;
					if (J.aQuiLeTour == 2 && cases[0][k] == 1)
						return 0;
				}		
			}
		}
		if (tableauxDifferents(cases,aux))	
			modif = 1;	//Si on a fait une modification dans cases, on refait une recherche
	}
	return 1;
}

int clicZoneMurVideV(POINT Pt, Joueur J, Mur* M, Plateau P)
{	//verifie si on peut placer un mur vertical dans la zone cliquee et renvoie les indices du mur si possible
	int i,j;
	
	//on verifie si le clic est dans une zone de murs verticaux
	for (i = 0; i < 8; i++)
	{
		//si le clic est dans un champ vertical de murs, on cherche sa hauteur et on retourne vrai et aussi les indices
		if ( Pt.x > (P.basGauche.x + (i+1)*P.tailleCase.x + i*P.epaisseurMur.x) 
		&& Pt.x < (P.basGauche.x + (i+1)*P.tailleCase.x + (i+1)*P.epaisseurMur.x) )
		
			//on cherche la hauteur une fois pour toutes
			for (j = 0; j < 8; j++)
			{
				if ( Pt.y > (P.basGauche.y + j*(P.tailleCase.y + P.epaisseurMur.y) ) 
				&& Pt.y < (P.basGauche.y + (j+1)*P.tailleCase.y + j*P.epaisseurMur.y) )
				{
					//une fois la bonne hauteur trouvee, il reste a verifie si cette zone est vide (pas de mur avant)
					if (M->existeMurV[j][i] == 0 && M->existeMurV[j+1][i] == 0 && M->croisementMurV[j][i] == 0)
					{	//si le placement du mur est possible, on marque la zone pleine et on retient les indices
						M->existeMurV[j][i] = 1;
						M->existeMurV[j+1][i] = 2;
						M->croisementMurH[j][i] = 1;
						//Si par contre ce mur est bloquant pour l'un des joueurs, on annule tout et on sort de la fonction
						if (murBloquantJoueurActuel(J,*M,P) || murBloquantAutreJoueur(J,*M,P))
						{
							M->existeMurV[j][i] = 0;
							M->existeMurV[j+1][i] = 0;
							M->croisementMurH[j][i] = 0;
							return 0;
						}
						return 1;
					}
				}
			}
	}
	return 0;
}
	
int clicZoneMurVideH(POINT Pt, Joueur J, Mur* M, Plateau P)
{
	int i,j;

	for (j = 0; j < 8; j++)
	{
		if ( Pt.y > (P.basGauche.y + (j+1)*P.tailleCase.y + j*P.epaisseurMur.y) 
		&& Pt.y < (P.basGauche.y + (j+1)*P.tailleCase.y + (j+1)*P.epaisseurMur.y) )
		
			for (i = 0; i < 8; i++)
			{
				if ( Pt.x > (P.basGauche.x + i*(P.epaisseurMur.x + P.tailleCase.x) ) 
				&& Pt.x < (P.basGauche.x + (i+1)*P.tailleCase.x + i*P.epaisseurMur.x) )
				{
					if (M->existeMurH[j][i] == 0 && M->existeMurH[j][i+1] == 0 && M->croisementMurH[j][i] == 0)
					{
						M->existeMurH[j][i] = 1;
						M->existeMurH[j][i+1] = 2;
						M->croisementMurV[j][i] = 1;
						if (murBloquantJoueurActuel(J,*M,P) || murBloquantAutreJoueur(J,*M,P))
						{
							M->existeMurH[j][i] = 0;
							M->existeMurH[j][i+1] = 0;
							M->croisementMurV[j][i] = 0;
							return 0;
						}
						return 1;
					}
				}
			}
	}
	return 0;
}
