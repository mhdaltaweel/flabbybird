#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rcs/fonctions_fichiers.h"
#include "rcs/fonctions_SDL.h"
#include <math.h>
#include "rcs/sdl2-ttf-light.h"
#include <unistd.h>

#define NB_PIECES 12
#define BORD_PLAT_X1 170
#define BORD_PLAT_X2 309
#define BORD_PLAT_Y1 170
#define BORD_PLAT_Y2 253

void apply_texture(SDL_Texture *texture,SDL_Renderer *renderer,int x, int y){
    SDL_Rect dst = {0, 0, 0, 0};
    
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    dst.x = x; dst.y=y;
    
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    
}

int main(int argc, char *argv[]){
    int n=0;
	int m=0;
    taille_fichier("pentomino.txt",&n,&m);
    char** tab1 = lire_fichier("pentomino.txt");
    afficher_tab_2D(tab1,n,m);
    
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
    fenetre = SDL_CreateWindow("pentomino", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, 600,600, SDL_WINDOW_RESIZABLE);
    if(fenetre == NULL){ // En cas d’erreur
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    
    init_ttf();
    SDL_Renderer* ecran;
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED); 
    SDL_Texture* fond = charger_image( "image/background.bmp", ecran );
    SDL_Texture* plateau = charger_image("image/fond.bmp", ecran);

    SDL_Texture* pieces1 = charger_image("image/bleu.bmp", ecran);
    SDL_Texture* pieces2 = charger_image("image/rouge.bmp", ecran);
    SDL_Texture* pieces3 = charger_image("image/vert.bmp", ecran);
    SDL_Texture* pieces4 = charger_image("image/jaune.bmp", ecran);
    SDL_Texture* pieces5 = charger_image("image/violet.bmp", ecran);
    SDL_Texture* pieces6 = charger_image("image/rose.bmp", ecran);
    
    SDL_Texture* menu = charger_image("image/menu.bmp", ecran);
    SDL_Texture* jouerMenu = charger_image("image/jouer.bmp", ecran);
    SDL_Texture* jouerMenuClique = charger_image("image/jouer_clique.bmp", ecran);
    
    TTF_Font* font = load_font("arial.ttf",14);
    
    int plateauRempli[60];
    
    SDL_Rect SrcR_plateau[1];
    SrcR_plateau[0].x = 25;
    SrcR_plateau[0].y = 25;
    SrcR_plateau[0].w = 25;
    SrcR_plateau[0].h = 25;

    SDL_Rect* DestR_plateau1;
    DestR_plateau1=malloc((n*m)*sizeof(SDL_Rect));
    int k = 0;
    for(int j = 0 ; j < 6 ; j++ ){
        for(int i = 0 ; i < 10 ; i++){
            DestR_plateau1[k].x = 170 + i*14 ;
            DestR_plateau1[k].y = 170 + j*14 ;
            DestR_plateau1[k].w = 13 ;
            DestR_plateau1[k].h = 13 ;
            k++;
        }
    }
    
    int p1W;
	int p1H;
	
	int p2W;
	int p2H;
	
	int p3W;
	int p3H;
	
	int p4W;
	int p4H;
	
	int p5W;
	int p5H;
	
	int p6W;
	int p6H;
	
	SDL_QueryTexture( pieces1 , NULL , NULL , &p1W ,&p1H );
	SDL_QueryTexture( pieces2 , NULL , NULL , &p2W ,&p2H );
	SDL_QueryTexture( pieces3 , NULL , NULL , &p3W ,&p3H );
	SDL_QueryTexture( pieces4 , NULL , NULL , &p4W ,&p4H );
	SDL_QueryTexture( pieces5 , NULL , NULL , &p5W ,&p5H );
	SDL_QueryTexture( pieces6 , NULL , NULL , &p6W ,&p6H );

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
	
	SDL_Rect* DestR_sprite;
	DestR_sprite=malloc((n*m)*sizeof(SDL_Rect));
	k=0;
	for(int j=0; j<n; j++){
		for(int i=0;i<m;i++){
            DestR_sprite[k].x=i*14;
            DestR_sprite[k].y=j*14;
            DestR_sprite[k].w=p1W/7;
            DestR_sprite[k].h=p1H/7;
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
	bool pieceInside;
	bool sec=true;
	int pieceClique=-1;
	
	int etat=1;
	
	int depart=1;
	
	int temps = 0;
	int secondes=0;
	int minutes=0;
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
			case SDL_KEYUP:
				if((event.key.state==SDL_RELEASED)&&(rota)){
					rota=false;
				}
				break;
			case SDL_KEYDOWN: // rotation
				if(keystate[SDL_SCANCODE_ESCAPE]){
					terminer=true;
				}
				if(keystate[SDL_SCANCODE_SPACE]){
					rota=true;
					if(rota){
						for(int i=0;i<12;i++){
							for(int j=0;j<5;j++){ 
								if((sourisX>=tableau[i].tab[j].x)&&(sourisX<=tableau[i].tab[j].x+tableau[i].tab[j].w)&&(sourisY>=tableau[i].tab[j].y)&&(sourisY<=tableau[i].tab[j].y+tableau[i].tab[j].h)){		
									for(int t = 0 ; t < 5 ; t++ ){
										int xr = tableau[i].tab[t].x - tableau[i].tab[2].x ;
										int yr = tableau[i].tab[t].y - tableau[i].tab[2].y ;
										tableau[i].tab[t].x = tableau[i].tab[2].x - yr;
										tableau[i].tab[t].y = tableau[i].tab[2].y + xr;
									}
								}	
							}
						}
					}
				}
				break;
			case SDL_MOUSEMOTION:
				sourisX=event.motion.x;
				sourisY=event.motion.y;
				if(sourisX>=200 && sourisX<=400 && sourisY>=200 && sourisY<=260 && depart<3){
					depart=2;
				}else if(depart<3){
					depart=1;
				}	
				if(event.button.button == SDL_BUTTON_LEFT){
					for(int i=0;i<12;i++){
						for(int j=0;j<5;j++){ 
							if((event.motion.x>=tableau[i].tab[j].x)&&(event.motion.x<=tableau[i].tab[j].x+tableau[i].tab[j].w)&&(event.motion.y>=tableau[i].tab[j].y)&&(event.motion.y<=tableau[i].tab[j].y+tableau[i].tab[j].h)){
								if(pieceClique<0){
									pieceClique=i;
								}
								for(int k=0;k<5;k++){	
									tableau[pieceClique].tab[k].x=event.motion.x+tableau[pieceClique].tab[k].x-tableau[pieceClique].tab[4].x-tableau[pieceClique].tab[j].w*0.5;
									tableau[pieceClique].tab[k].y=event.motion.y+tableau[pieceClique].tab[k].y-tableau[pieceClique].tab[4].y-tableau[pieceClique].tab[j].h*0.5;
								}
							}
						}
					}
				
			break;
			case SDL_MOUSEBUTTONUP:
				pieceClique=-1;
				pieceInside=false;
				if(sourisX>=200 && sourisX<=400 && sourisY>=200 && sourisY<=260 && depart<3){
					depart=3;
				}
				if(event.button.button == SDL_BUTTON_LEFT){
					for(int i = 0 ; i < 12 ; i++){
						for(int j = 0 ; j < 5 ; j++){
							for(int l = 0 ; l < 60 ; l++){
								k = 0;
								pieceInside = false;
								if((tableau[i].tab[j].x >= DestR_plateau1[l].x &&  tableau[i].tab[j].x <= 130 + DestR_plateau1[l].x) && (tableau[i].tab[j].y >= DestR_plateau1[l].y &&  tableau[i].tab[j].y <= 78 + DestR_plateau1[l].y)){
									int k = 0 ;
									while( tableau[i].tab[k].x  >= BORD_PLAT_X1  && tableau[i].tab[k].x <= BORD_PLAT_X2 && tableau[i].tab[k].y>= BORD_PLAT_Y1 && tableau[i].tab[k].y<= BORD_PLAT_Y2 ){
										if( k == 4 ){
											pieceInside = true;
										}
										k++;
										if(tableau[i].tab[j].x - DestR_plateau1[l].x <= 13 && tableau[i].tab[j].y - DestR_plateau1[l].y <= 13 && pieceInside){
											tableau[i].tab[j].x = DestR_plateau1[l].x;
											tableau[i].tab[j].y = DestR_plateau1[l].y;
											
										}
									}
								}
							}
						}
					}
				}
			}
			break;
        }// end switche

        SDL_RenderClear(ecran);
		SDL_RenderCopy(ecran, fond, NULL, NULL);
		
		if(etat<=1){
			k = 0;
        	for(int i = 0 ; i < 6 ; i++){
         		for(int j = 0 ; j < 10 ; j++){
           			if(tab1[i][j] == '#'){
             	    	SDL_RenderCopy(ecran, plateau, NULL , &DestR_plateau1[k]);
               		}
               		k++;
            	}
        	}
		}
		k=0; 
		for(int i=0;i<12;i++){
			for(int j=0;j<5;j++){
				if(i==0 || i==5){
					SDL_RenderCopy(ecran, pieces1, NULL, &(tableau[i].tab[j]));
				}else if(i==1 || i==6 || i==11){
					SDL_RenderCopy(ecran, pieces2, NULL, &(tableau[i].tab[j]));
				}else if(i==2 || i==7){
					SDL_RenderCopy(ecran, pieces3, NULL, &(tableau[i].tab[j]));
				}else if(i==3 || i==8){
					SDL_RenderCopy(ecran, pieces4, NULL, &(tableau[i].tab[j]));
				}else if(i==4 || i==9){
					SDL_RenderCopy(ecran, pieces5, NULL, &(tableau[i].tab[j]));
				}else if(i==5 || i==10){
					SDL_RenderCopy(ecran, pieces6, NULL, &(tableau[i].tab[j]));
				}
			} 
		}
		if(etat!=2){
			etat=1;
		}
		for(int l=0;l<60;l++){
			for(int i=0;i<12;i++){
				for(int j=0;j<5;j++){
					if(DestR_plateau1[l].x==tableau[i].tab[j].x && DestR_plateau1[l].y==tableau[i].tab[j].y){
						plateauRempli[l]=1;
					}
				}
			}
			if(plateauRempli[l]!=1){
				etat=-1;
			}
		}
		 
		if(etat==1){
			etat=2;
		}
		if(depart==1){
			temps=SDL_GetTicks();
			apply_texture(menu, ecran, 0, 0);
			apply_texture(jouerMenu, ecran, 200, 200);
		}else if(depart==2){
			temps=SDL_GetTicks();
			apply_texture(menu, ecran, 0, 0);
			apply_texture(jouerMenuClique, ecran, 200, 200);
		}else{
			if(etat!=2){
				int tempsPresent=SDL_GetTicks()-temps;
				secondes=(tempsPresent/1000)%60; 
				if(secondes==59 && sec){
					printf("%d \n",secondes);
					secondes=0;
					minutes++;
					sec=false;
				}else if(secondes!=59){
					sec=true;
				}
			}else{
				apply_text(ecran, 150,340, 200, 40,"MISSION ACCOMPLIE",font);
			}
			char chaine[25];
			snprintf(chaine, sizeof chaine,"Temps : %d min %d sec",minutes,secondes);
			apply_text(ecran, 200,50, 200, 40,chaine,font);	
		}
		SDL_RenderPresent(ecran);
    }
    free(DestR_plateau1);
    free(DestR_sprite);

    // Quitter SDL
	SDL_DestroyTexture(pieces1);
	SDL_DestroyTexture(pieces2);
	SDL_DestroyTexture(pieces3);
	SDL_DestroyTexture(pieces4);
	SDL_DestroyTexture(pieces5);
	SDL_DestroyTexture(pieces6);
	SDL_DestroyTexture(fond);
	SDL_DestroyTexture(plateau);
	SDL_DestroyTexture(menu);
	SDL_DestroyTexture(jouerMenu);
	SDL_DestroyTexture(jouerMenuClique);
	
	TTF_CloseFont(font);
	
    SDL_DestroyRenderer(ecran);
    SDL_DestroyWindow(fenetre);
    desallouer_tab_2D(tab1, n);
    SDL_Quit();

    return 0;
   
}



