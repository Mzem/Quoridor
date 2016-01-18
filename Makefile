all: quoridor

run:	quoridor
		./quoridor
		
quoridor: 	main.o graphics.o affichage.o deplace.o mur.o jeu.o save.o
			gcc -Wall main.o graphics.o affichage.o deplace.o mur.o jeu.o save.o -o quoridor `sdl-config --libs` -lSDL_ttf -lm
		
main.o:	main.c jeu.h
		gcc -c -Wall main.c

affichage.o:	affichage.c definitions.h
				gcc -c -Wall affichage.c

deplace.o: 	deplace.c definitions.h
			gcc -c -Wall deplace.c
			
mur.o:		mur.c definitions.h deplace.h
			gcc -c -Wall mur.c 
			
save.o: 	save.c definitions.h
			gcc -c -Wall save.c			
				
jeu.o: 	jeu.c affichage.h deplace.h mur.h save.h
		gcc -c -Wall jeu.c


#construit le fichier binaire graphics.o
graphics.o: graphics.c graphics.h
	rm -f police.h
	touch police.h
	if test -e /usr/include/SDL_ttf.h;           then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/include/SDL/SDL_ttf.h;       then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/local/include/SDL_ttf.h;     then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/local/include/SDL/SDL_ttf.h; then echo "#define SDL_TTF_OK" > police.h; fi
	gcc -Wall `sdl-config --cflags`  -c graphics.c

clean:
	rm *.o
	rm quoridor
