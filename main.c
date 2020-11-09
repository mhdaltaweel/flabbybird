#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_fichiers.h"
#include "test.h"
#include "fonctions_SDL.h"


int main(int argc, char *argv[]){
    //test(); // ex2
    // exo 3 
    int n=0;
	int m=0;
    taille_fichier("pentomino.txt",&n,&m);
    char** tab1 = lire_fichier("pentomino.txt");
    afficher_tab_2D(tab1,n,m);
    //desallouer_tab_2D(tab1, n);
/***********************************************************/
    SDL_Window* fenetre; // Déclaration de la fenêtre
    SDL_Event evenements; // Événements liés à la fenêtre
    bool terminer = false;
    

    if(SDL_Init(SDL_INIT_VIDEO) < 0){ // Initialisation de la SDL
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // Créer la fenêtre
    fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, 600,600, SDL_WINDOW_RESIZABLE);
    if(fenetre == NULL){ // En cas d’erreur
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    /* newwwwwwwwwwwww*/
    
    SDL_Renderer* ecran; //new
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED); //new
    SDL_Texture* fond = charger_image( "background.bmp", ecran );
    

    SDL_Texture* pieces = charger_image("redsqr2.bmp", ecran);
	
    int objetW;
	int objetH;
	SDL_QueryTexture( pieces , NULL , NULL , &objetW ,&objetH );

    SDL_Rect SrcR_sprite[1];
	int k=0;
	for(int j=0; j<1; j++){
		for(int i=0;i<1;i++){
            SrcR_sprite[k].x=i*32;
            SrcR_sprite[k].y=j*32;
            SrcR_sprite[k].w=objetW/7;
            SrcR_sprite[k].h=objetH/7;
            k++;
		}
	}
	
	SDL_Rect DestR_sprite[n*m];
	k=0;
	for(int j=0; j<n; j++){
		for(int i=0;i<m;i++){
            DestR_sprite[k].x=i*13;
            DestR_sprite[k].y=j*13;
            DestR_sprite[k].w=objetW/7;
            DestR_sprite[k].h=objetH/7;
            k++;
		}
	}

    //Boucle principale
    while(!terminer){
        SDL_PollEvent( &evenements );
        switch(evenements.type){
            case SDL_QUIT:
                terminer = true; 
                break;
            case SDL_KEYDOWN:
            switch(evenements.key.keysym.sym){
                case SDLK_ESCAPE:
                case SDLK_q:
                terminer = true; 
                break;
            }
        }
        SDL_RenderClear(ecran);
		SDL_RenderCopy(ecran, fond, NULL, NULL);

        //SDL_RenderCopy(ecran, pieces, &SrcR, &DestR);
		k=0;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){	
				if(tab1[i][j] == '#' ){
				    SDL_RenderCopy(ecran, pieces, NULL, &DestR_sprite[k]);
                }
				k++;

			}
		}
	
		
		SDL_RenderPresent(ecran);

    }
    // Quitter SDL
    SDL_DestroyRenderer(ecran);
    //SDL_DestroyRenderer(sprite);
    SDL_DestroyWindow(fenetre);
   
    SDL_Quit();

    return 0;
   
}



