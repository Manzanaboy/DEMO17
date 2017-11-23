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

//             Symboles définies avec l'instruction enum
enum Pers{LIGNEPERS, COLPERS, LIGNEBUT, COLBUT, ETAT};

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
	int GrandTab[nbp][NB_INFO_PERS];
	int a, b, k;
	if (verbose){
		printf("placer les gens\n");
		}
	//placement pers 1
	scanf("%d %d %d %d", &GrandTab[0][LIGNEPERS], &GrandTab[0][COLPERS], &GrandTab[0][LIGNEBUT], &GrandTab[0][COLBUT]);
	GrandTab[0][ETAT] = 1;
	//placement autres pers
	for (k=1;k<nbp;k++){
		scanf("%d %d %d %d", &GrandTab[k][LIGNEPERS], &GrandTab[k][COLPERS], &GrandTab[k][LIGNEBUT], &GrandTab[k][COLBUT]);
		GrandTab[k][ETAT] = 0;
	//test indices
		for (b=LIGNEPERS; b<COLBUT; b++){
			if (GrandTab[k][b] < 0 || GrandTab[k][b] > n-1){
				erreur_indice_ligne_colonne(GrandTab[k][b],k);
				return 0;
			}
		}
	}
	//test superposition
	for (a=1; a<nbp; a++){
		for (k=0; k<a; k++){
			if (GrandTab[k][LIGNEPERS] == GrandTab[a][LIGNEPERS] && GrandTab[k][COLPERS] == GrandTab[a][COLPERS]){
				erreur_superposition(k, a);
				return 0;
			}
		}
	}
	
	
	
	return EXIT_SUCCESS;
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
