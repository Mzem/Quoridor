#include "affichage.h"
#include "deplace.h"
#include "mur.h"
#include "save.h"

//Test clic boutons menu
int clicBouton1(POINT clic, Plateau P){
	POINT HG, BD;
	
	HG.x = X/2 - 11*P.tailleCase.x/2;	//presque *6
	BD.x = X/2 + 11*P.tailleCase.x/2;
	BD.y = P.tailleCase.y + 3*P.tailleCase.y/2 + P.tailleCase.y/3 + + 3*P.tailleCase.y/2 + P.tailleCase.y/3;
	HG.y = BD.y + 3*P.tailleCase.y/2; 
	
	if ( clic.x > HG.x && clic.x < BD.x && clic.y > BD.y && clic.y < HG.y )
		return 1;
		
	return 0;
}

int clicBouton2(POINT clic, Plateau P){
	POINT HG, BD;
	
	HG.x = X/2 - 11*P.tailleCase.x/2;	//presque *6
	BD.x = X/2 + 11*P.tailleCase.x/2;
	BD.y = P.tailleCase.y + 3*P.tailleCase.y/2 + P.tailleCase.y/3;
	HG.y = BD.y + 3*P.tailleCase.y/2;
	
	if ( clic.x > HG.x && clic.x < BD.x && clic.y > BD.y && clic.y < HG.y )
		return 1;
		
	return 0;
}

int clicBouton3(POINT clic, Plateau P){
	POINT HG, BD;
	
	HG.x = X/2 - 11*P.tailleCase.x/2;	//presque *6
	BD.x = X/2 + 11*P.tailleCase.x/2;
	BD.y = P.tailleCase.y;
	HG.y = BD.y + 3*P.tailleCase.y/2;  
	
	if ( clic.x > HG.x && clic.x < BD.x && clic.y > BD.y && clic.y < HG.y )
		return 1;
		
	return 0;
}

//Test clic boutons jeu
int clicBACK(POINT clic, Plateau P){	
	POINT HG, BD;
	HG.x = P.hautDroite.x + (X - P.hautDroite.x)/2 - 3*P.tailleCase.x/2 ;
	BD.x = P.hautDroite.x + (X - P.hautDroite.x)/2 + 3*P.tailleCase.x/2 ;
	HG.y = Y/2 + 2*P.tailleCase.y/3;
	BD.y = Y/2 - 2*P.tailleCase.y/3;
	
	if (clic.x > HG.x && clic.x < BD.x && clic.y > BD.y && clic.y < HG.y)		
		return 1;
	
	return 0;
}

int clicSAVE(POINT clic, Plateau P){	
	POINT HG, BD;
	HG.x = P.hautDroite.x + (X - P.hautDroite.x)/2 - 3*P.tailleCase.x/2 ;
	BD.x = P.hautDroite.x + (X - P.hautDroite.x)/2 + 3*P.tailleCase.x/2 ;
	HG.y = Y/2 + 2*P.tailleCase.y/3 + P.tailleCase.y/2 + 4*P.tailleCase.y/3;
	BD.y = Y/2 - 2*P.tailleCase.y/3 + P.tailleCase.y/2 + 4*P.tailleCase.y/3;
	
	if (clic.x > HG.x && clic.x < BD.x && clic.y > BD.y && clic.y < HG.y)		
		return 1;
	
	return 0;
}

int clicQUIT(POINT clic, Plateau P){	
	POINT HG, BD;
	HG.x = P.hautDroite.x + (X - P.hautDroite.x)/2 - 3*P.tailleCase.x/2 ;
	BD.x = P.hautDroite.x + (X - P.hautDroite.x)/2 + 3*P.tailleCase.x/2 ;
	HG.y = Y/2 + 2*P.tailleCase.y/3 - P.tailleCase.y/2 - 4*P.tailleCase.y/3;
	BD.y = Y/2 - 2*P.tailleCase.y/3 - P.tailleCase.y/2 - 4*P.tailleCase.y/3;
	
	if (clic.x > HG.x && clic.x < BD.x && clic.y > BD.y && clic.y < HG.y)		
		return 1;
	
	return 0;
}

//Test si un joueur a gagne
int aGagne(Joueur J){
	if (J.indiceJoueur1.y == 8)
		return 1;
	if (J.indiceJoueur2.y == 0)
		return 1;
	return 0;
}

//Initialise les elements du jeu
void initJeu(Joueur* J, Mur* M, Plateau* P)
{	
	//Initialisation de la taille des elements du plateau : plateau, cases et murs
	//on va definir le plateau de facon a le diviser en 9 cases et 8 murs tq tCase = 5*tMur
	//X/4 correspond a la marge laissee pour afficher le score et le nombre de murs
	P->hautDroite.x = (X - X/4) - (X - X/4)%53;
	P->hautDroite.y = Y - Y%53; 			
									
	//definition de l'epaisseur du mur et de la taille d'une case
	P->epaisseurMur.x = P->hautDroite.x/53;		
	P->epaisseurMur.y = P->hautDroite.y/53;
	P->tailleCase.x = 5*P->epaisseurMur.x;	
	P->tailleCase.y = 5*P->epaisseurMur.y;
			
	//position en bas a gauche du plateau dans la fenetre compte tenu des marges qu'on va laisser
	P->basGauche.x = (Y - P->hautDroite.y)/2;	
	P->basGauche.y = (Y - P->hautDroite.y)/2;
	
	P->hautDroite.x += P->basGauche.x;
	P->hautDroite.y += P->basGauche.y;
	
	//Initialisation de la position des joueurs et du nombre des murs
	J->indiceJoueur1.x = 4;	J->indiceJoueur1.y = 0;
	J->indiceJoueur2.x = 4;	J->indiceJoueur2.y = 8;
	J->aQuiLeTour = 1;
	M->nbMursJoueur1 = 10; M->nbMursJoueur2 = 10;
}

//Jeu Multi
void tourDeJeuMulti(int* retour, int cases[9][9], Etats* E, Joueur* J, Mur* M, Plateau P)
{	
	int nbMursJoueurActuel = (J->aQuiLeTour == 1 ? M->nbMursJoueur1 : M->nbMursJoueur2);
	
	while (1)
	{
		*retour = 0;
		POINT clic = wait_clic();
			
		if ( clicDansCaseAccessible(clic, cases, J, P) )
			break;	//On sort en ayant retenu les nouveaux indices du joueur actuel
		
		if ( clicBACK(clic, P) && (*E)->suiv != NULL){	//On ne peut pas retourner en arriere au depart
			afficheBoutonBACK(couleur_RGB(170,170,170),P);
			affiche_all();								//Effet sur le bouton
			attendre(100);
			*retour = 1;	//retour 1 signifie qu'on a retourne un coup en arriere, on n'enregistre pas cet etat dans la liste
			*E = suppDebut(*E, cases, J, M);
			break;
		}
		if ( clicSAVE(clic, P)){
			afficheBoutonSAVE(couleur_RGB(170,170,170),P);
			annonceSAVE(P);								//Effet sur le bouton
			affiche_all();
			attendre(1000);
											
			*retour = 1;	//On n'enregistre pas cet etat
			save(*E);
			J->aQuiLeTour = (J->aQuiLeTour == 1 ? 2 : 1);

			break;
		}
		if ( clicQUIT(clic, P)){
			afficheBoutonQUIT(couleur_RGB(170,170,170),P);
			affiche_all();								//Effet sur le bouton
			attendre(200);
			*retour = -1;	//retour -1 signifie qu'on quitte le jeu
			break;
		}
		
		if (nbMursJoueurActuel > 0)	//Si il reste des murs au joueur actuel
		{
			if ( clicZoneMurVideV (clic, *J, M, P) )
			{
				(J->aQuiLeTour == 1 ? M->nbMursJoueur1-- : M->nbMursJoueur2-- );	//On diminue le nombre de murs
				break;
			}
			if ( clicZoneMurVideH (clic, *J, M, P) )
			{
				(J->aQuiLeTour == 1 ? M->nbMursJoueur1-- : M->nbMursJoueur2-- );
				break;
			}
		} 
	}
}

void jouerMulti(Etats E, Joueur J, Mur M, Plateau P)
{
	int retour = 0;
	
	while (!aGagne(J))
	{	
		int cases[9][9] = {{0}}; 			//Tableau ou sont marquees les cases accessibles, a chaque tour on reinitialise ce tableau
		
		casesAccessibles(cases, J, M, P);	//On repere dans le tableau cases, les cases accessibles pour le joueur qui est en train de jouer
		
		if (!retour)
			E = ajoutDebut(E,cases,J,M);	//Sauvegarde l'etat de jeu actuel, fais une sauvegarde
		
		afficheJeuMulti(0,cases, J, M, P);	//Affiche le jeu actuel
		
		tourDeJeuMulti(&retour, cases, &E, &J, &M, P);
		
		if (retour == -1)
			break;
		
		J.aQuiLeTour = (J.aQuiLeTour == 1 ? 2 : 1);
		
		if (aGagne(J)){
			afficheJeuMulti(1,cases, J, M, P);
			afficheVictoire(J.aQuiLeTour,P);
		}
	}
	destruction(E);							//On libere toute la memoire allouee a E, on n'a plus besoin des retours en arriere	
}

//Jeu Solo
POINT IA(int cases[9][9], Joueur J, Mur M, Plateau P)
{
	srand(time(NULL));
	
	POINT clic;
	
	if (rand()%4 != 2)	//Probabilité 3/4 de se deplacer et 1/4 de mettre un mur
	{
		if (J.indiceJoueur2.y != 0 && cases[J.indiceJoueur2.y - 1][J.indiceJoueur2.x] == 1){
			clic.x = J.indiceJoueur2.x;
			clic.y = J.indiceJoueur2.y - 1;
			return coordJoueur(clic,P);
		}
		if (J.indiceJoueur2.x != 1 && cases[J.indiceJoueur2.y - 2][J.indiceJoueur2.x] == 1){
			clic.x = J.indiceJoueur2.x;
			clic.y = J.indiceJoueur2.y - 2;
			return coordJoueur(clic,P);
		}
		if (J.indiceJoueur2.x != 8 && cases[J.indiceJoueur2.y][J.indiceJoueur2.x + 1] == 1){
			clic.x = J.indiceJoueur2.x + 1;
			clic.y = J.indiceJoueur2.y;
			return coordJoueur(clic,P);
		}	
		if (J.indiceJoueur2.x != 0 && cases[J.indiceJoueur2.y][J.indiceJoueur2.x - 1] == 1){
			clic.x = J.indiceJoueur2.x - 1;
			clic.y = J.indiceJoueur2.y;
			return coordJoueur(clic,P);
		}
		if (J.indiceJoueur2.y != 8 && cases[J.indiceJoueur2.y + 1][J.indiceJoueur2.x] == 1){
			clic.x = J.indiceJoueur2.x;
			clic.y = J.indiceJoueur2.y + 1;
			return coordJoueur(clic,P);
		}
	}
	clic.x = J.indiceJoueur1.x;
	clic.y = J.indiceJoueur1.y;
	clic.x = coordJoueur(clic,P).x;
	clic.y = coordJoueur(clic,P).y + P.tailleCase.y/2 + 3;
	if (clicZoneMurVideH(clic, J, &M, P))
		return clic;
		
	clic.x = J.indiceJoueur1.x - 1;
	clic.y = J.indiceJoueur1.y;
	clic.x = coordJoueur(clic,P).x;
	clic.y = coordJoueur(clic,P).y + P.tailleCase.y/2 + 3;
	if (clicZoneMurVideH(clic, J, &M, P))
		return clic;
	
	printf("randomizing\n");
	clic.x = P.basGauche.x + rand()%(P.hautDroite.x - P.basGauche.x);
	clic.y = P.basGauche.y + rand()%(P.hautDroite.y - P.basGauche.y);
	return clic;
}

void tourDeJeuSolo(int* retour, int cases[9][9], Joueur* J, Mur* M, Plateau P)
{	
	int nbMursJoueurActuel = (J->aQuiLeTour == 1 ? M->nbMursJoueur1 : M->nbMursJoueur2);
	
	while (1)
	{
		*retour = 0;
		
		POINT clic = (J->aQuiLeTour == 1 ? wait_clic() : IA(cases, *J, *M, P) );
			
		if ( clicDansCaseAccessible(clic, cases, J, P) )
			break;	//On sort en ayant retenu les nouveaux indices du joueur actuel
		
		if ( clicBACK(clic, P))	//la position du bouton BACK en Multi represente la position du bouton QUIT en solo
		{
			afficheBoutonQUITSolo(couleur_RGB(170,170,170),P);
			affiche_all();								//Effet sur le boutton
			attendre(200);
			*retour = -1;	//retour -1 signifie qu'on quite le jeu
			break;
		}
		
		if (nbMursJoueurActuel > 0)
		{
			if ( clicZoneMurVideV (clic, *J, M, P) )
			{
				(J->aQuiLeTour == 1 ? M->nbMursJoueur1-- : M->nbMursJoueur2-- );
				break;
			}
			if ( clicZoneMurVideH (clic, *J, M, P) )
			{
				(J->aQuiLeTour == 1 ? M->nbMursJoueur1-- : M->nbMursJoueur2-- );
				break;
			}
		} 
	}
}

void jouerSolo(Joueur J, Mur M, Plateau P)
{
	int retour = 0;
	
	while (!aGagne(J))
	{	
		int cases[9][9] = {{0}}; 			//la case a 1 sera accessible, a chaque tour on reinitialise ce tableau
		
		casesAccessibles(cases, J, M, P);	//On repere dans le tableau cases, les cases accessibles pour le joueur qui est en train de jouer
				
		afficheJeuSolo(0,cases, J, M, P);
		
		tourDeJeuSolo(&retour, cases, &J, &M, P);
		
		if (retour == -1)
			break;
		
		J.aQuiLeTour = (J.aQuiLeTour == 1 ? 2 : 1);
		
		if (aGagne(J)){
			afficheJeuSolo(1,cases, J, M, P);
			afficheVictoire(J.aQuiLeTour,P);
		}
	}	
}


