/*
libnbb - Nothing But Blits

Copyright (C) Ben "GreaseMonkey" Russell, 2013
All rights reserved.
See LICENCE-libnbb.txt for full licence (it's 2-clause BSD).
*/
#include <string.h>

#include "nbb.h"

/*
Reference implementation of a direct, block-byte-aligned blit with magic colour transparency.

WARNING: This only works correctly on little-endian machines!
*/
void blit_direct_aligned_magic(blimg_t *dest, blimg_t *src, int sx, int sy, int sw, int sh, int dx, int dy)
{
	int x,y;
	int pixlen;
	int stride;
	int magic, pmask;
	int p;
	char *sp, *dp;

	/* Prepare for blit */
	blit_prep_start(src, &sx, &sy, &sw, &sh, &dx, &dy, &sp, NULL, &pixlen);
	blit_prep_start(dest, &dx, &dy, &sw, &sh, &sx, &sy, &dp, NULL, NULL);

	/* Get pixel/stride length in bytes */
	pixlen = blfmt_blklen(dest->pixfmt) / 8; 
	stride = pixlen * sw;

	/* Get magic / pixel mask */
	magic = src->magic;
	pmask = (1 << (pixlen * 8)) - 1;

	/* Blit */
	for(y = 0; y < sh; y++, sp += src->pitch - stride, dp += dest->pitch - stride)
	for(x = 0; x < sw; x++, sp += pixlen, dp += pixlen)
	{
		p = *(int *)sp;
		if((p & pmask) != magic)
			*(int *)dp = (p & pmask)
				| ((*(int *)dp) & ~pmask);
	}
}

