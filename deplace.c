#include "definitions.h"

//Conditions relatives au deplacements du joueurs

void casesAccessibles(int cases[9][9], Joueur J, Mur M, Plateau P)
{	//modifie le tableau de cases selon la position des joueurs et des murs pour savoir quelles cases sont accessibles
	
	POINT indiceJoueur, indiceAutreJoueur;
	if (J.aQuiLeTour == 1)
	{
		indiceJoueur.x = J.indiceJoueur1.x;			indiceJoueur.y = J.indiceJoueur1.y;
		indiceAutreJoueur.x = J.indiceJoueur2.x;	indiceAutreJoueur.y = J.indiceJoueur2.y;
	}
	else
	{
		indiceJoueur.x = J.indiceJoueur2.x;			indiceJoueur.y = J.indiceJoueur2.y;
		indiceAutreJoueur.x = J.indiceJoueur1.x;	indiceAutreJoueur.y = J.indiceJoueur1.y;
	}
	
	//la case ou se trouve l'autre joueur n'est pas accessible pour le joueur actuel, on y met 2
	cases[indiceAutreJoueur.y][indiceAutreJoueur.x] = 2;
	
	//Test si la case a gauche est accessbile
	if (indiceJoueur.x != 0)
	{
		//Si ya pas de mur avant la case a gauche
		if ( !M.existeMurV[indiceJoueur.y][indiceJoueur.x-1] )
		{	
			//Si ya pas de joueur dans la case a gauche
			if ( cases[indiceJoueur.y][indiceJoueur.x-1] != 2 )
				cases[indiceJoueur.y][indiceJoueur.x-1] = 1;
			
			//Sinon si ya pas de mur qui bloque la case a gauche d'apres
			else if ( indiceJoueur.x != 1 && !M.existeMurV[indiceJoueur.y][indiceJoueur.x-2] )
				cases[indiceJoueur.y][indiceJoueur.x-2] = 1;
				//sinon si un mur empeche d'acceder a cette case
				else 
				{	
					if ( indiceJoueur.y != 8 && !M.existeMurH[indiceJoueur.y][indiceJoueur.x-1] )
						cases[indiceJoueur.y+1][indiceJoueur.x-1] = 1;
					if ( indiceJoueur.y != 0 && !M.existeMurH[indiceJoueur.y-1][indiceJoueur.x-1] )
						cases[indiceJoueur.y-1][indiceJoueur.x-1] = 1;
				}
		}
	}
	
	//Test si la case a droite est accessbile
	if (indiceJoueur.x != 8)
	{
		if ( !M.existeMurV[indiceJoueur.y][indiceJoueur.x] )
		{	
			if ( cases[indiceJoueur.y][indiceJoueur.x+1] != 2 )
				cases[indiceJoueur.y][indiceJoueur.x+1] = 1;

			else if ( indiceJoueur.x != 7 && !M.existeMurV[indiceJoueur.y][indiceJoueur.x+1] )
				cases[indiceJoueur.y][indiceJoueur.x+2] = 1;
				
				else 
				{	
					if ( indiceJoueur.y != 8 && !M.existeMurH[indiceJoueur.y][indiceJoueur.x+1] )
						cases[indiceJoueur.y+1][indiceJoueur.x+1] = 1;
					if ( indiceJoueur.y != 0 && !M.existeMurH[indiceJoueur.y-1][indiceJoueur.x+1] )
						cases[indiceJoueur.y-1][indiceJoueur.x+1] = 1;
				}
		}
	}
	
	//Test si la case en haut est accessbile
	if (indiceJoueur.y != 8)
	{
		if ( !M.existeMurH[indiceJoueur.y][indiceJoueur.x] )
		{	
			if ( cases[indiceJoueur.y+1][indiceJoueur.x] != 2 )
				cases[indiceJoueur.y+1][indiceJoueur.x] = 1;

			else if ( indiceJoueur.y != 7 && !M.existeMurH[indiceJoueur.y+1][indiceJoueur.x] )
				cases[indiceJoueur.y+2][indiceJoueur.x] = 1;
				
			else 
				{	
					if ( indiceJoueur.x != 0 && !M.existeMurV[indiceJoueur.y+1][indiceJoueur.x-1] )
						cases[indiceJoueur.y+1][indiceJoueur.x-1] = 1;
					if ( indiceJoueur.x != 8 && !M.existeMurV[indiceJoueur.y+1][indiceJoueur.x] )
						cases[indiceJoueur.y+1][indiceJoueur.x+1] = 1;
				}
		}
	}
	
	//Test si la case en bas est accessbile
	if (indiceJoueur.y != 0)
	{
		if ( !M.existeMurH[indiceJoueur.y-1][indiceJoueur.x] )
		{	
			if ( cases[indiceJoueur.y-1][indiceJoueur.x] != 2 )
				cases[indiceJoueur.y-1][indiceJoueur.x] = 1;

			else if ( indiceJoueur.y != 1 && !M.existeMurH[indiceJoueur.y-2][indiceJoueur.x] )
				cases[indiceJoueur.y-2][indiceJoueur.x] = 1;
				
			else {	
					if ( indiceJoueur.x != 0 && !M.existeMurV[indiceJoueur.y-1][indiceJoueur.x-1] )
						cases[indiceJoueur.y-1][indiceJoueur.x-1] = 1;
					if ( indiceJoueur.x != 8 && !M.existeMurV[indiceJoueur.y-1][indiceJoueur.x] )
						cases[indiceJoueur.y-1][indiceJoueur.x+1] = 1;
				}
		}
	}
	
}


int clicDansCaseAccessible(POINT Pt, int cases[9][9], Joueur* J, Plateau P)
{	//verifie si on a clique dans une case accessible du plateau et modifie les indices du joueurs actuel
	int i,j;
	
	for (i = 0; i < 9; i++)
	{
		//si le clic est dans une colonne de cases, on cherche sa ligne et on retourne vrai si possible et aussi les indices
		if ( Pt.x > (P.basGauche.x + i*P.tailleCase.x + i*P.epaisseurMur.x) 
		&& Pt.x < (P.basGauche.x + (i+1)*P.tailleCase.x + i*P.epaisseurMur.x) )
		
			//on cherche alors si c'est dans une ligne correspondant a une case
			for (j = 0; j < 9; j++)
			{
				if ( Pt.y > (P.basGauche.y + j*(P.tailleCase.y + P.epaisseurMur.y) ) 
				&& Pt.y < (P.basGauche.y + (j+1)*P.tailleCase.y + j*P.epaisseurMur.y) )
				{
					//une fois la bonne ligne (donc la case) trouvee, on verifie si cette case est accessible
					if (cases[j][i] == 1)
					{	
						//On retient les indices de la nouvelle case et retourne vrai
						if (J->aQuiLeTour == 1)
						{
							J->indiceJoueur1.x = i;
							J->indiceJoueur1.y = j;
						}
						else
						{
							J->indiceJoueur2.x = i;
							J->indiceJoueur2.y = j;
						}
						return 1;
					}
				}
			}
	}
	return 0;
}

