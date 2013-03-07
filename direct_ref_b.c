/*
libnbb - Nothing But Blits

Copyright (C) Ben "GreaseMonkey" Russell, 2013
All rights reserved.
See LICENCE-libnbb.txt for full licence (it's 2-clause BSD).
*/
#include <string.h>

#include "nbb.h"

/*
Reference implementation of a direct, block-byte-aligned blit.
*/
void blit_direct_aligned(blimg_t *dest, blimg_t *src, int sx, int sy, int sw, int sh, int dx, int dy)
{
	int y;
	int pixlen;
	int stride;
	char *sp, *dp;

	/* Get pixel/stride length in bytes */
	pixlen = blfmt_blklen(dest->pixfmt) / 8; 
	stride = pixlen * sw;

	/* Get pointers */
	sp = src->data + (src->pitch * sy) + (pixlen * sx);
	dp = dest->data + (dest->pitch * dy) + (pixlen * dx);

	/* Blit */
	for(y = 0; y < sh; y++, sp += src->pitch, dp += dest->pitch)
		memcpy(dp, sp, stride);
}

