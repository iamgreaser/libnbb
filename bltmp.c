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
blimg_t **bltmp_img = NULL;
int bltmp_max = 0;

/*
Releases a temporary image.
*/
void bltmp_release(blimg_t *img)
{
	if(img != NULL)
		img->pixfmt = BLFMT_NONE;
}

/*
Frees unused temporary images.
*/
void bltmp_free_unused(void)
{
	int i;

	for(i = 0; i < bltmp_max; i++)
		if(bltmp_img[i] != NULL && bltmp_img[i]->pixfmt == BLFMT_NONE)
		{
			/* Clear palette so we don't free the supplied palette */
			bltmp_img[i]->pal = NULL;

			/* Free img */
			blimg_free(bltmp_img[i]);
			bltmp_img[i] = NULL;
		}
}

/*
Frees all temporary images.
*/
void bltmp_free_all(void)
{
	int i;

	/* Mark all temp images as unused */
	for(i = 0; i < bltmp_max; i++)
		if(bltmp_img[i] != NULL)
			bltmp_img[i]->pixfmt = BLFMT_NONE;
	
	/* Free all unused images - all are marked "unused" by this point! */
	bltmp_free_unused();
	
	/* Free image list */
	free(bltmp_img);
	bltmp_img = NULL;
	bltmp_max = 0;
}

