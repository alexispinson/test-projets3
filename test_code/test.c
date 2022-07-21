#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>





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
		SDL_Rect image_rect = {100,10,500,500}; //ici pour modifier l'affichage de l'image
		SDL_RenderCopy(renderer,image_texture,NULL,&image_rect);
		SDL_RenderPresent(renderer);
	}

	IMG_Quit();
	SDL_Quit();
	return 0;
}

SDL_Surface *creerSurface(SDL_Surface *s){
	SDL_Surface *retour = NULL;
	size_t i,j,w = (size_t) s->w, h = (size_t) s->h;
	Uint32 *dst = NULL, *src = NULL;
	if(SDL_LockSurface(s)<0){
		printf("Erreur SDL_LockSurface");
		goto lock_surface_fail;
	}
	dst = malloc((size_t)s->pitch * h);
	if(NULL==dst){
		perror("Erreur malloc : ");
		goto alloc_memory_fail;
	}

	src = (Uint32 *)s->pixels;

	for(i=0;i<h;i++){
		for (j=0;j<w;j++){
		//a mettre ici
			SDL_GetRGB(p[i*w+j],s->format,&color.r,&color.g,&color.b);
			Uint8 gris = (color.r+color.g+color.b)/3;
			pixels[i*w+j] = SDL_MapRGB(s->format,gris,gris,gris);
		}
	}

	retour = SDL_CreateRGBSurfaceWithFormatFrom(dst,s->w,s->h,32,s->pitch,s->format->format);

	if(NULL==retour)
	{
		printf("Erreur SDL_CreateRGBSurface");
		goto creatergbsurfacefrom_fail;
	}

creatergbsurfacefrom_fail:
	free(dst);
alloc_memory_fail:
	SDL_UnlockSurface(s);
lock_surface_fail:
	return retour;

}









