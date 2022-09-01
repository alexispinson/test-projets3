#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

void affichage(SDL_Surface *image_surface_origine,SDL_Renderer *renderer,SDL_Texture *image_texture_origine,
SDL_Surface *image_surface, SDL_Texture *image_texture){
    int quit = 0;
	    while(quit ==0){
		    SDL_Event windowEvent;
		    while(SDL_PollEvent(&windowEvent)){
			    if(windowEvent.type == SDL_QUIT){
			    quit = 1;
			    break;
			    }
		    }
		    SDL_Rect image_rect_origine = {100,10,image_surface_origine->w/4,image_surface_origine->h/4};
		    SDL_RenderCopy(renderer,image_texture_origine,NULL,&image_rect_origine);

		    SDL_Rect image_rect = {100,20+image_surface_origine->h/4,image_surface_origine->w/4,image_surface->h/4}; //ici pour modifier l'affichage de l'image
		    SDL_RenderCopy(renderer,image_texture,NULL,&image_rect);
		    SDL_RenderPresent(renderer);
        }
}

Uint32 obtenirPixel(SDL_Surface *surface, int x,int y){
	int nbOctetsParPixel = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;
	
	switch(nbOctetsParPixel){
		case 1 :
			return *p;
		case 2:
			return *(Uint16 *)p;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN){
				return p[0] << 16 | p[1] << 8 | p[2];
			}
			else{
				return p[0] | p[1] << 8 | p[2] << 16;
			}
		case 4 :
			return *(Uint32 *)p;
			
		default:
			return 0;
	}
}

void definirPixel(SDL_Surface *surface, int x,int y, Uint32 pixel){
	int nbOctetsParPixel = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;
	
	switch(nbOctetsParPixel){
		case 1:
			*p = pixel;
			break;
		case 2 :
			*(Uint16 *)p=pixel;
		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN){
				p[0]=(pixel >> 16) & 0xff;
				p[1]=(pixel >> 8) & 0xff;
				p[2]=pixel & 0xff;
			}
			else{
				p[2]=(pixel >> 16) & 0xff;
				p[1]=(pixel >> 8) & 0xff;
				p[0]=pixel & 0xff;
			}
		case 4:
			*(Uint32 *)p = pixel;
			break;
	}
}