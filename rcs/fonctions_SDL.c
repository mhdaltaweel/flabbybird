#include <SDL2/SDL.h>
#include "fonctions_SDL.h"

SDL_Texture* charger_image(const char* cheminFichier, SDL_Renderer* renderer){

  SDL_Surface* surface =  SDL_LoadBMP(cheminFichier);
  SDL_Texture* image = SDL_CreateTextureFromSurface(renderer, surface);
  
  return image;

}

SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b){
  SDL_Surface* surface =  SDL_LoadBMP(nomfichier);
  

  Uint32 couleur = SDL_MapRGB(surface->format, r, g, b);
  SDL_SetColorKey(surface, SDL_TRUE , couleur) ;

  SDL_Texture* image = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  return image;
}