#ifndef FONCTIONS_SDL_H
#define FONCTIONS_SDL_H

SDL_Texture* charger_image(const char* nomfichier, SDL_Renderer*renderer);

SDL_Texture* charger_image_transparente(const char* nomfichier,SDL_Renderer* renderer,Uint8 r, Uint8 g, Uint8 b) ;

#endif