/**
 * \file		289148.c
 * \version		2.2
 * \date		2017-11-02
 * \author		Perez Grether Damian 289148
 * \brief		Programme pour le projet du cours CS-111(c)
 *              le nom projet17.c est utile pour la mise au point.
 *              Pour les rendus, il faut modifier le nom du fichier comme
 *              expliqué en section 4 de la donnée (on utilise son SCIPER)
 */

// *******************************************************************
// 		inclusion de fichiers en-tête avec la directives include

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



// *******************************************************************
//			   Symboles définis avec la directive define
#define NB_INFO_PERS 5
#define T_MIN_MONDE 2
#define NB_MIN_PERS 2
#define NB_CASE 8
#define GAUCHE -1
#define DROITE 1
#define HAUT -1
#define BAS 1
#define DECALAGE 1
#define POSMIN 0
#define NB_MAX_CYCLE 200

//             Symboles définies avec l'instruction enum
enum Pers{LIGNEPERS, COLPERS, LIGNEBUT, COLBUT, ETAT};
enum Etat{NORMAL, CONT, INCUB, VACC, VIDE, BUT};
// *******************************************************************
//						Functions declaration

// ########   ne pas modifier ces déclarations de fonctions    #######

/**
 * \brief	Si nbSim n'est pas strictement positif
 * \param   nbSim		la valeur invalide de nbSim
 */
static void erreur_nbSim(int nbSim);

/**
 * \brief	Si la taille du monde n'est pas strictement supérieure à 1
 * \param 	n	   		la valeur invalide
 */
static void erreur_taille_monde(int n);

/**
 * \brief	Si le nombre de personnes n'est pas dans [2, n*n]
 * \param 	nbP		la valeur invalide
 * \param 	n		la taille du monde
 */

static void erreur_nbP(int nbP, int n);

/**
 * \brief	Si un indice de position ou de but n'est pas dans [0, n-1]
 * \param 	indice	             la première valeur d'indice invalide
 * \param 	indicePersonne		 l'indice de la personne dans [0, nbP-1]
 */

static void erreur_indice_ligne_colonne(int indice, int indicePersonne);

/**
 * \brief	Si deux personnes ont la même position
 * \param 	indiceP_A	l'indice de la premiere personne dans [0, nbP-1]
 * \param 	indiceP_B	l'indice de la seconde  personne dans [0, nbP-1]
 */
static void erreur_superposition(int indiceP_A, int indiceP_B);

static int lireVerbose();
/*\brief	Lit l'input verbose.
 * */
 
static int lireGrille(int verbose);
/*\brief	Lit et vérifie l'intput pour afficher la grille.
 * */
 
static int lireSim(int verbose);
/*\brief	Lit et vérifie l'intput pour du nombre de simulations.
 * */
 
static int lireMonde(int verbose);
/*\brief	Lit et vérifie l'intput de la taille du monde.
 * */
 
static int lirenbp(int verbose, int n);
/*\brief	Lit et vérifie l'intput du nombre de personnes.
 * */
 
static void placerPers(int grandTab[][NB_INFO_PERS], int verbose,  int n, int nbp);
/*\brief	Lit et vérifie l'intput des personnes et les place 
 * 			dans grandTab.
 * */

static int rebouclement(int x,int n);
/*\brief	Vérifie une position et la change si besoins.
 * */
static void grille(int tab[][NB_INFO_PERS], int n, int nbp);
/*\brief	Affiche la grille du monde avec les personnes à l'intérieur.
 * */
static int libre(int tab[][NB_INFO_PERS], int nbp, int x, int y);
/*\brief	Vérifie si une la case (x,y) est occupée.
 * */
static void nouvBut(int n, int tab[][NB_INFO_PERS], int i);
/*\brief	Cherche aléatoirement un nouveau but.
 * */
static void move(int n, int tab[][NB_INFO_PERS], int nbp, int i);
/*\brief	Deplace la personne d'indice i selon son but et dans la 
 * 			mesure du possible ou lui attribue un nouveau but.
 * */
static void contamine(int tab[][NB_INFO_PERS], int i, int nbp, int n);
/*\brief	Vérifie si la personne d'indice i contamine les personnes
 * 			à ses alentours si elle est contaminée. Si elle est 
 * 			non-contaminée et non-vaccinée alors la fonction vérifie
 * 			si cette personne est contaminée par ses voisines.
 * */
static void mergemoi(int tab[],int liun[], int lide[], int tun, int tde);
/*\brief	Met les valeurs de deux listes liun et lide de longeurs 
 * 			respectives tun et tde déjà triés dans une troisième liste
 * 			tab de manière à ce que les éléments de tab soient triés.
 * */
static void msort(int tab[], int l);
/*\brief	Trie la liste tab de longueur l selon le principe du 
 * 			mergesort.
 * */
static int simul(int tab[][NB_INFO_PERS], int n, int nbp, int afG, int nbvacc);
/*\brief	Crée une simulation de contamination avec un nombre de 
 * 			personnes donnés et un nombre de personnes vaccinées dans
 * 			un monde de taille n et affiche la grille si besoins.
 * */
static void regroupe(int tab[][NB_INFO_PERS], int n, int nbp, int afG, int nbSim);
/*\brief	regroupe tous les contextes possibles et fait nbSim nombre
 * 			de simulations pour chacun. trie les resultats et affiche
 * 			la valeur mediane du nombre de cycles.
 * */
// ############################ END ##################################

// *******************************************************************
//						Global variable

/** variable booléenne déterminant l'affichage des messages d'invitation */
static bool	verbose;

// *******************************************************************
//						MAIN

int main(void)
{
	//rendu 1
	int nbSim, n, nbp, afG;
	verbose = lireVerbose();
	afG = lireGrille(verbose);
	nbSim = lireSim(verbose);
	n = lireMonde(verbose);
	nbp = lirenbp(verbose, n);
	int grandTab[nbp][NB_INFO_PERS];
	placerPers(grandTab, verbose, n, nbp);
	
	//simulations
	regroupe(grandTab, n, nbp, afG, nbSim);
	return EXIT_SUCCESS;
}

// *******************************************************************
//              ***        mes fonctions        ***
// *******************************************************************
static int lireVerbose(){
	int reponse;
	scanf("%d", &reponse);
	if(reponse==0){
		return 0;
	}
	else{
		return 1;
	}
	}

static int lireGrille(int verbose){
	int afG;
	if (verbose){
		printf("#afficher la grille ? 0=non 1=oui\n");
	}
	scanf("%d", &afG);
	return afG;
	}

static int lireSim(int verbose){
	int nbSim;
	if (verbose){
		printf("#nombre de simulations : \n");
	}
	scanf("%d",&nbSim);
	if (nbSim <= 0){
		erreur_nbSim(nbSim);
		exit(EXIT_FAILURE);
	}
	if (verbose){
		printf("#vous avez choisis %d simulation(s)\n", nbSim);
	}
	return nbSim;
	}

static int lireMonde(int verbose){
	int n;
	if (verbose){
		 printf("#choisissez la taille du monde\n");
	}
	scanf("%d", &n);
	if (n < T_MIN_MONDE){
		erreur_taille_monde(n);
		exit(EXIT_FAILURE);
	}
	if (verbose){
		printf("#le monde fait %d*%d \n", n, n);
	}
	return n;
	}

static int lirenbp(int verbose, int n){
	int nbp;
	if (verbose){
		printf("#combien de personnes habitent ce monde ?\n");
	}
	scanf("%d", &nbp);
	if (nbp < NB_MIN_PERS || nbp>(n*n) ){
		erreur_nbP(nbp,n);
		exit(EXIT_FAILURE);
	}
	else{
		if (verbose){
		printf("#il y a %d personnes dans ce monde\n",nbp);
		}
	}
	return nbp;
	}

static void placerPers(int grandTab[][NB_INFO_PERS], int verbose,  int n, int nbp){
	int a, b, k;
	if (verbose){
		printf("#placer les gens\n");
		}
	scanf("%d %d %d %d", &grandTab[0][LIGNEPERS], &grandTab[0][COLPERS], &grandTab[0][LIGNEBUT], &grandTab[0][COLBUT]);
	grandTab[0][ETAT] = CONT;
	for (k=1;k<nbp;k++){
		scanf("%d %d %d %d", &grandTab[k][LIGNEPERS], &grandTab[k][COLPERS], &grandTab[k][LIGNEBUT], &grandTab[k][COLBUT]);
		grandTab[k][ETAT] = NORMAL;
		for (b=LIGNEPERS; b<COLBUT; b++){
			if (grandTab[k][b] < 0 || grandTab[k][b] > n-1){
				erreur_indice_ligne_colonne(grandTab[k][b],k);
				exit(EXIT_FAILURE);
			}
		}
	}
	for (a=1; a<nbp; a++){
		for (k=0; k<a; k++){
			if (grandTab[k][LIGNEPERS] == grandTab[a][LIGNEPERS] && grandTab[k][COLPERS] == grandTab[a][COLPERS]){
				erreur_superposition(k, a);
				exit(EXIT_FAILURE);
			}
		}
	}
	}

static int rebouclement(int x,int n){
	if(x < POSMIN || x == n){
		(x < POSMIN )? (x = (n+GAUCHE)) : (x = POSMIN);
		}
		return x;
	}
	
static void grille(int tab[][NB_INFO_PERS], int n, int nbp){
	int i, j;
	printf("#");
	for (i=0; i<n; i++){
		printf(" _");
		}
	printf("\n");
	int gr[n][n];
	for (i=0; i<n; i++){
		for (j=0;j<n;j++){
			gr[i][j]=VIDE;
			}
		}
	for (i=0; i<nbp; i++){
		gr[tab[i][LIGNEPERS]][tab[i][COLPERS]] = tab[i][ETAT];
		if (gr[tab[i][LIGNEBUT]][tab[i][COLBUT]] == VIDE){
			gr[tab[i][LIGNEBUT]][tab[i][COLBUT]] = BUT;
			}
		}
	for (i=0; i<n; i++){
		printf("#");
		for (j=0; j<n; j++){
			printf("|");
			switch (gr[i][j]){
				case VIDE:
					printf("_");
					break;
				case INCUB:
					printf("I");
					break;
				case NORMAL:
					printf("N");
					break;
				case CONT:
					printf("C");
					break;
				case VACC:
					printf("V");
					break;
				case BUT:
					printf("B");
					break;
			}
		}
		printf("|\n");
		}
	}
	
static int libre(int tab[][NB_INFO_PERS], int nbp, int x, int y){
	int res = 0;
	for(int i=0; i<nbp; i++){
		if(tab[i][LIGNEPERS] == x && tab[i][COLPERS] == y){
			res = i + DECALAGE;
			i=nbp;
			}
		}
	return res;
	}

static void nouvBut(int n, int tab[][NB_INFO_PERS], int i){
	int pos = 0;
	int indx;
	int indy;
	do {
		pos=1;
		indx = (rand()%n);
		indy = (rand()%n);
		if (indx == tab[i][LIGNEPERS] && indy == tab[i][COLPERS] ){
			pos=0;
			}
		} while (pos!=1);
	tab[i][LIGNEBUT]=indx;
	tab[i][COLBUT]=indy;
}

static int shortest(int position, int but, int n){
	int dif = but - position;
	int dep=0;
	if (dif < 0){
		if (abs(dif) <= (n/2)){
			dep = GAUCHE;	
			}
		else {
			dep = DROITE;	
			}
		}
	if (dif > 0){
		if (abs(dif) <= (n/2)){
			dep = DROITE;
			}
		else {
			dep = GAUCHE;	
			}
		}
	return dep;
	}

static int allerVersBut(int tab[][NB_INFO_PERS], int nbp, int depx, int depy, int i){
	if (!libre(tab,nbp,depx,depy)){
		tab[i][LIGNEPERS] =depx;
		tab[i][COLPERS] =depy;
		return 1;
		}
	if (!libre(tab,nbp,depx,tab[i][COLPERS])){
		tab[i][LIGNEPERS] =depx;
		return 1;
		}	
	if (!libre(tab,nbp,tab[i][LIGNEPERS],depy)){
		tab[i][COLPERS] =depy;
		return 1;
		}
	return 0;
	}

static int bloquage(int tab[][NB_INFO_PERS], int posx, int posy, int nbp, int i, int n){
	int depx;
	int depy;
	for (int k= -1;k<=1;k++){
		for (int j=-1;j<=1;j++){
			depx = posx + k;
			depy = posy + j;
			depx = rebouclement(depx,n);
			depy = rebouclement(depy,n);
			if(!(k == 0 && j == 0)){
				if (!libre(tab, nbp, depx, depy)){
					tab[i][LIGNEPERS] = depx;
					tab[i][COLPERS] = depy;
					return 1;
					}
				}
			}
		}
	return 0;
	}

static void move(int n, int tab[][NB_INFO_PERS], int nbp, int i){
	int depx = tab[i][LIGNEPERS];
	int depy = tab[i][COLPERS];
	int dep;
	if (tab[i][LIGNEPERS] == tab[i][LIGNEBUT] && tab[i][COLPERS] == tab[i][COLBUT]){
		nouvBut(n,tab,i);
		}
	depx = depx + shortest(depx, tab[i][LIGNEBUT], n);
	depy = depy + shortest(depy, tab[i][COLBUT], n);
	depx = rebouclement(depx,n);
	depy = rebouclement(depy,n);
	dep = allerVersBut(tab, nbp, depx, depy, i);
	if (!dep){
		dep = bloquage(tab, depx, depy, nbp, i, n);
		}
	if (!dep){
		nouvBut(n, tab, i);
		}
}

static void contamine(int tab[][NB_INFO_PERS], int i, int nbp, int n){
	int etat = tab[i][ETAT];
	int posx = tab[i][LIGNEPERS];
	int posy = tab[i][COLPERS];
	int indice, depx, depy;
	for (int k=GAUCHE;k<=DROITE;k++){
		for (int j=HAUT;j<=BAS;j++){
			depx = posx + k;
			depy = posy + j;
			depx = rebouclement(depx,n);
			depy = rebouclement(depy,n);
			if (etat == CONT){
				indice = libre(tab, nbp, depx, depy)-DECALAGE;
				if (tab[indice][ETAT] == NORMAL){
					tab[indice][ETAT] = INCUB;
					}
				}
			if (etat == NORMAL){
				indice = libre(tab, nbp, depx, depy)-DECALAGE;
				if (tab[indice][ETAT] == CONT){
					tab[i][ETAT] = INCUB;
					}
				}
			}
		}
	}
	
static void mergemoi(int tab[],int liun[], int lide[], int tun, int tde){
	int i=0,j=0,k=0;
	while(i<tun && j<tde){
		if (liun[i]< lide[j]){
			tab[k]=liun[i];
			i++;
			k++;
			}
		else{
			tab[k]=lide[j];
			j++;
			k++;
			}
		}
	while (i<tun){
		tab[k]=liun[i];
		i++;
		k++;
		}
	while (j<tde){
		tab[k]=lide[j];
		j++;
		k++;
		}
	}
	
static void msort(int tab[], int l){
	if (l>1){
		int i,k=0;
		int mil=l/2;
		int tun = l - mil;
		int tde = l - tun;
		int liun[tun];
		int lide[tde];
		for (i=0;i<tun;i++){
			liun[k] = tab[k];
			k++;
			}
		for (i=0;i<tde;i++){
			lide[i] = tab[k];
			k++;
			}
		msort(liun, tun);
		msort(lide, tde);
		mergemoi(tab,liun,lide, tun, tde);
		}
	}

static int simul(int tab[][NB_INFO_PERS], int n, int nbp, int afG, int nbvacc){
	int nbCycle=0;
	int nbCont=1;
	int i;
	for (i=1;i<=nbvacc;i++){
		tab[i][ETAT]= VACC;
		}
	if (afG){
			grille(tab, n, nbp);
			}
	contamine(tab, 0, nbp, n);
	for (i=0;i<nbp;i++){
			if (tab[i][ETAT] == INCUB){
				tab[i][ETAT] = CONT;
				nbCont++;
				}
			}
	while(nbCycle < NB_MAX_CYCLE && nbCont < nbp-nbvacc){
		for (i=0;i<nbp;i++){
			if (tab[i][ETAT] == INCUB){
				tab[i][ETAT] = CONT;
				nbCont++;
				}
			}
		for(i=0;i<nbp;i++){
			move(n, tab, nbp, i);
			contamine(tab, i, nbp, n);
			}
		if (afG){
			grille(tab, n, nbp);
			}
		nbCycle++;
		}
	for(i=0;i<nbp;i++){
		}
	return nbCycle;
	}

static void regroupe(int tab[][NB_INFO_PERS], int n, int nbp, int afG, int nbSim){
	int nbpSim, nbpVacc, k, l, m;
	float compte;
	int tabde[nbp][NB_INFO_PERS];
	int tabForMerg[nbSim];
	for (nbpSim=nbp; nbpSim>=NB_MIN_PERS; nbpSim--){
		for(nbpVacc=0; nbpVacc<nbpSim-1; nbpVacc++){
			for(k=0; k<nbSim; k++){
				for (l=0; l<nbpSim; l++){
					for(m=0; m<NB_INFO_PERS; m++){
						tabde[l][m] = tab[l][m];
						}
					}
				
				tabForMerg[k] = simul(tabde, n, nbpSim, afG, nbpVacc); 
				}
			msort(tabForMerg, nbSim);
			if (nbSim%2 == 0){
				compte = ((float)tabForMerg[nbSim/2] + (float)tabForMerg[(nbSim/2)-1])/2;
				}
			else{
				compte = tabForMerg[nbSim/2];
				}
			float tauxVacc = (float)nbpVacc/nbpSim;
			float densitePop = nbpSim/(float)(n*n);
			printf("%f %f %.1f\n", densitePop, tauxVacc, compte);
			}
		printf("\n");
		}
	}

// *******************************************************************

// ################## Ne pas modifier ces fonctions ##################
//====================================================================//
//																	  //
//				***		 Fonctions d'erreurs   	***					  //
//																	  //
//					  /!\ NE PAS MODIFIER /!\						  //
//																	  //
//====================================================================//

static void erreur_nbSim(int nbSim)
{
	printf("nbSim (=%d) ne valide pas nbSim > 0 !\n", nbSim);
}

static void erreur_taille_monde(int n)
{
	printf("n (=%d) ne valide pas n > 1 !\n", n);
}

static void erreur_nbP(int nbP, int n)
{
	printf("nbP (=%d) ne valide pas nbP > 1 ET nbP <= %d !\n", nbP, n*n);
}

static void erreur_indice_ligne_colonne(int indice, int indicePersonne)
{
	printf("indice incorrect %d de ligne ou colonne de la personne d'indice %d !\n", 
	       indice, indicePersonne);
}

static void erreur_superposition(int indiceP_A, int indiceP_B)
{
	// s'assure d'avoir les indices A et B dans l'ordre croissant
	if(indiceP_B > indiceP_A) 
	{
		int temp = indiceP_A;
		indiceP_A = indiceP_B;
		indiceP_B = temp;
	}
	
	printf("les personnes d'indices %d et %d se superposent !\n", 
		   indiceP_A, indiceP_B);
}

// ############################ END ##################################
