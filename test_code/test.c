#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

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



int main(int argc, char *argv[]){
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
	image_surface = IMG_Load("image1.jpeg"); //changer l'image ici
	if(image_surface == NULL){
		printf("peut pas trouver image");
		SDL_Quit();
	}

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

	int quit = 0;
	while(quit ==0){
		SDL_Event windowEvent;
		while(SDL_PollEvent(&windowEvent)){
			if(windowEvent.type == SDL_QUIT){
			quit = 1;
			break;
			}
		}
		SDL_Rect image_rect = {100,10,image_surface->w/2,image_surface->h/2}; //ici pour modifier l'affichage de l'image
		SDL_RenderCopy(renderer,image_texture,NULL,&image_rect);
		SDL_RenderPresent(renderer);
	}

	IMG_Quit();
	SDL_Quit();
	return 0;
}





