/*
libnbb - Nothing But Blits

Copyright (C) Ben "GreaseMonkey" Russell, 2013
All rights reserved.
See LICENCE-libnbb.txt for full licence (it's 2-clause BSD).
*/
#include <string.h>

#include "nbb.h"

/*
Reference implementation of a paletted-to-direct, block-byte-aligned blit.

Currently this only supports 8bpp as a base format.
If you wish to do 8bpp paletted to 8bpp paletted, and don't care about palette, use blit_direct_aligned.
*/
void blit_mapped_aligned(blimg_t *dest, blimg_t *src, int sx, int sy, int sw, int sh, int dx, int dy)
{
	int x,y;
	int spixlen, dpixlen;
	int sstride, dstride;
	char *sp, *dp;
	char *pal;

	/* Prepare for blit */
	blit_prep_start(src, &sx, &sy, &sw, &sh, &dx, &dy, &sp, NULL, &spixlen);
	blit_prep_start(dest, &dx, &dy, &sw, &sh, &sx, &sy, &dp, NULL, &dpixlen);

	/* Get pixel/stride lengths in bytes */
	spixlen = blfmt_blklen(src->pixfmt) / 8; 
	dpixlen = blfmt_blklen(dest->pixfmt) / 8; 
	sstride = spixlen * sw;
	dstride = dpixlen * sw;

	/* Get palette related stuff */
	pal = src->pal;

	/* Blit */
	for(y = 0; y < sh; y++, sp += src->pitch - sstride, dp += dest->pitch - dstride)
	for(x = 0; x < sw; x++, sp += spixlen, dp += dpixlen)
		memcpy(dp, &pal[dpixlen * (int)(*(unsigned char *)sp)], dpixlen);
}

