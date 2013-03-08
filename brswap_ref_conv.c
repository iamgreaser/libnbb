/*
libnbb - Nothing But Blits

Copyright (C) Ben "GreaseMonkey" Russell, 2013
All rights reserved.
See LICENCE-libnbb.txt for full licence (it's 2-clause BSD).
*/
#include <stdio.h>
#include "nbb.h"

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

