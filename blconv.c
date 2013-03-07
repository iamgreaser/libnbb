/*
libnbb - Nothing But Blits

Copyright (C) Ben "GreaseMonkey" Russell, 2013
All rights reserved.
See LICENCE-libnbb.txt for full licence (it's 2-clause BSD).
*/
#include <stdio.h>
#include "nbb.h"

/* 2D mapping of format converters, [i][j] means map i to j */
blfmt_t blconv_map[BLFMT_COUNT][BLFMT_COUNT];
int blconv_isready = 0;

#define BLCONV_MAP(fs, fd, zfn, zcn) { \
	blconv_map[(fs)][(fd)].fn_conv = (zfn); \
	blconv_map[(fs)][(fd)].chain = (zcn); }

/*
Swaps red and blue in RGB8/BGR8 images.
*/
int blconv_rgb8_brswap(blimg_t *dest, blimg_t *src, int sx, int sy, int sw, int sh, int dx, int dy) 
{
	int x, y;
	char *sp, *dp;

	/* Prepare for blit */
	blit_prep_start(src, &sx, &sy, &sw, &sh, &dx, &dy, &sp, NULL, NULL);
	blit_prep_start(dest, &dx, &dy, &sw, &sh, &sx, &sy, &dp, NULL, NULL);

	/* Blit away */
	for(y = 0; y < sh; y++, sp += src->pitch - sw*3, dp += dest->pitch - sw*3)
	for(x = 0; x < sw; x++)
	{
		*(dp++) = sp[2];
		*(dp++) = sp[1];
		*(dp++) = sp[0];
		sp += 3;
	}

	return 0;
}

/*
Prepare the conversion chain system.
This is automatically called, so you don't have to call it yourself.
*/
void blconv_init(void)
{
	int i,j;

	/* Do not attempt to re-ready the system */
	if(blconv_isready != 0)
		return;
	
	/* Clear the conversion table */
	for(i = 0; i < BLFMT_COUNT; i++)
	for(j = 0; j < BLFMT_COUNT; j++)
	{
		blconv_map[i][j].fn_conv = NULL;
		blconv_map[i][j].chain = BLFMT_NONE;
	}

	/* Load our converters into the table */
	BLCONV_MAP(BLFMT_RGB8, BLFMT_BGR8, blconv_rgb8_brswap, BLFMT_NONE);
	/*
	BLCONV_MAP(BLFMT_, BLFMT_, , BLFMT_NONE);
	*/
}

