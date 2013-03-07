/*
libnbb - Nothing But Blits

Copyright (C) Ben "GreaseMonkey" Russell, 2013
All rights reserved.
See LICENCE-libnbb.txt for full licence (it's 2-clause BSD).
*/
#include <stdio.h>
#include <stdlib.h>

#include "nbb.h"

/*
Frees a blimg_t.

WARNING: This will ALSO free pal/data!
If you rolled your own blimg_t wrapper around e.g. a framebuffer, DO NOT use this function!
*/
void blimg_free(blimg_t *img)
{
	/* Check if NULL */
	if(img == NULL)
		return;
	
	/* Free what we have */
	if(img->pal != NULL) free(img->pal);
	if(img->data != NULL) free(img->data);
	free(img);
}

/*
Prepares a blimg_t.

See blimg_new for information on the parameters.
*/
void blimg_prep(blimg_t *img, int w, int h, int pitch, int pixfmt, int magic, int palfmt, int pallen, char *data, char *pal)
{
	/* Fill the structure */
	img->w = w;
	img->h = h;
	img->pitch = pitch;
	img->pixfmt = pixfmt;
	img->magic = magic;
	img->palfmt = palfmt;
	img->pallen = pallen;
	img->pal = pal;
	img->data = data;
}

/*
Create a new blimg_t, where:
- w,h are the dimensions of the image
- pitch is the offset in bytes for each line
- pixfmt is the pixel format used
- magic is the magic colour used for transparency, if any (-1 for no magic colour)
- palfmt is the palette format used (BLFMT_NONE for no palette)
- pallen is the length of the palette to allocate, in bytes (0 for no palette)

Allocates pitch*h bytes for data, and pallen bytes for pal.
Returns NULL on failure.
*/
blimg_t *blimg_new(int w, int h, int pitch, int pixfmt, int magic, int palfmt, int pallen)
{
	blimg_t *img;
	char *data, *pal;
	
	/* Allocate memory */
	img = malloc(sizeof(blimg_t));
	data = malloc(h*pitch);
	pal = (pallen == 0 ? NULL : malloc(pallen));

	/* If any allocations fail, free + return */
	if(img == NULL || data == NULL || (pallen != 0 && pal == NULL))
	{
		if(img != NULL) free(img);
		if(data != NULL) free(data);
		if(pal != NULL) free(pal);
		return NULL;
	}

	/* Fill the structure */
	blimg_prep(img, w, h, pitch, pixfmt, magic, palfmt, pallen, data, pal);

	/* Return image */
	return img;
}

