/**
 * \file		projet17.c / nom à modifier pour les rendus (section 4)
 * \version		0.0
 * \date		2017-mm-dd
 * \author		Nom et SCIPER
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


//             Symboles définies avec l'instruction enum


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
	if (n<2){
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
	if (nbp<2 || nbp>(n*n) ){
		erreur_nbP(nbp,n);
		return 0;
	}
	else{
		if (verbose){
		printf("il y a %d personnes dans ce monde\n",nbp);
	}}
	
	//test des personnes
	int GrandTab[nbp][5];
	int a, b, k, r;
	if (verbose){
		printf("placer les gens\n");
		}
	scanf("%d %d %d %d", &GrandTab[0][0], &GrandTab[0][1], &GrandTab[0][2], &GrandTab[0][3]);
	GrandTab[0][4] = 1;
	if (verbose){
		printf("personne1 est en(");
		for (r=0; r<3; r++){
			printf("%d,", GrandTab[0][r]);
		}
		printf("%d)\n", GrandTab[0][3]);
	}
	for (k=1;k<nbp;k++){
		if (verbose){
			printf("placer la personne suivante\n");
		}
		scanf("%d %d %d %d", &GrandTab[k][0], &GrandTab[k][1], &GrandTab[k][2], &GrandTab[k][3]);
		GrandTab[k][4] = 0;
		for (b=0; b<3; b++){
			if (GrandTab[k][b] < 0 || GrandTab[k][b] > n-1){
				erreur_indice_ligne_colonne(GrandTab[k][b],k);
				return 0;
				}
			}
		for (a=0;a<k;a++){
			if (GrandTab[k][0] == GrandTab[a][0] && GrandTab[k][1] == GrandTab[a][1]){
				erreur_superposition(k, a);
				return 0;
			}
		}
		if (verbose){
			printf("personne %d est en [%d,%d,%d,%d]\n", k+1 ,GrandTab[k][0], GrandTab[k][1], GrandTab[k][2], GrandTab[k][3]);
		}
	}
	
	void affGrille(taille,nbp,grandTab){
	int i, j, k;
	for (i=0;i<taille;i++){
		for (j=0;j<taille;j++){
			for (k=0;k<taille;k++){
				printf("--")
			}
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
