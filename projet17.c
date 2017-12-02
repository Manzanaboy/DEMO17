/**
 * \file		289148.c
 * \version		1.0
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

static void print(int tab[], int a);
static int rebouclement(int x,int n);
static void grille(int tab[][NB_INFO_PERS], int n, int nbp);
static int libre(int tab[][NB_INFO_PERS], int nbp, int x, int y);
static void nouvBut(int n, int tab[][NB_INFO_PERS], int i);
static void move(int n, int tab[][NB_INFO_PERS], int nbp, int i);
static void contamine(int tab[][NB_INFO_PERS], int i, int nbp, int n);
static int simul(int tab[][NB_INFO_PERS], int n, int nbp, int afG, int nbvacc);
// ############################ END ##################################

// *******************************************************************
//						Global variable

/** variable booléenne déterminant l'affichage des messages d'invitation */
static bool	verbose;

// *******************************************************************
//						MAIN

int main(void)
{

	int reponse, nbSim, n, nbp, afG;
	
	//verbose
	scanf("%d", &reponse);
	if(reponse==0){
		verbose=0;
	}
	else{
		verbose=1;
	}
	
	//affichage de la grille
	if (verbose){
		printf("afficher la grille ? 0=non 1=oui\n");
	}
	scanf("%d", &afG);
	
	//nombre de simulations
	if (verbose){
		printf("nombre de simulations : \n");
	}
	scanf("%d",&nbSim);
	if (nbSim <= 0){
		erreur_nbSim(nbSim);
		return 0;
	}
	if (verbose){
		printf("vous avez choisis %d simulation(s)\n", nbSim);
	}
	
	//taille du monde
	 if (verbose){
		 printf("choisissez la taille du monde\n");
	}
	scanf("%d", &n);
	if (n < T_MIN_MONDE){
		erreur_taille_monde(n);
		return 0;
	}
	if (verbose){
		printf("le monde fait %d*%d \n", n, n);
	}
	
	//nombre de personnes
	if (verbose){
		printf("combien de personnes habitent ce monde ?\n");
	}
	scanf("%d", &nbp);
	if (nbp < NB_MIN_PERS || nbp>(n*n) ){
		erreur_nbP(nbp,n);
		return 0;
	}
	else{
		if (verbose){
		printf("il y a %d personnes dans ce monde\n",nbp);
		}
	}
	
	//test des personnes
	int grandTab[nbp][NB_INFO_PERS];
	int a, b, k;
	if (verbose){
		printf("placer les gens\n");
		}
	//placement pers 1
	scanf("%d %d %d %d", &grandTab[0][LIGNEPERS], &grandTab[0][COLPERS], &grandTab[0][LIGNEBUT], &grandTab[0][COLBUT]);
	grandTab[0][ETAT] = CONT;
	//placement autres pers
	for (k=1;k<nbp;k++){
		scanf("%d %d %d %d", &grandTab[k][LIGNEPERS], &grandTab[k][COLPERS], &grandTab[k][LIGNEBUT], &grandTab[k][COLBUT]);
		grandTab[k][ETAT] = NORMAL;
	//test indices
		for (b=LIGNEPERS; b<COLBUT; b++){
			if (grandTab[k][b] < 0 || grandTab[k][b] > n-1){
				erreur_indice_ligne_colonne(grandTab[k][b],k);
				return 0;
			}
		}
	}
	//test superposition
	for (a=1; a<nbp; a++){
		for (k=0; k<a; k++){
			if (grandTab[k][LIGNEPERS] == grandTab[a][LIGNEPERS] && grandTab[k][COLPERS] == grandTab[a][COLPERS]){
				erreur_superposition(k, a);
				return 0;
			}
		}
	}
	int deuxiemeTab[nbp][NB_INFO_PERS];
	
	simul(grandTab, n, nbp, afG, 0);
	for(int i=0;i<nbp;i++){
		print(grandTab[i],NB_INFO_PERS);
		}
	
	return EXIT_SUCCESS;
}

// *******************************************************************
//              ***        mes fonctions        ***
// *******************************************************************

static int rebouclement(int x,int n){
	if(x < POSMIN || x == n){
		(x < POSMIN )? (x = (n+GAUCHE)) : (x = POSMIN);
		}
		return x;
	}

/*static int abs(int a){
	if (a<0){
		a = -a;
		}
	return a;
	}*/
	
static void grille(int tab[][NB_INFO_PERS], int n, int nbp){
	int i, j;
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
		gr[tab[i][COLPERS]][tab[i][LIGNEPERS]] = tab[i][ETAT];
		if (gr[tab[i][COLBUT]][tab[i][LIGNEBUT]] == VIDE){
			gr[tab[i][COLBUT]][tab[i][LIGNEBUT]] = BUT;
			}
		}
	for (i=0; i<n; i++){
		for (j=0; j<n; j++){
			printf("|");
			switch (gr[i][j]){
			
				case VIDE:
					printf("_");
					break;
				case INCUB:
				case NORMAL:
					printf("N");
					break;
				case CONT:
					printf("C");
					break;
				case VACC:
					printf("V");
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
		if (indx == tab[i][LIGNEBUT] && indy == tab[i][COLBUT] ){
			pos=0;
			}
		} while (pos!=1);
	tab[i][LIGNEBUT]=indx;
	tab[i][COLBUT]=indy;
}

static void move(int n, int tab[][NB_INFO_PERS], int nbp, int i){
	//i = indice de la personne
	//moving variables
	int difx = tab[i][LIGNEBUT] - tab [i][LIGNEPERS];       //but - position
	int depx = tab[i][LIGNEPERS];
	int dify = tab[i][COLBUT] - tab[i][COLPERS];        //but - position
	int depy = tab[i][COLPERS];
	int dep;
	int k=0;
	///////////////////////////

			//but atteint
	if (tab[i][LIGNEPERS] == tab[i][LIGNEBUT] && tab[i][COLPERS] == tab[i][COLBUT]){
		nouvBut(n,tab,i);
		}
	//but a gauche
	if (difx < 0){
		if (abs(difx) <= (n/2)){
			depx = tab[i][LIGNEPERS]+GAUCHE;	
			}
		else {
			depx = tab[i][LIGNEPERS]+DROITE;	
			}
		}
	
		//but a droite
	if (difx > 0){
		if (abs(difx) <= (n/2)){
			depx = tab[i][LIGNEPERS]+DROITE;
			}
		else {
			depx = tab[i][LIGNEPERS]+GAUCHE;	
			}
		}
			
	//but en haut
	if(dify < 0){
		if(abs(dify) <= (n/2)){
			depy = tab[i][COLPERS]+HAUT;
			}
		else{
			depy = tab[i][COLPERS]+BAS;			
		}
	}
		
	//but en bas
	if(dify > 0){
		if(abs(dify) <= (n/2)){
			depy = tab[i][COLPERS]+BAS;
			}
		else{
			depy = tab[i][COLPERS]+HAUT;
		}
	}
	depx = rebouclement(depx,n);
	depy = rebouclement(depy,n);
	
	//test si case libre
	if (!libre(tab,nbp,depx,depy)){
		tab[i][LIGNEPERS] =depx;
		tab[i][COLPERS] =depy;
		dep=1;
		}
	else if (!libre(tab,nbp,depx,tab[i][COLPERS])){
		tab[i][LIGNEPERS] =depx;
		dep=1;
		}	
	else if (!libre(tab,nbp,tab[i][LIGNEPERS],depy)){
		tab[i][COLPERS] =depy;
		dep=1;
		}
		
	/*if(tab[i][LIGNEPERS] < POSMIN || tab[i][LIGNEPERS] == n){
		(tab[i][LIGNEPERS] < POSMIN )? (tab[i][LIGNEPERS] = (n+GAUCHE)) : (tab[i][LIGNEPERS] = POSMIN);
		}
	if(tab[i][COLPERS] < POSMIN || tab[i][COLPERS] == n){
		(tab[i][COLPERS] < POSMIN )? (tab[i][COLPERS] = (n+HAUT)) : (tab[i][COLPERS] = POSMIN);
		}*/
			
	//si elle peut pas aller vers l'objectif
	while(dep != 1){
		switch(k){
			case 0:
				if(!libre(tab,nbp,tab[i][LIGNEPERS]+GAUCHE,tab[i][COLPERS]+HAUT)){
					tab[i][LIGNEPERS]--;
					tab[i][COLPERS]--;
					dep=1;
					break;
					}
			case 1:
				if(!libre(tab,nbp,tab[i][LIGNEPERS],tab[i][COLPERS]+HAUT)){
					tab[i][COLPERS]--;
					dep=1;
					break;
					}
			case 2:
				if(!libre(tab,nbp,tab[i][LIGNEPERS]+DROITE,tab[i][COLPERS]+HAUT)){
					tab[i][LIGNEPERS]++;
					tab[i][COLPERS]--;
					dep=1;
					break;
					}
			case 3:
				if(!libre(tab,nbp,tab[i][LIGNEPERS]+GAUCHE,tab[i][COLPERS])){
					tab[i][LIGNEPERS]--;
					dep=1;
					break;
					}
			case 4:
				if(!libre(tab,nbp,tab[i][LIGNEPERS]+DROITE,tab[i][COLPERS])){
					tab[i][LIGNEPERS]++;
					dep=1;
					break;
					}
			case 5:
				if(!libre(tab,nbp,tab[i][LIGNEPERS]+GAUCHE,tab[i][COLPERS]+BAS)){
					tab[i][LIGNEPERS]--;
					tab[i][COLPERS]++;
					dep=1;
					break;
					}
			case 6:
				if(!libre(tab,nbp,tab[i][LIGNEPERS],tab[i][COLPERS]+BAS)){
					tab[i][COLPERS]++;
					dep=1;
					break;
					}
			case 7:
				if(!libre(tab,nbp,tab[i][LIGNEPERS]+DROITE,tab[i][COLPERS]+BAS)){
					tab[i][LIGNEPERS]++;
					tab[i][COLPERS]++;
					dep=1;
					break;
					}
			case 8:
				dep=1;
				nouvBut(n,tab,i);
				break;
			}
		k++;
		}
	if(tab[i][LIGNEPERS] < POSMIN || tab[i][LIGNEPERS] == n){
		(tab[i][LIGNEPERS] < POSMIN )? (tab[i][LIGNEPERS] = (n+GAUCHE)) : (tab[i][LIGNEPERS] = POSMIN);
		}
	if(tab[i][COLPERS] < POSMIN || tab[i][COLPERS] == n){
		(tab[i][COLPERS] < POSMIN )? (tab[i][COLPERS] = (n+HAUT)) : (tab[i][COLPERS] = POSMIN);
		}
}

static void contamine(int tab[][NB_INFO_PERS], int i, int nbp, int n){
	int k=0;
	int posx, posy, val;
	if (tab[i][ETAT] == CONT){
		while(k<NB_CASE){
			posx = tab[i][LIGNEPERS];
			posy = tab[i][COLPERS];
		switch(k){
			case 0:
				posx = posx+GAUCHE;
				posy = posy+HAUT;
				break;
			case 1:
				posy = posy+HAUT;
				break;
			case 2:
				posx = posx+DROITE;
				posy = posy+HAUT;
				break;
			case 3:
				posx = posx+GAUCHE;
				break;
			case 4:
				posx = posx+DROITE;
				break;
			case 5:
				posx = posx+GAUCHE;
				posy = posy+BAS;
				break;
			case 6:
				posy = posy+BAS;
				break;
			case 7:
				posx = posx+DROITE;
				posy = posy+BAS;
				break;
			}
		posx = rebouclement(posx,n);
		posy = rebouclement(posy,n);
		val=libre(tab,nbp,posx,posy);
		if(val){
			if(tab[val-DECALAGE][ETAT] == NORMAL){
				tab[val-DECALAGE][ETAT] = INCUB;
				printf("pers %d cont par %d\n", i, val-1);
				}
			}	
		k++;
		}
	}
	
	if (tab[i][ETAT] == NORMAL){
		while(k<NB_CASE){
			posx = tab[i][LIGNEPERS];
			posy = tab[i][COLPERS];
		switch(k){
			case 0:
				posx = posx+GAUCHE;
				posy = posy+HAUT;
				break;
			case 1:
				posy = posy+HAUT;
				break;
			case 2:
				posx = posx+DROITE;
				posy = posy+HAUT;
				break;
			case 3:
				posx = posx+GAUCHE;
				break;
			case 4:
				posx = posx+DROITE;
				break;
			case 5:
				posx = posx+GAUCHE;
				posy = posy+BAS;
				break;
			case 6:
				posy = posy+BAS;
				break;
			case 7:
				posx = posx+DROITE;
				posy = posy+BAS;
				break;
			}
		posx = rebouclement(posx,n);
		posy = rebouclement(posy,n);
		val=libre(tab,nbp,posx,posy);
		if(val){
			if(tab[val-DECALAGE][ETAT] == CONT){
				tab[i][ETAT] = INCUB;
				printf("pers %d cont par %d\n", i, val-1);
				}
			}	
		k++;
		}
	}	
	}

static void print(int tab[], int a){
	for(int i=0;i<a;i++){
		printf("%d ",tab[i]);
		}
	printf("\n");
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
	for (i=0;i<nbvacc;i++){
		tab[nbp-i][ETAT]= VACC;
		}
	while(nbCycle < NB_MAX_CYCLE && nbCont < nbp-nbvacc){
		for (i=0;i<nbp;i++){
			if (tab[i][ETAT] == INCUB){
				tab[i][ETAT] = CONT;
				nbCont++;
				printf("nbCont %d lim=%d", nbCont, nbp-nbvacc);
				print(tab[i], nbp);
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
		print(tab[i],NB_INFO_PERS);
		}
	return nbCycle;
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
