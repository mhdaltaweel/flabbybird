#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_fichiers.h"
#include "fonctions_SDL.h"
#include <math.h>
/*
void trierTab(piece_s piece){
	for(int i=0;i<5;i++){
		if
	}
}*/

int main(int argc, char *argv[]){
    int n=0;
	int m=0;
    taille_fichier("pentomino.txt",&n,&m);
    char** tab1 = lire_fichier("pentomino.txt");
    afficher_tab_2D(tab1,n,m);
    //desallouer_tab_2D(tab1, n);
/***********************************************************/
    SDL_Window* fenetre; // Déclaration de la fenêtre
    SDL_Event event; // Événements liés à la fenêtre
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
    SDL_Texture* plateau = charger_image("fond.bmp", ecran);

    SDL_Texture* pieces = charger_image("redsqr2.bmp", ecran);
    
    SDL_Rect SrcR_plateau[1];
    SrcR_plateau[0].x = 25;
    SrcR_plateau[0].y = 25;
    SrcR_plateau[0].w = 25;
    SrcR_plateau[0].h = 25;

    SDL_Rect DestR_plateau[n*m];
    int k = 0;
    for(int j = 0 ; j < 8 ; j++ ){
        for(int i = 0 ; i < 11 ; i++){
            DestR_plateau[k].x = 170 + i*14 ;
            DestR_plateau[k].y = 170 + j*14 ;
            DestR_plateau[k].w = 13 ;
            DestR_plateau[k].h = 13 ;
            k++;
        }
    }
	
    int objetW;
	int objetH;
	SDL_QueryTexture( pieces , NULL , NULL , &objetW ,&objetH );

    SDL_Rect SrcR_sprite[7];
	k=0;
	for(int j=0; j<7; j++){
		for(int i=0;i<7;i++){
            SrcR_sprite[k].x=i*14;
            SrcR_sprite[k].y=j*14;
            SrcR_sprite[k].w=14;
            SrcR_sprite[k].h=14;
            k++;
		}
	}
	
	SDL_Rect DestR_sprite[n*m];
	k=0;
	for(int j=0; j<n; j++){
		for(int i=0;i<m;i++){
            DestR_sprite[k].x=i*14;
            DestR_sprite[k].y=j*14;
            DestR_sprite[k].w=objetW/7;
            DestR_sprite[k].h=objetH/7;
            k++;
		}
	}

	struct piece_s {
		SDL_Rect tab[5];
	};
	
	typedef struct piece_s piece_t;
	
	piece_t tableau[12];
	int a=0;
	int t=0;	
	k=0;
	piece_t p;
	for(int i=7;i<n;i++){
		for(int j=0;j<m;j++){	
			if(tab1[i][j] == '#' ){
				p.tab[a]=DestR_sprite[k];
				a++;
				if(a>=5){
					tableau[t]=p;
					t++;
					a=0;
				}
          }
			k++;

		}
	}
	
	bool rota = false;
    //Boucle principale
    
    
    while(!terminer){
        SDL_PollEvent(&event);
		
		const Uint8* keystate = SDL_GetKeyboardState(NULL);
		
		double sourisX;
		double sourisY;
		
		
        switch(event.type){
        	
            case SDL_QUIT:
                terminer = true; 
                break;
            //case SDL_KEYDOWN:
          	/*case SDL_MOUSEBUTTONUP:
            	click=false;
			case SDL_MOUSEBUTTONDOWN:
				click=true;
			*/
			case SDL_KEYUP:
				if((event.key.state==SDL_RELEASED)&&(rota)){
					rota=false;
					
				}
				
				break;
			case SDL_KEYDOWN:
				if(keystate[SDL_SCANCODE_SPACE]){
					rota=true;
					
					if(rota){
						
					for(int i=0;i<12;i++){
						for(int j=0;j<5;j++){ 
						
									if((sourisX>=tableau[i].tab[j].x)&&(sourisX<=tableau[i].tab[j].x+tableau[i].tab[j].w)&&(sourisY>=tableau[i].tab[j].y)&&(sourisY<=tableau[i].tab[j].y+tableau[i].tab[j].h)){
						
								for(int t=0;t<5;t++){
									if((tableau[i].tab[t].x>=tableau[i].tab[2].x)&&(tableau[i].tab[t].y<=tableau[i].tab[2].y)&&(t!=2)){
										int nX=(tableau[i].tab[t].x-tableau[i].tab[2].x)/tableau[i].tab[t].w;
										
										int nY=(tableau[i].tab[2].y-tableau[i].tab[t].y)/tableau[i].tab[t].h; 
										
										tableau[i].tab[t].x=tableau[i].tab[2].x-tableau[i].tab[2].w*nY;
										tableau[i].tab[t].y=tableau[i].tab[2].y-tableau[i].tab[2].h*nX;
									}
									else if((tableau[i].tab[t].x<tableau[i].tab[2].x)&&(tableau[i].tab[t].y<=tableau[i].tab[2].y)&&(t!=2)){
										int nX=(tableau[i].tab[2].x-tableau[i].tab[t].x)/tableau[i].tab[t].w;
										int nY=(tableau[i].tab[2].y-tableau[i].tab[t].y)/tableau[i].tab[t].h; 
										
										tableau[i].tab[t].x=tableau[i].tab[2].x+tableau[i].tab[2].w*nY;
										tableau[i].tab[t].y=tableau[i].tab[2].y+tableau[i].tab[2].h*nX;
									}
									else if((tableau[i].tab[t].x<=tableau[i].tab[2].x)&&(tableau[i].tab[t].y>tableau[i].tab[2].y)&&(t!=2)){
										int nX=(tableau[i].tab[2].x-tableau[i].tab[t].x)/tableau[i].tab[t].w;
										int nY=(tableau[i].tab[t].y-tableau[i].tab[2].y)/tableau[i].tab[t].h; 
										
										tableau[i].tab[t].x=tableau[i].tab[2].x+tableau[i].tab[2].w*nY;
										tableau[i].tab[t].y=tableau[i].tab[2].y+tableau[i].tab[2].h*nX;
									}
									else if((tableau[i].tab[t].x>tableau[i].tab[2].x)&&(tableau[i].tab[t].y>=tableau[i].tab[2].y)&&(t!=2)){
										int nX=(tableau[i].tab[t].x-tableau[i].tab[2].x)/tableau[i].tab[t].w;
										int nY=(tableau[i].tab[t].y-tableau[i].tab[2].y)/tableau[i].tab[t].h; 
										
										tableau[i].tab[t].x=tableau[i].tab[2].x-tableau[i].tab[2].w*nY;
										tableau[i].tab[t].y=tableau[i].tab[2].y-tableau[i].tab[2].h*nX;
									}
									
									
								}
								
							}	
							
				}
				
				
				}
				}
				}
				break;
				
			
			
				
			/*case SDL_KEYDOWN:
				if(keystate[SDL_SCANCODE_SPACE]){
					rota=true;
					printf("keydown \n");
				}
				break;*/
			
			case SDL_MOUSEMOTION:
				sourisX=event.motion.x;
				sourisY=event.motion.y;
				if(event.button.button == SDL_BUTTON_LEFT){
					
				for(int i=0;i<12;i++){
					for(int j=0;j<5;j++){ 
									if((event.motion.x>=tableau[i].tab[j].x)&&(event.motion.x<=tableau[i].tab[j].x+tableau[i].tab[j].w)&&(event.motion.y>=tableau[i].tab[j].y)&&(event.motion.y<=tableau[i].tab[j].y+tableau[i].tab[j].h)){
								/*printf("tututututu \n");
								if(rota){
									printf("rnc \n");
								
								for(int t=0;t<5;t++){
									if((tableau[i].tab[t].x>=tableau[i].tab[2].x)&&(tableau[i].tab[t].y<tableau[i].tab[2].y)&&(t!=2)){
									printf("1 \n");
										int nX=tableau[i].tab[t].x-tableau[i].tab[2].x/tableau[i].tab[t].w;
										int nY=tableau[i].tab[2].y-tableau[i].tab[t].y/tableau[i].tab[t].h; 
										tableau[i].tab[t].x=tableau[i].tab[2].x-tableau[i].tab[2].w*nY;
										tableau[i].tab[t].y=tableau[i].tab[2].y-tableau[i].tab[2].h*nX;
									}
									if((tableau[i].tab[t].x<=tableau[i].tab[2].x)&&(tableau[i].tab[t].y<tableau[i].tab[2].y)&&(t!=2)){
									printf("2 \n");
										int nX=tableau[i].tab[2].x-tableau[i].tab[t].x/tableau[i].tab[t].w;
										int nY=tableau[i].tab[2].y-tableau[i].tab[t].y/tableau[i].tab[t].h; 
										tableau[i].tab[t].x=tableau[i].tab[2].x+tableau[i].tab[2].w*nY;
										tableau[i].tab[t].y=tableau[i].tab[2].y+tableau[i].tab[2].h*nX;
									}
									if((tableau[i].tab[t].x<=tableau[i].tab[2].x)&&(tableau[i].tab[t].y>tableau[i].tab[2].y)&&(t!=2)){
									printf("3 \n");
										int nX=tableau[i].tab[2].x-tableau[i].tab[t].x/tableau[i].tab[t].w;
										int nY=tableau[i].tab[t].y-tableau[i].tab[2].y/tableau[i].tab[t].h; 
										tableau[i].tab[t].x=tableau[i].tab[2].x+tableau[i].tab[2].w*nY;
										tableau[i].tab[t].y=tableau[i].tab[2].y+tableau[i].tab[t].h*nX;
									}
									if((tableau[i].tab[t].x>tableau[i].tab[2].x)&&(tableau[i].tab[t].y>=tableau[i].tab[2].y)&&(t!=2)){
									printf("4 \n");
										int nX=tableau[i].tab[t].x-tableau[i].tab[2].x/tableau[i].tab[t].w;
										int nY=tableau[i].tab[t].y-tableau[i].tab[2].y/tableau[i].tab[t].h; 
										tableau[i].tab[t].x=tableau[i].tab[2].x-tableau[i].tab[2].w*nY;
										tableau[i].tab[t].y=tableau[i].tab[2].y-tableau[i].tab[2].h*nX;
									}
								}
							}*/

							for(int k=0;k<5;k++){
							if(k<=j){	
								tableau[i].tab[k].x=event.motion.x+tableau[i].tab[k].x-tableau[i].tab[4].x-tableau[i].tab[j].w*0.5;
								tableau[i].tab[k].y=event.motion.y+tableau[i].tab[k].y-tableau[i].tab[4].y-tableau[i].tab[j].h*0.5;
								}else{
									tableau[i].tab[k].x=event.motion.x+tableau[i].tab[k].x-tableau[i].tab[4].x-tableau[i].tab[j].w*0.5;
									tableau[i].tab[k].y=event.motion.y+tableau[i].tab[k].y-tableau[i].tab[4].y-tableau[i].tab[j].h*0.5;
								}
							}
				
				
				}
	}
}}




				break;
            switch(event.key.keysym.sym){
                case SDLK_ESCAPE:
                case SDLK_q:
                terminer = true; 
                break;
            }
        }
        SDL_RenderClear(ecran);
		SDL_RenderCopy(ecran, fond, NULL, NULL);
		
		k = 0;
        for(int i = 0 ; i < 7 ; i++){
            for(int j = 0 ; j < 11 ; j++){
                if(tab1[i][j] == '#'){
                    SDL_RenderCopy(ecran, plateau, NULL , &DestR_plateau[k]);
                }
                k++;
            }
        }
        //SDL_RenderCopy(ecran, pieces, &SrcR, &DestR);
		k=0;
		for(int i=0;i<12;i++){
			for(int j=0;j<5;j++){
				SDL_RenderCopy(ecran, pieces, &SrcR_sprite[i], &(tableau[i].tab[j]));
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



