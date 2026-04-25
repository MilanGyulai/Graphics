#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

double degree_to_radian(double degree)
{
	return degree * M_PI / 180.0;
}

GLuint load_texture(const char* filename){
	GLuint texture;
	SDL_Surface* surface;

	surface = IMG_Load(filename);
	if(surface == NULL){
		printf("ERROR: file was not found %s \n", filename);
		printf("ERROR: SDL_image %s \n", IMG_GetError());
		return 0;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int mode = GL_RGB;
	if(surface->format->BytesPerPixel == 4){
		mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	SDL_FreeSurface(surface);

	return texture;
}

