CC = gcc 
CFLAGS = -W -Wall -ansi -std=c99 -g
LIBS = -L./SDL2_ttf/.libs -L./SDL2_image/.libs
LDFLAGS =`sdl2-config --cflags --libs -lSDL2_image` -lSDL2_ttf 
INCLUDES = -I./SDL2_ttf -I./SDL2_image
EXEC = pentomino
SRC = main.c ./rcs/fonctions_fichiers.c ./rcs/fonctions_SDL.c ./rcs/sdl2-ttf-light.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)
pentomino: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -rf *.o *~
mrproper: clean
	rm -rf $(EXEC)
