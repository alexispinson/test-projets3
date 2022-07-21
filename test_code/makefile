build :
	gcc test.c -o executable $$(sdl2-config --cflags --libs) -lSDL2_image
run :
	./executable
clean : 
	rm executable
tout : 
	gcc test.c -o executable $$(sdl2-config --cflags --libs) -lSDL2_image
	./executable
	rm executable
