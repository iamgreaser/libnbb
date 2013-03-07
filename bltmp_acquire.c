/*
libnbb - Nothing But Blits

Copyright (C) Ben "GreaseMonkey" Russell, 2013
All rights reserved.
See LICENCE-libnbb.txt for full licence (it's 2-clause BSD).
*/
#include <stdio.h>
#include <stdlib.h>
#include "nbb.h"

/* Dynamic list for temporary images */
extern blimg_t **bltmp_img;
extern int bltmp_max;

enum {
	ACSTEP_SAMEPITCH,
	ACSTEP_LARGER,
	ACSTEP_NULL,
	ACSTEP_UNALLOC,

	ACSTEP_COUNT
};

/*
Acquires a temporary image.
*/
blimg_t *bltmp_acquire(int w, int h, int pitch, int pixfmt, int magic, int palfmt, int pallen, char *pal)
{
	int r, i;
	int oldmax;

	/* Find an image */
	for(r = 0; r < ACSTEP_COUNT; r++)
	for(i = 0; i < bltmp_max; i++)
	{
		/* Is there an image here? */
		if(bltmp_img[i] == NULL)
		{
			if(r != ACSTEP_NULL)
				continue;

			/* Allocate and return */
			bltmp_img[i] = blimg_new(w, h, pitch, pixfmt, magic, palfmt, 0);
			bltmp_img[i]->pal = pal;
			bltmp_img[i]->pallen = pallen;
			return bltmp_img[i];
		}

		/* Is it allocated? */
		if(bltmp_img[i]->pixfmt != BLFMT_NONE)
			continue;

		/* Check the size if possible */
		if(r == ACSTEP_SAMEPITCH && bltmp_img[i]->pitch != pitch)
			continue;
		if(r <= ACSTEP_LARGER && (bltmp_img[i]->pitch < pitch || bltmp_img[i]->h < h))
			continue;

		/* Check if we need to reallocate */
		if(bltmp_img[i]->pitch != pitch || bltmp_img[i]->h < h)
			blimg_prep(bltmp_img[i], w, h, pitch, pixfmt, magic, palfmt, pallen, realloc(bltmp_img[i]->data, pitch*h), pal);
		else
			blimg_prep(bltmp_img[i], w, bltmp_img[i]->h, bltmp_img[i]->pitch, pixfmt, magic, palfmt, pallen, bltmp_img[i]->data, pal);

		/* Return */
		return bltmp_img[i];
	}

	/* Haven't found one, so extend the list and retry */
	oldmax = bltmp_max;
	bltmp_max += 10;
	bltmp_img = realloc(bltmp_img, sizeof(blimg_t *) * bltmp_max);
	for(i = oldmax; i < bltmp_max; i++)
		bltmp_img[i] = NULL;
	return bltmp_acquire(w, h, pitch, pixfmt, magic, palfmt, pallen, pal);
}

