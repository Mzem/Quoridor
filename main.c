#include "jeu.h"

//extern void pour eviter le warning "implicit declaration"
extern void afficheMenu(Plateau P);
extern void afficheBouton1(COULEUR C, Plateau P);
extern void afficheBouton2(COULEUR C, Plateau P);
extern void afficheBouton3(COULEUR C, Plateau P);
extern void initJeu(Joueur* J, Mur* M, Plateau* P);
extern Etats load(Etats E, Joueur* J, Mur* M);
extern void annonceLOAD(Plateau P);


int main()
{
	init_graphics(X,Y);
	int lancement = 1;
	
	while (1)
	{	
		Joueur J;
		Mur M = { {{0}},{{0}} };
		Plateau P;
		Etats E = NULL;
		
		initJeu(&J, &M, &P);
		
		if (lancement){
			afficheMenu(P);
			lancement = 0;
		}
		
		POINT choix = wait_clic();
	
		if ( clicBouton1(choix,P) )
		{
			afficheBouton1(couleur_RGB(170,170,170), P);
			affiche_all();
			attendre(200);
			
			jouerSolo(J, M, P);
			afficheMenu(P);
		}
		else if ( clicBouton2(choix,P) )
		{
			afficheBouton2(couleur_RGB(170,170,170), P);
			affiche_all();
			attendre(200);
			
			jouerMulti(E, J, M, P);
			afficheMenu(P);
		}
		else if ( clicBouton3(choix,P) )
		{
			afficheBouton3(couleur_RGB(170,170,170), P);
			affiche_all();
			attendre(200);
			
			E = load(E, &J, &M);
			
			if (E != NULL)
				jouerMulti(E, J, M, P);
				
			else{
				annonceLOAD(P);
				affiche_all();
				attendre(1000);
			}
			afficheMenu(P);
		}
	}
	wait_escape();
	
	return 0;
}
