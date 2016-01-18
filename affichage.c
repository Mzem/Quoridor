#include "definitions.h"

//Affichage des elements du menu
void afficheBouton1(COULEUR C, Plateau P){
	POINT HG, BD;
	int taillePolice = (X*Y)/12000;
	
	HG.x = X/2 - 11*P.tailleCase.x/2;	//presque *6
	BD.x = X/2 + 11*P.tailleCase.x/2;
	BD.y = P.tailleCase.y + 3*P.tailleCase.y/2 + P.tailleCase.y/3 + + 3*P.tailleCase.y/2 + P.tailleCase.y/3;
	HG.y = BD.y + 3*P.tailleCase.y/2; 
	
	draw_fill_rectangle(HG,BD,C);
	draw_rectangle(HG,BD,couleur_RGB(10,10,10));
	
	HG.x = HG.x + (BD.x - HG.x - 12*(taillePolice/2 + taillePolice/30) )/2; //12 est le nombre de lettre dans "Singleplayer"
	HG.y = HG.y - (HG.y - BD.y - taillePolice)/2 + taillePolice*2/10;
	
	aff_pol("Singleplayer", taillePolice, HG, couleur_RGB(50,50,50));
}

void afficheBouton2(COULEUR C, Plateau P){
	POINT HG, BD;
	int taillePolice = (X*Y)/12000;
	
	HG.x = X/2 - 11*P.tailleCase.x/2;	//presque *6
	BD.x = X/2 + 11*P.tailleCase.x/2;
	BD.y = P.tailleCase.y + 3*P.tailleCase.y/2 + P.tailleCase.y/3;
	HG.y = BD.y + 3*P.tailleCase.y/2; 
	
	draw_fill_rectangle(HG,BD,C);
	draw_rectangle(HG,BD,couleur_RGB(10,10,10));
	
	HG.x = HG.x + (BD.x - HG.x - 11*(taillePolice/2) )/2;	//11 est le nombre de lettre dans "Multiplayer"
	HG.y = HG.y - (HG.y - BD.y - taillePolice)/2 + taillePolice*2/10;
	
	aff_pol("Multiplayer", taillePolice, HG, couleur_RGB(50,50,50));
}

void afficheBouton3(COULEUR C, Plateau P){
	POINT HG, BD;
	int taillePolice = (X*Y)/12000;
	
	HG.x = X/2 - 11*P.tailleCase.x/2;	//presque *6
	BD.x = X/2 + 11*P.tailleCase.x/2;
	BD.y = P.tailleCase.y;
	HG.y = BD.y + 3*P.tailleCase.y/2; 
	
	draw_fill_rectangle(HG,BD,C);
	draw_rectangle(HG,BD,couleur_RGB(10,10,10));
	
	HG.x = HG.x + (BD.x - HG.x - 9*(taillePolice/2 + taillePolice/7) )/2; //9 est le nombre de lettre dans "Load Game"
	HG.y = HG.y - (HG.y - BD.y - taillePolice)/2 + taillePolice*2/10;
	
	aff_pol("Load Game", taillePolice, HG, couleur_RGB(50,50,50));
}

void degrade(){
	int i;
	POINT P1, P2;
	P1.x = 0;
	P2.x = X;
	
	for (i = 0; i < Y; i++)
	{	
		P1.y = i;
		P2.y = P1.y + 1;
		
		if (117+i/5 < 255)
			draw_fill_rectangle(P1,P2,couleur_RGB(190+i/15,170+i/10,117+i/5));
		else
			draw_fill_rectangle(P1,P2,couleur_RGB(237,240,255));
	}
}

void afficheMenu(Plateau P){
	affiche_auto_off();
	degrade();	//La fonction degrade fait buger l'affichage du menu PARFOIS !!!
	//fill_screen(couleur_RGB(237,237,237));
	
	POINT HG;
	int i, taillePolice = (X*Y)/7000;
	
	for (i = 0; i < 5; i++)
	{//Ajustement du point HG pour que l'affichage soit en haut et au milieu de l'ecran, valable pour n'importe quelle taille de fenetre
		HG.x = (X - 8*(taillePolice/2 + taillePolice/5) )/2;
		HG.y = 9*Y/10;
	
		aff_pol("QUORIDOR",taillePolice,HG,couleur_RGB(200 - 20*i, 170 - 20*i, 120 - 20*i));
		
		taillePolice += 10;
	}
	
	afficheBouton1(couleur_RGB(207,207,207),P);
	afficheBouton2(couleur_RGB(207,207,207),P);
	afficheBouton3(couleur_RGB(207,207,207),P);
	
	affiche_all();
}


//Affichage des elements d'un jeu
POINT coordJoueur(POINT indiceJoueur, Plateau P){	
	//convertit les indices du joueur en coordonnees pour pouvoir l'afficher
	POINT Pt;
	Pt.x = P.basGauche.x + P.tailleCase.x/2 + indiceJoueur.x*(P.tailleCase.x + P.epaisseurMur.x);
	Pt.y = P.basGauche.y + P.tailleCase.y/2 + indiceJoueur.y*(P.tailleCase.y + P.epaisseurMur.y);
	return Pt;
}

void affichePlateau(Plateau P){	
	int i,j;
	POINT P1,P2;
	COULEUR cArriere = couleur_RGB(237,237,237);
	COULEUR cCase = couleur_RGB(190,170,117);
	
	fill_screen(cArriere);			

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			P1.x = P.basGauche.x + i*(P.epaisseurMur.x + P.tailleCase.x);
			P1.y = P.basGauche.y + j*(P.epaisseurMur.y + P.tailleCase.y);
			P2.x = P.basGauche.x + P.tailleCase.x + i*(P.epaisseurMur.x + P.tailleCase.x);
			P2.y = P.basGauche.y + P.tailleCase.y + j*(P.epaisseurMur.y + P.tailleCase.y);
			draw_fill_rectangle(P1,P2,cCase);
		}	
	}
}

void afficheJoueur(int aQuiLeTour, POINT indiceJoueur, Plateau P){
	int i;
	COULEUR c = ( aQuiLeTour == 1 ? couleur_RGB(23,123,27) : couleur_RGB(187,27,17) );
	POINT coord = coordJoueur(indiceJoueur,P);
	
	draw_circle(coord, (P.tailleCase.x+P.tailleCase.y)/6,noir);
	for (i = 0; i < 5; i++)
	{
		draw_fill_circle(coord, (P.tailleCase.x+P.tailleCase.y)/6,c);
		coord.y++;
	}
	draw_circle(coord, (P.tailleCase.x+P.tailleCase.y)/6,noir);
}

void allumeCasesAccessibles(int aQuiLeTour, int cases[9][9], Plateau P){
	int i,j;
	POINT Pt;
	COULEUR c;
	
	if (aQuiLeTour == 1)	c = couleur_RGB(170,230,117);
	else 					c = couleur_RGB(255,170,117);
	
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (cases[j][i] == 1)
			{		
				Pt.x = P.basGauche.x + P.tailleCase.x/2 + i*(P.tailleCase.x + P.epaisseurMur.x);
				Pt.y = P.basGauche.y + P.tailleCase.y/2 + j*(P.tailleCase.y + P.epaisseurMur.y);
				draw_fill_circle(Pt, P.tailleCase.x/4,c);
			}
		}
	}
}

void afficheMurV(POINT indiceMur, Plateau P){
	POINT P1,P2;
	int i = indiceMur.x;
	int j = indiceMur.y;
	COULEUR c = couleur_RGB(77,53,17);
	
	P1.x = P.basGauche.x + (i+1)*P.tailleCase.x + i*P.epaisseurMur.x;
	P1.y = P.basGauche.y + j*(P.tailleCase.y + P.epaisseurMur.y);
	P2.x = P1.x + P.epaisseurMur.x;
	P2.y = P1.y + 2*P.tailleCase.y + P.epaisseurMur.y;
	
	draw_fill_rectangle(P1,P2,c);
}

void afficheMurH(POINT indiceMur, Plateau P){
	POINT P1,P2;
	int i = indiceMur.x;
	int j = indiceMur.y;
	COULEUR c = couleur_RGB(77,53,17);
	
	P1.x = P.basGauche.x + i*(P.tailleCase.x + P.epaisseurMur.x);
	P1.y = P.basGauche.y + (j+1)*P.tailleCase.y + j*P.epaisseurMur.y;
	P2.x = P1.x + 2*P.tailleCase.x + P.epaisseurMur.x;
	P2.y = P1.y + P.epaisseurMur.y;
	
	draw_fill_rectangle(P1,P2,c);
}

void afficheNbMurs(int aQuiLeTour, int nbMurs, Plateau P){
	POINT Pt;
	COULEUR c;
	int taillePolice = (X*Y)/10007;
	
	Pt.x = P.hautDroite.x + (X - P.hautDroite.x)/2 - taillePolice/2;
	
	if(aQuiLeTour == 1){
		Pt.y = Y - P.hautDroite.y + taillePolice + taillePolice/2;
		c = couleur_RGB(23,123,27);
	}
	else{
		Pt.y = P.hautDroite.y; 
		c = couleur_RGB(187,27,17);
	}
	aff_int(nbMurs,taillePolice,Pt,c);
}

void afficheTousLesMurs(Mur M, Plateau P){
	int i,j;
	POINT Pt;
	
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			Pt.x = i; Pt.y = j;
			if (M.existeMurV[j][i] == 1) //1 pas 2, car 2 veut dire que cette case est la seconde partie d'un mur
				afficheMurV(Pt, P);
			if (M.existeMurH[j][i] == 1) //1 pas 2, car 2 veut dire que cette case est la seconde partie d'un mur
				afficheMurH(Pt, P);
		}
	}
}


//Affichage des boutons du jeu
void afficheBoutonBACK(COULEUR C, Plateau P){
	POINT HG, BD;
	int taillePolice = (X*Y)/13000;
	
	HG.x = P.hautDroite.x + (X - P.hautDroite.x)/2 - 3*P.tailleCase.x/2 ;
	BD.x = P.hautDroite.x + (X - P.hautDroite.x)/2 + 3*P.tailleCase.x/2 ;
	HG.y = Y/2 + 2*P.tailleCase.y/3;
	BD.y = Y/2 - 2*P.tailleCase.y/3;
	
	draw_fill_rectangle(HG,BD,C);
	draw_rectangle(HG,BD,couleur_RGB(10,10,10));
	
	//On adapte HG pour l'affichage du texte puisque la fonction aff_pol ne propose pas beaucoup de solutions...
	//On trouve des valeurs bizarres ici, mais je n'ai pas pu faire mieux a cause de la fonction aff_pol predefinie
	//La largeur d'un caractere fait a peu pres taillePolice/2 pixels, 11/4 correspond aux espaces entre les caracteres (4 caracteres dans BACK)
	//La hauteur d'un caractere fait taillePolice l'affichage commence 20% de taillePolice en dessous du point hautGauche
	HG.x = HG.x + (BD.x - HG.x - 11*taillePolice/4)/2;
	HG.y = HG.y - (HG.y - BD.y - taillePolice)/2 + taillePolice*2/10;
	
	aff_pol("BACK", taillePolice, HG, couleur_RGB(50,50,50));
}

void afficheBoutonSAVE(COULEUR C, Plateau P){
	POINT HG, BD;
	int taillePolice = (X*Y)/13000;
	
	HG.x = P.hautDroite.x + (X - P.hautDroite.x)/2 - 3*P.tailleCase.x/2 ;
	BD.x = P.hautDroite.x + (X - P.hautDroite.x)/2 + 3*P.tailleCase.x/2 ;
	HG.y = Y/2 + 2*P.tailleCase.y/3 + P.tailleCase.y/2 + 4*P.tailleCase.y/3;
	BD.y = Y/2 - 2*P.tailleCase.y/3 + P.tailleCase.y/2 + 4*P.tailleCase.y/3;
	
	draw_fill_rectangle(HG,BD,C);
	draw_rectangle(HG,BD,couleur_RGB(10,10,10));
	
	HG.x = HG.x + (BD.x - HG.x - 11*taillePolice/4)/2;
	HG.y = HG.y - (HG.y - BD.y - taillePolice)/2 + taillePolice*2/10;
	
	aff_pol("SAVE", taillePolice, HG, couleur_RGB(50,50,50));
}

void afficheBoutonQUIT(COULEUR C, Plateau P){
	POINT HG, BD;
	int taillePolice = (X*Y)/13000;
	
	HG.x = P.hautDroite.x + (X - P.hautDroite.x)/2 - 3*P.tailleCase.x/2 ;
	BD.x = P.hautDroite.x + (X - P.hautDroite.x)/2 + 3*P.tailleCase.x/2 ;
	HG.y = Y/2 + 2*P.tailleCase.y/3 - P.tailleCase.y/2 - 4*P.tailleCase.y/3;
	BD.y = Y/2 - 2*P.tailleCase.y/3 - P.tailleCase.y/2 - 4*P.tailleCase.y/3;
	
	draw_fill_rectangle(HG,BD,C);
	draw_rectangle(HG,BD,couleur_RGB(10,10,10));
	
	HG.x = HG.x + (BD.x - HG.x - 11*taillePolice/4)/2;
	HG.y = HG.y - (HG.y - BD.y - taillePolice)/2 + taillePolice*2/10;
	
	aff_pol("QUIT", taillePolice, HG, couleur_RGB(50,50,50));
}

void afficheBoutonQUITSolo(COULEUR C, Plateau P){
	POINT HG, BD;
	int taillePolice = (X*Y)/13000;
	
	HG.x = P.hautDroite.x + (X - P.hautDroite.x)/2 - 3*P.tailleCase.x/2 ;
	BD.x = P.hautDroite.x + (X - P.hautDroite.x)/2 + 3*P.tailleCase.x/2 ;
	HG.y = Y/2 + 2*P.tailleCase.y/3;
	BD.y = Y/2 - 2*P.tailleCase.y/3;
	
	draw_fill_rectangle(HG,BD,C);
	draw_rectangle(HG,BD,couleur_RGB(10,10,10));
	
	//On adapte HG pour l'affichage du texte puisque la fonction aff_pol ne propose pas beaucoup de solutions...
	//On trouve des valeurs bizarres ici, mais je n'ai pas pu faire mieux a cause de la fonction aff_pol predefinie
	//La largeur d'un caractere fait a peu pres taillePolice/2 pixels, 11/4 correspond aux espaces entre les caracteres (4 caracteres dans BACK)
	//La hauteur d'un caractere fait taillePolice l'affichage commence 20% de taillePolice en dessous du point hautGauche
	HG.x = HG.x + (BD.x - HG.x - 11*taillePolice/4)/2;
	HG.y = HG.y - (HG.y - BD.y - taillePolice)/2 + taillePolice*2/10;
	
	aff_pol("QUIT", taillePolice, HG, couleur_RGB(50,50,50));
}

void annonceSAVE(Plateau P){
	POINT HG, BD;
	int taillePolice = (X*Y)/10000;
	
	HG.x = P.basGauche.x + (P.hautDroite.x - P.basGauche.x)/2 - 4*P.tailleCase.x ;
	BD.x = P.basGauche.x + (P.hautDroite.x - P.basGauche.x)/2 + 4*P.tailleCase.x ;
	HG.y = Y/2 + P.tailleCase.y;
	BD.y = Y/2 - P.tailleCase.y;
	
	draw_fill_rectangle(HG,BD,couleur_RGB(170,230,117));
	draw_rectangle(HG,BD,couleur_RGB(10,10,10));
	
	HG.x = HG.x + (BD.x - HG.x - 13*(taillePolice/2 + taillePolice/30) )/2; //14 est le nombre de lettre dans "Save Complete!"
	HG.y = HG.y - (HG.y - BD.y - taillePolice)/2 + taillePolice*2/10;
	
	aff_pol("Game Saved!", taillePolice, HG, couleur_RGB(50,50,50));
}

void annonceLOAD(Plateau P){
	POINT HG, BD;
	int taillePolice = (X*Y)/10000;
	
	HG.x = X/2 - 4*P.tailleCase.x ;
	BD.x = X/2 + 4*P.tailleCase.x ;
	HG.y = Y/2 + P.tailleCase.y;
	BD.y = Y/2 - P.tailleCase.y;
	
	draw_fill_rectangle(HG,BD,couleur_RGB(255,170,117));
	draw_rectangle(HG,BD,couleur_RGB(10,10,10));
	
	HG.x = HG.x + (BD.x - HG.x - 17*(taillePolice/2 + taillePolice/30) )/2;
	HG.y = HG.y - (HG.y - BD.y - taillePolice)/2 + taillePolice*2/10;
	
	aff_pol("No Saved Games!", taillePolice, HG, couleur_RGB(50,50,50));
}

//Affichage d'un etat de jeu
void afficheJeuMulti(int gagne, int cases[9][9], Joueur J, Mur M, Plateau P)
{
	affiche_auto_off();
	
	affichePlateau(P);
	
	afficheJoueur(1, J.indiceJoueur1, P);
	afficheJoueur(2, J.indiceJoueur2, P);
	
	afficheTousLesMurs(M,P);
	
	afficheBoutonBACK(couleur_RGB(207,207,207),P);
	afficheBoutonSAVE(couleur_RGB(207,207,207),P);
	afficheBoutonQUIT(couleur_RGB(207,207,207),P);
	
	afficheNbMurs(1, M.nbMursJoueur1, P);
	afficheNbMurs(2, M.nbMursJoueur2, P);
	
	if (!gagne)
		allumeCasesAccessibles(J.aQuiLeTour, cases, P);
	
	affiche_all();
}

void afficheJeuSolo(int gagne, int cases[9][9], Joueur J, Mur M, Plateau P)
{
	affiche_auto_off();
	
	affichePlateau(P);
	
	afficheJoueur(1, J.indiceJoueur1, P);
	afficheJoueur(2, J.indiceJoueur2, P);
	
	afficheTousLesMurs(M,P);
	
	afficheBoutonQUITSolo(couleur_RGB(207,207,207),P);
	
	afficheNbMurs(1, M.nbMursJoueur1, P);
	afficheNbMurs(2, M.nbMursJoueur2, P);
	
	if (!gagne)
		allumeCasesAccessibles(J.aQuiLeTour, cases, P);
	
	affiche_all();
}


//Affichage a la fin d'une partie
void afficheVictoire(int aQuiLeTour, Plateau P)
{
	POINT HG, BD;
	int taillePolice = (X*Y)/9000;
	COULEUR C = (aQuiLeTour == 2 ? couleur_RGB(170,230,117) : couleur_RGB(255,170,117) );
	
	HG.x = P.basGauche.x + (P.hautDroite.x - P.basGauche.x)/2 - 5*P.tailleCase.x ;
	BD.x = P.basGauche.x + (P.hautDroite.x - P.basGauche.x)/2 + 5*P.tailleCase.x ;
	HG.y = Y/2 + P.tailleCase.y;
	BD.y = Y/2 - P.tailleCase.y;
	
	draw_fill_rectangle(HG,BD,C);
	draw_rectangle(HG,BD,couleur_RGB(10,10,10));
	
	HG.x = HG.x + (BD.x - HG.x - 15*(taillePolice/2 + taillePolice/30) )/2; //14 est le nombre de lettre dans "Save Complete!"
	HG.y = HG.y - (HG.y - BD.y - taillePolice)/2 + taillePolice*2/10;
	
	if (aQuiLeTour == 2)
		aff_pol("Player 1 Wins!",taillePolice,HG,couleur_RGB(50,50,50));
	else
		aff_pol("Player 2 Wins!",taillePolice,HG,couleur_RGB(50,50,50));
	
	affiche_all();
	attendre(5000);
}
