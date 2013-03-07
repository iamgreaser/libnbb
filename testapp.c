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

	(void)argc;
	(void)argv;

	/* Loading a .tga the evil way */
	src = blimg_new(710, 597, 710*3, BLFMT_BGR8, -1, BLFMT_NONE, 0);
	fp = fopen("dat/rainbowclown-24bpp.tga","rb");
	fseek(fp, 18, SEEK_CUR);
	fread(src->data, 3*710*597, 1, fp);
	fclose(fp);

	/* Start SDL for our test */
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_NOPARACHUTE);
	screen = SDL_SetVideoMode(640, 480, 24, 0);
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, SIG_DFL);

	/* Prepare our blimg_t for the screen */
	blimg_prep(&dest, screen->w, screen->h, screen->pitch, BLFMT_BGR8, -1, BLFMT_NONE, 0, screen->pixels, NULL);

	/* Perform a blit */
	blit_direct_aligned(&dest, src, 10, 10, 620, 460, 0, 5);

	/* Show it */
	SDL_Flip(screen);

	SDL_Delay(1000);

	return 0;
}

