/*
libnbb - Nothing But Blits

Copyright (C) Ben "GreaseMonkey" Russell, 2013
All rights reserved.
See LICENCE-libnbb.txt for full licence (it's 2-clause BSD).
*/
#include <stdio.h>

#include "nbb.h"

/*
Prepares variables for a static-width blit.
ptr, subptr, and pixlen are optional (use NULL if you don't want to read them).
*/
void blit_prep_start(blimg_t *img, int *x, int *y, int *w, int *h, int *ax, int *ay, char **ptr, int *subptr, int *pixlen)
{
	int bitx;
	int tptr, tsubptr, tpixlen;

	/* Replace some unused variables with temporaries */
	if(ptr == NULL) ptr = &tptr;
	if(subptr == NULL) subptr = &tsubptr;
	if(pixlen == NULL) pixlen = &tpixlen;

	/* Clamp top-left corner */
	if(*x < 0)
	{
		*w += *x;
		*ax -= *x;
		*x = 0;
	}

	if(*y < 0)
	{
		*h += *y;
		*ay -= *y;
		*y = 0;
	}

	/* Clamp bottom-right corner */
	if(*x + *w > img->w)
		*w = img->w - *x;
	if(*y + *h > img->h)
		*h = img->h - *y;
	
	/* Compensate for underflow for w/h */
	if(*w < 0) *w = 0;
	if(*h < 0) *h = 0;

	/* Get pixel length in bits */
	*pixlen = blfmt_blklen(img->pixfmt); 

	/* Get pointer */
	bitx = (*pixlen) * (*x);
	*ptr = img->data + (img->pitch * (*y)) + (bitx >> 3);
	*subptr = (bitx & 7);

}

