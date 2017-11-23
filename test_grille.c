#include <stdio.h>
#include <stdlib.h>

/*
void affGrille(int taille, int * grandTab){
	int i, j, k;
	for (i=0;i<taille;i++){
		
		for (j=0;j<taille;j++){
			
			for (k=0;k<taille;k++){ //print les lignes du dessus et dessous
				printf("---");
			}
			if (grandTab[1][0] == i && grandTab[1][1] == j){
				Printf("P");
			}
			printf("\n");
			}
		}
	}
	*/
void test(int ** Tab){
	
	printf ("Tab[1][2] %d\n", Tab[1][2])	;
	
	
	}

int main(void){
	int taille = 3;
	int grandTab[1][5]={{0,1,2,3,4}};
	int haha[5]={0,1,2,3,4};
	test(grandTab);
	//affGrille(taille,grandTab);
	}


