#include <stdio.h>
#include <stdlib.h>

#define MAX_CYCLE 10 

int abs(int a){
	if (a<0){
		a = -a;
		}
	return a;
	}
	
void grille(int tab[][5], int n, int nbp){
	int i, j;
	for (i=0; i<n; i++){
		printf(" _");
		}
	printf("\n");
	int gr[n][n];
	for (i=0; i<n; i++){
		for (j=0;j<n;j++){
			gr[i][j]=0;
			}
		}
	for (i=0; i<nbp; i++){
		gr[tab[i][1]][tab[i][0]] = tab[i][4];
		if (gr[tab[i][3]][tab[i][2]] == 0){
			gr[tab[i][3]][tab[i][2]] = 6;
			}
		}
	for (i=0; i<n; i++){
		for (j=0; j<n; j++){
			printf("|");
			switch (gr[i][j]){
			
				case 0:
					printf("_");
					break;
				case 1:
					printf("N");
					break;
				case 2:
					printf("C");
					break;
				case 6:
					printf("B");
					break;
			}
		}
		printf("|\n");
		
		}
	}
	
int libre(int tab[][5], int nbp, int x, int y){
	int res = 0;
	for(int i=0; i<nbp; i++){
		if(tab[i][0] == x && tab[i][1] == y){
			res = i + 1;
			i=nbp;
			}
		}
	return res;
	}

void nouvBut(int n, int tab[][5], int i){
	int pos = 0;
	int indx;
	int indy;
	do {
		pos=1;
		indx = (rand()%n);
		indy = (rand()%n);
		if (indx == tab[i][0] && indy == tab[i][1] ){
			pos=0;
			}
		if (indx == tab[i][2] && indy == tab[i][3] ){
			pos=0;
			}
		} while (pos!=1);
	tab[i][2]=indx;
	tab[i][3]=indy;
}

void move(int n, int tab[][5], int nbp, int i){
	//i = indice de la personne
	//moving variables
	int difx = tab[i][2] - tab [i][0];       //but - position
	int depx = tab[i][0];
	int dify = tab[i][3] - tab[i][1];        //but - position
	int depy = tab[i][1];
	int dep;
	int k=0;
	///////////////////////////
	//but a gauche
	if (difx < 0){
		if (abs(difx) <= (n/2)){
			depx = tab[i][0]-1;	
			}
		else {
			depx = tab[i][0]+1;	
			}
		}
	
		//but a droite
	if (difx > 0){
		if (abs(difx) <= (n/2)){
			depx = tab[i][0]+1;
			}
		else {
			depx = tab[i][0]-1;	
			}
		}
			
	//but en haut
	if(dify < 0){
		if(abs(dify) <= (n/2)){
			depy = tab[i][1] - 1;
			}
		else{
			depy = tab[i][1] + 1;			
		}
	}
		
	//but en bas
	if(dify > 0){
		if(abs(dify) <= (n/2)){
			depy = tab[i][1] + 1;
			}
		else{
			depy = tab[i][1] - 1;
		}
	}
	//printf("pers%d va en (%d,%d)\n",i, depx, depy);

	//test si case libre
	if (!libre(tab,nbp,depx,depy)){
		//printf("*%d*",libre(tab,nbp,depx,depy));
		tab[i][0] =depx;
		tab[i][1] =depy;
		dep=1;
		}
	else if (!libre(tab,nbp,depx,tab[i][1])){
		//printf("*%d*",libre(tab,nbp,depx,tab[i][1]));
		tab[i][0] =depx;
		dep=1;
		}	
	else if (!libre(tab,nbp,tab[i][0],depy)){
		//printf("*%d*",libre(tab,nbp,tab[i][0],depy));
		tab[i][1] =depy;
		dep=1;
		}
	if(tab[i][0] == -1 || tab[i][0] == n){
		(tab[i][0] == -1 )? (tab[i][0] = (n-1)) : (tab[i][0] = 0);
		}
	if(tab[i][1] == -1 || tab[i][1] == n){
		(tab[i][1] == -1 )? (tab[i][1] = (n-1)) : (tab[i][1] = 0);
		}

		//but atteint
	if (tab[i][0] == tab[i][2] && tab[i][3] == tab[i][1]){
		nouvBut(n,tab,i);
		printf("nouv but pers %d (%d,%d)\n", i+1, tab[i][2], tab[i][3]);
		dep=1;
		}
			
	//si elle peut pas aller vers l'objectif
	while(dep != 1){
		switch(k){
			case 0:
				if(!libre(tab,nbp,tab[i][0]-1,tab[i][1]-1)){
					tab[i][0]--;
					tab[i][1]--;
					dep=1;
					break;
					}
			case 1:
				if(!libre(tab,nbp,tab[i][0],tab[i][1]-1)){
					tab[i][1]--;
					dep=1;
					break;
					}
			case 2:
				if(!libre(tab,nbp,tab[i][0]+1,tab[i][1]-1)){
					tab[i][0]++;
					tab[i][1]--;
					dep=1;
					break;
					}
			case 3:
				if(!libre(tab,nbp,tab[i][0]-1,tab[i][1])){
					tab[i][0]--;
					dep=1;
					break;
					}
			case 4:
				if(!libre(tab,nbp,tab[i][0]+1,tab[i][1])){
					tab[i][0]++;
					dep=1;
					break;
					}
			case 5:
				if(!libre(tab,nbp,tab[i][0]-1,tab[i][1]+1)){
					tab[i][0]--;
					tab[i][1]++;
					dep=1;
					break;
					}
			case 6:
				if(!libre(tab,nbp,tab[i][0],tab[i][1]+1)){
					tab[i][1]++;
					dep=1;
					break;
					}
			case 7:
				if(!libre(tab,nbp,tab[i][0]+1,tab[i][1]+1)){
					tab[i][0]++;
					tab[i][1]++;
					dep=1;
					break;
					}
			case 8:
				dep=1;
				break;				
			}
		k++;
		}
	if(tab[i][0] == -1 || tab[i][0] == n){
		(tab[i][0] == -1 )? (tab[i][0] = (n-1)) : (tab[i][0] = 0);
		}
	if(tab[i][1] == -1 || tab[i][1] == n){
		(tab[i][1] == -1 )? (tab[i][1] = (n-1)) : (tab[i][1] = 0);
		}
	//printf("%d(%d,%d)\n",i,tab[i][0],tab[i][1]);
}

void contamine(int tab[][5], int i, int nbp){
	//2=contamine 1=normal 4=vaccine 3=incubation
	int k=0;
	if (tab[i][4] == 2){
		while(k<8){
		switch(k){
			case 0:
				if(libre(tab,nbp,tab[i][0]-1,tab[i][1]-1)){
					if(tab[libre(tab,nbp,tab[i][0]-1,tab[i][1]-1)-1][4] == 1 )
					tab[libre(tab,nbp,tab[i][0]-1,tab[i][1]-1)-1][4] = 3;
					break;
					}
			case 1:
				if(libre(tab,nbp,tab[i][0],tab[i][1]-1)){
					if(tab[libre(tab,nbp,tab[i][0],tab[i][1]-1)-1][4] == 1 )
					tab[libre(tab,nbp,tab[i][0],tab[i][1]-1)-1][4] = 3;
					break;
					}
			case 2:
				if(libre(tab,nbp,tab[i][0]+1,tab[i][1]-1)){
					if(tab[libre(tab,nbp,tab[i][0]+1,tab[i][1]-1)-1][4] == 1 )
					tab[libre(tab,nbp,tab[i][0]+1,tab[i][1]-1)-1][4] = 3;
					break;
					}
			case 3:
				if(libre(tab,nbp,tab[i][0]-1,tab[i][1])){
					if(tab[libre(tab,nbp,tab[i][0]-1,tab[i][1])-1][4] == 1 )
					tab[libre(tab,nbp,tab[i][0]-1,tab[i][1])-1][4] = 3;
					break;
					}
			case 4:
				if(libre(tab,nbp,tab[i][0]+1,tab[i][1])){
					if(tab[libre(tab,nbp,tab[i][0]+1,tab[i][1])-1][4] == 1 )
					tab[libre(tab,nbp,tab[i][0]+1,tab[i][1])-1][4] = 3;
					break;
					}
			case 5:
				if(libre(tab,nbp,tab[i][0]-1,tab[i][1]+1)){
					if(tab[libre(tab,nbp,tab[i][0]-1,tab[i][1]+1)-1][4] == 1 )
					tab[libre(tab,nbp,tab[i][0]-1,tab[i][1]+1)-1][4] = 3;
					break;
					}
			case 6:
				if(libre(tab,nbp,tab[i][0],tab[i][1]+1)){
					if(tab[libre(tab,nbp,tab[i][0],tab[i][1]+1)-1][4] == 1 )
					tab[libre(tab,nbp,tab[i][0],tab[i][1]+1)-1][4] = 3;
					break;
					}
			case 7:
				if(libre(tab,nbp,tab[i][0]+1,tab[i][1]+1)){
					if(tab[libre(tab,nbp,tab[i][0]+1,tab[i][1]+1)-1][4] == 1 )
					tab[libre(tab,nbp,tab[i][0]+1,tab[i][1]+1)-1][4] = 3;
					break;
					}
		}
		k++;
		}
	}

	if (tab[i][4] == 1){
		while(k<8){
		switch(k){
			case 0:
				if(libre(tab,nbp,tab[i][0]-1,tab[i][1]-1)){
					if(tab[libre(tab,nbp,tab[i][0]-1,tab[i][1]-1)-1][4] == 2 )
						tab[i][4] = 3;
					break;
					}
			case 1:
				if(libre(tab,nbp,tab[i][0],tab[i][1]-1)){
					if(tab[libre(tab,nbp,tab[i][0],tab[i][1]-1)-1][4] == 2 )
						tab[i][4] = 3;
					break;
					}
			case 2:
				if(libre(tab,nbp,tab[i][0]+1,tab[i][1]-1)){
					if(tab[libre(tab,nbp,tab[i][0]+1,tab[i][1]-1)-1][4] == 2 )
						tab[i][4] = 3;
					break;
					}
			case 3:
				if(libre(tab,nbp,tab[i][0]-1,tab[i][1])){
					if(tab[libre(tab,nbp,tab[i][0]-1,tab[i][1])-1][4] == 2 )
						tab[i][4] = 3;
					break;
					}
			case 4:
				if(libre(tab,nbp,tab[i][0]+1,tab[i][1])){
					if(tab[libre(tab,nbp,tab[i][0]+1,tab[i][1])-1][4] == 2 )
						tab[i][4] = 3;
					break;
					}
			case 5:
				if(libre(tab,nbp,tab[i][0]-1,tab[i][1]+1)){
					if(tab[libre(tab,nbp,tab[i][0]-1,tab[i][1]+1)-1][4] == 2 )
						tab[i][4] = 3;
					break;
					}
			case 6:
				if(libre(tab,nbp,tab[i][0],tab[i][1]+1)){
					if(tab[libre(tab,nbp,tab[i][0],tab[i][1]+1)-1][4] == 2 )
						tab[i][4] = 3;
					break;
					}
			case 7:
				if(libre(tab,nbp,tab[i][0]+1,tab[i][1]+1)){
					if(tab[libre(tab,nbp,tab[i][0]+1,tab[i][1]+1)-1][4] == 2 )
						tab[i][4] = 3;
					break;
					}
			}
			k++;
		}
		}
	
	//printf(" %d \n", libre(tab,nbp,tab[i][0]+1,tab[i][1]+1));
	}


int main(){
	//static int a permet de garder valeur (global) ?pour arret nb contaminés?
	int nbp=2;
	int pers[2][5]={{2,2,7,6,2},{3,2,4,3,1}/*,{3,9,2,1,1},{5,3,7,7,1}*/};
	int world = 10;
	int i=0;
	int tab[1][5]={{2,2,7,6,2}};
	int j;
	while (i<20){
		grille(pers, world, nbp);
		for (j=0; j<nbp; j++){
			move(world, pers, nbp, j);
			//contamine(pers, j, nbp);
		}
		for (j=0; j<nbp; j++){
			if (pers[j][4] == 3){
				pers[j][4] =2;
				}
			}
		
		//printf("%d\n", rand()%world);
		//printf("%d %d\n",tab[0][2], tab[0][3]);
		nouvBut( world, tab, 0);
		i++;
	}
}
