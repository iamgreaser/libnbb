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
	BLCONV_MAP(BLFMT_BGR8, BLFMT_RGB8, blconv_rgb8_brswap, BLFMT_NONE);

	/*
	BLCONV_MAP(BLFMT_, BLFMT_, , BLFMT_NONE);
	*/
}

/*
Convert from one format to another.
*/
void blconv_auto(blimg_t *dest, blimg_t *src, int sx, int sy, int sw, int sh, int dx, int dy)
{
	/* */
}

