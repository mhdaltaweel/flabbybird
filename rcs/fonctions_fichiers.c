#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions_fichiers.h"
#include <SDL2/SDL.h>
#include "fonctions_SDL.h"

char** allouer_tab_2D(int n, int m){
	char ** tab;
	tab = (char **) malloc (n*sizeof(char*));
	for(int i=0; i<n; i++){
		tab[i]=(char *)malloc(m* sizeof(char));
    }
	for (int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			tab[i][j]=' ';
        }
    }
	return tab;
}
/***************************************************************************/

void desallouer_tab_2D(char** tab, int n){

    for (int i = 0 ; i < n ; i++){
        free(tab[i]);
    } 
    free(tab);
}

/***************************************************************************/

void afficher_tab_2D(char** tab, int n, int m){

    int i , j ;

    for(i = 0 ; i < n ; i++){
        for(j = 0 ; j < m ; j++){
            printf("%c" , tab[i][j]);
        }
        printf("\n");
    }
}

/***************************************************************************/

/******************** meeee ********************** */
// void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol){
//     FILE* pFile;
//     int c ;
//     int  max ; 
//     *nbLig = 0;
//     *nbCol = 0;
//     max = 0;
//     pFile =fopen(nomFichier , "r");
//     if(pFile == NULL){
//         printf(" ficher introuvable\n ");
//     }else{
//         c = getc(pFile);
//         while ( c != EOF ){
//             if(c != '\r' && c != '\n')
//             *nbCol = *nbCol + 1;
//             if (c=='\n'){
//                 *nbLig = *nbLig + 1;
//                 max = *nbCol ;
//                 *nbCol = 0;
//             }
//             if(*nbCol > max){
//                max = *nbCol  ;
//             }
//         }
        
//     }
// }

    /*   ****************       version arthur     **************** */
// void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol){
//     FILE *file = NULL;
//     file = fopen(nomFichier , "r");
//     int charac = 0;
//     int maxCol = 0;
//     *nbCol = 0 ;
//     if(file != NULL){
//         do{
//             charac = getc(file);
//             *nbCol +=1;
//             if(*nbCol > maxCol){
//                 maxCol = *nbCol;
//             }
//                 if(charac == '\n'){
//                     *nbLig +=1;
//                     *nbCol = 0;
//                 }
//         }while(charac != EOF);
//         *nbCol = maxCol;
//         fclose(file);
//     }
// }

void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol){
	
    FILE* file = NULL;
    file = fopen(nomFichier,"r");
    int charac = 0;
    int maxCol=0;
    *nbCol = 0;
    if(file != NULL){
        do {
            charac = getc(file);
            if (charac != '\n' && charac != '\r') 
            	*nbCol += 1;
		    if (*nbCol>maxCol){
				maxCol=*nbCol;
			}
            if (charac == '\n') {
                *nbLig += 1;
		 *nbCol=0;
            }
        }while (charac != EOF);
		*nbCol=maxCol;
        fclose(file);
    }
}


/***************************************************************************/


// char** lire_fichier(const char* nomFichier){
//     FILE* fichier = fopen(nomFichier, "r");
//     if (fichier == NULL){
//         printf("Impossible d'ouvrir le fichier text : %s",nomFichier);
//     }else {

//         int nbLig,nbCol;
//         taille_fichier(nomFichier,&nbLig,&nbCol);
//         int maxchar = nbLig * nbCol;

//         char ch[maxchar];
//         char** tab = allouer_tab_2D(nbLig,nbCol);

//         int i = 0;
//         while (fgets(ch, maxchar, fichier) != NULL){
//             for(int j = 0; j< nbCol ; j++){
//                 tab[i][j] = ch[j];
//             }
//             i++;
//         }
//     fclose(fichier);
//     return tab;
//     }
// } 

char** lire_fichier(const char* nomFichier){
	FILE* fichier = fopen(nomFichier,"r");
	if(fichier==NULL){
		printf("Error opening file");
		return 0;
	}
	else{
		int nbLig=0,nbCol=0;
		taille_fichier(nomFichier,&nbLig,&nbCol);
		int maxChar = nbLig * nbCol;
		char* ch;
		ch=malloc(maxChar*sizeof(char));
		char** tab = allouer_tab_2D(nbLig,nbCol);
		int i = 0;
		while(fgets(ch, maxChar, fichier) != NULL){
			int n = strlen(ch);
			for(int j=0; j<n; j++){
				if(ch[j]!='\n' && ch[j]!='\r')
					tab[i][j] = ch[j];
			}
			i++;
		}
		free(ch);
		fclose(fichier);
		return tab;
	}
}



/***************************************************************************/

char** modifier_caractere(char** tab, int n, int m, char ancien, char
nouveau){
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            if(tab[i][j] == ancien){
                tab[i][j] = nouveau;
            }
        }
    }
    return tab ;
}


void ecrire_fichier(const char* nomFichier, char** tab, int n, int m){
    FILE* fichier = fopen(nomFichier,"w");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            fputc(tab[i][j],fichier);
        }
        fputs("\n",fichier);
    }
    fclose(fichier);
}

/*void trier_tab(piece_t *p){
	int tmp;
	for(int i=0;i<12;i++){
		for(int j=0;j<(12-i);j++){
			if(p.tab[j].y==p.tab[j+1].y && p.tab[j].x>p.tab[j+1].x){
				tmp=p.tab[j];
				p.tab[j]=p.tab[j+1];
				p.tab[j+1]=tmp;
			}else if(p.tab[j].y>p.tab[j+1].y){
				tmp=p.tab[j];
				p.tab[j]=p.tab[j+1];
				p.tab[j+1]=tmp;
			}
		}
	}
}*/

/*
void liaisonSprite(SDL_Rect* Destr, char** tab, int m, int k,SDL_Renderer* renderer, SDL_Texture* texture, int x, int y){
	int j, i; 
	i = k % m;
	j = k/4;
	if(tab[i+1][j]=='#'){
		Destr[k+1].x=x+Destr[k+1].w;
		Destr[k+1].y=y+Destr[k+1].h;
		SDL_RenderCopy(renderer, texture, NULL, &Destr[k+1]);
		liaisonSprite(Destr, tab, m, k+1,renderer, texture, x,y);
	}
	if(tab[i-1][j]=='#'){
		Destr[k-1].x=x-Destr[k-1].w;
		Destr[k-1].y=y-Destr[k-1].h;
		SDL_RenderCopy(renderer, texture, NULL, &Destr[k-1]);
		liaisonSprite(Destr, tab, m, k-1,renderer, texture,x,y);
	}
	if(tab[i][j+1]=='#'){
		Destr[k+m].x=x+Destr[k+m].w;
		Destr[k+m].y=y+Destr[k+m].h;
		SDL_RenderCopy(renderer, texture, NULL, &Destr[k+m]);
		liaisonSprite(Destr, tab, m, k+m,renderer, texture,x,y);
	}
	if(tab[i][j-1]=='#'){
		Destr[k-m].x=x-Destr[k-m].w;
		Destr[k-m].y=y-Destr[k-m].h;
		SDL_RenderCopy(renderer, texture, NULL, &Destr[k-m]);
		liaisonSprite(Destr, tab, m, k-m,renderer, texture,x,y);
	}
}*/




