CC = gcc
CFLAGS = -Iinclude/ -Wall -Wextra -Wpedantic
SRC = src/app.c src/camera.c src/main.c src/scene.c src/utils.c

ifeq ($(OS), Windows_NT)
	LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lm
	TARGET = main.exe
else
	LIBS = -lSDL2 -lSDL2_image -lGL -lm
	TARGET = main
endif

all:
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(TARGET)