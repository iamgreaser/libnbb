/*
libnbb - Nothing But Blits

Copyright (C) Ben "GreaseMonkey" Russell, 2013
All rights reserved.
See LICENCE-libnbb.txt for full licence (it's 2-clause BSD).
*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <SDL.h>

#include <signal.h>

#include <nbb.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	SDL_Surface *screen;
	blimg_t *src;
	blimg_t dest;
	int i;

	(void)argc;
	(void)argv;

	/* Loading a .tga the evil way */
	/*src = blimg_new(710, 597, 710*3, BLFMT_BGR8, 0xf7b509, BLFMT_NONE, 0);*/
	/*src = blimg_new(710, 597, 710, BLFMT_P8, -1, BLFMT_BGR8, 3*256);*/
	src = blimg_new(800, 600, 800*4, BLFMT_BGRA8, -1, BLFMT_NONE, 0);
	fp = fopen("dat/pngdemo.tga","rb");
	fseek(fp, 18, SEEK_CUR);
	/*fread(src->pal, 3*128, 1, fp);*/
	fread(src->data, 4*800*600, 1, fp);
	fclose(fp);

	/* Start SDL for our test */
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_NOPARACHUTE);
	screen = SDL_SetVideoMode(640, 480, 32, 0);
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, SIG_DFL);

	/* Prepare our blimg_t for the screen */
	blimg_prep(&dest, screen->w, screen->h, screen->pitch, BLFMT_BGRA8, -1, BLFMT_NONE, 0, screen->pixels, NULL);

	/* Perform a blit */
	for(i = 0; i < 10; i++)
	{
		blit_rgba8_aligned_alpha(&dest, src, 10, 10, 620, 460, 0, 5);

		/* Show it */
		SDL_Flip(screen);

		SDL_Delay(200);
	}

	bltmp_free_all();
	return 0;
}

