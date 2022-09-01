#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "utile.c"

char image[] = "image1.jpeg";

int main(int argc, char *argv[]){

	//verif des importations
	if(SDL_Init(SDL_INIT_VIDEO))
	{
		printf("probleme video");
	}
	int flags = IMG_INIT_JPG;
	int initted = IMG_Init(flags);
	if((initted & flags) != flags){
		printf("probleme charge biblio image");
	}
	SDL_Window* window = SDL_CreateWindow("Window",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,0);
	if (!window){
		printf("Error creation de la fenetre");
		return 2;
	}


	SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	SDL_Surface *image_surface = NULL;
	image_surface = IMG_Load(image); 

	if(image_surface == NULL){
		printf("peut pas trouver image");
		SDL_Quit();
	}

	///pour l'original;
	SDL_Surface *image_surface_origine = NULL;
	image_surface_origine = IMG_Load(image);
	SDL_Texture *image_texture_origine = SDL_CreateTextureFromSurface(renderer,image_surface_origine);
	

	//changement de la surface à mettre ici
	//////////////////////////////////////////////
	SDL_LockSurface(image_surface);
	Uint32 pixel;
	Uint8 r,v,b,a;
	for (int x = 0;x<image_surface->w;x++){
		for (int y = 0;y<image_surface->h;y++){
			Uint32 pixel = obtenirPixel(image_surface,x,y);
			SDL_GetRGBA(pixel,image_surface->format,&r,&v,&b,&a);
			//changement
			Uint8 gris = (r+v+b)/3;
			//permet de mettre soit en noir soit en blanc
			if (2*gris>255){ 
				gris = 255;
			}
			else{
				gris = 0;
			}
			
			
			pixel = SDL_MapRGBA(image_surface->format,gris,gris,gris,a);
			

			//
			
			
			definirPixel(image_surface,x,y,pixel);	
		}
	}
	SDL_UnlockSurface(image_surface);
	
	//mise en place d'un filtre médian
	/*int nb255 =0;
	int nb0=0;
	for (int x = 0;x<image_surface->w;x++){
		for (int y = 0;y<image_surface->h;y++){
			Uint32 pixel = obtenirPixel(image_surface,x,y);
			SDL_GetRGBA(pixel,image_surface->format,&r,&v,&b,&a);
			//faire tous les pixels en fonction de la place
			
			if(nb255>nb0){
				pixel = SDL_MapRGBA(image_surface->format,255,255,255,a);
			}
			else if (nb0>nb255){
				pixel = SDL_MapRGBA(image_surface->format,0,0,0,a);
			}
			definirPixel(image_surface,x,y,pixel);
		}
	}
	*/
	
	
	
	


	//////////////////////////////////////////////
	SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer,image_surface);
	SDL_FreeSurface(image_surface);


	affichage(image_surface_origine,renderer,image_texture_origine,
	image_surface,image_texture);


	IMG_Quit();
	SDL_Quit();
	return 0;
}





