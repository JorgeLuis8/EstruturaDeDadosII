all: main.exe

main.exe: main.o
	gcc main.o -o main.exe

main.o: temas.o entrevistas.o podcast.o plataforma.o salvandomain.o main.c
	gcc temas.o entrevistas.o podcast.o plataforma.o salvandomain.o -c main.c

podcast.o: temas.o podcast.c
	gcc temas.o -c podcast.c

temas.o: entrevistas.o temas.c
	gcc entrevistas.o -c temas.c

entrevistas.o: entrevistas.c
	gcc -c entrevistas.c

plataforma.o: plataforma.c
	gcc -c plataforma.c

salvandomain.o: temas.o entrevistas.o podcast.o plataforma.o salvandomain.c
	gcc temas.o entrevistas.o podcast.o plataforma.o -c salvandomain.c