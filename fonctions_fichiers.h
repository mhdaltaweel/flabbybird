#ifndef FONCTIONS_FICHERS
#define FONCTIONS_FICHERS
#include <SDL2/SDL.h>
#include "fonctions_SDL.h"

struct piece_s {
	
};

char** allouer_tab_2D(int n, int m);

void desallouer_tab_2D(char** tab, int n);

void afficher_tab_2D(char** tab, int n, int m);

void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);

char** lire_fichier(const char* nomFichier);

char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau);

void ecrire_fichier(const char* nomFichier, char** tab, int n, int m);

//void liaisonSprite(SDL_Rect* Destr, char** tab, int m, int k, SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);

#endif
