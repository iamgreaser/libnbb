/*
libnbb - Nothing But Blits

Copyright (C) Ben "GreaseMonkey" Russell, 2013
All rights reserved.
See LICENCE-libnbb.txt for full licence (it's 2-clause BSD).
*/
#include <string.h>

#include "nbb.h"

/*
Reference implementation of a direct, block-byte-aligned alpha blit.
*/
void blit_rgba8_aligned_alpha(blimg_t *dest, blimg_t *src, int sx, int sy, int sw, int sh, int dx, int dy)
{
	int x, y, i;
	int aidx;
	unsigned int aval;
	int stride;
	unsigned char *sp, *dp;

	/* Prepare for blit */
	blit_prep_start(src, &sx, &sy, &sw, &sh, &dx, &dy, (char **)&sp, NULL, NULL);
	blit_prep_start(dest, &dx, &dy, &sw, &sh, &sx, &sy, (char **)&dp, NULL, NULL);

	/* Get stride length in bytes */
	stride = 4 * sw;

	/* Find alpha component */
	switch(src->pixfmt)
	{
		case BLFMT_ARGB8:
		case BLFMT_ABGR8:
			aidx = 0;
			break;
		case BLFMT_RGBA8:
		case BLFMT_BGRA8:
			aidx = 3;
			break;
		default:
			/* You shouldn't be using this blit for any other formats. */
			return;
	}

	/* Get pointers */
	sp = (unsigned char *)(src->data + (src->pitch * sy) + (4 * sx));
	dp = (unsigned char *)(dest->data + (dest->pitch * dy) + (4 * dx));

	/* Blit */
	for(y = 0; y < sh; y++, sp += src->pitch - stride, dp += dest->pitch - stride)
	for(x = 0; x < sw; x++, sp += 4, dp += 4)
	{
		aval = sp[aidx];
		aval += (aval>>8);
		for(i = 0; i < 4; i++)
			if(i != aidx)
				dp[i] = ((sp[i]*aval) + (dp[i]*(0x100-aval)) + 0x80)>>8;
	}
}

