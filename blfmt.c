/*
libnbb - Nothing But Blits

Copyright (C) Ben "GreaseMonkey" Russell, 2013
All rights reserved.
See LICENCE-libnbb.txt for full licence (it's 2-clause BSD).
*/
#include "nbb.h"

/*
Gets the length of a block in bits.
Returns 0 if the format is either invalid or does not have a fixed bit width.
*/
int blfmt_blklen(int fmt)
{
	switch(fmt)
	{
		case BLFMT_BGRA8:
		case BLFMT_RGBA8:
		case BLFMT_ABGR8:
		case BLFMT_ARGB8:
		case BLFMT_BGRX8:
		case BLFMT_RGBX8:
		case BLFMT_XBGR8:
		case BLFMT_XRGB8:
			return 32;

		case BLFMT_BGR8:
		case BLFMT_RGB8:
			return 24;

		case BLFMT_16RGBL:
		case BLFMT_16RGBB:
		case BLFMT_16BGRL:
		case BLFMT_16BGRB:
		case BLFMT_15XRGBL:
		case BLFMT_15XRGBB:
		case BLFMT_15ARGBL:
		case BLFMT_15ARGBB:
		case BLFMT_15RGBXL:
		case BLFMT_15RGBXB:
		case BLFMT_15RGBAL:
		case BLFMT_15RGBAB:
			return 16;

		case BLFMT_P8:
			return 8;

		case BLFMT_P4CB:
		case BLFMT_P4LB:
		case BLFMT_P4CL:
		case BLFMT_P4LL:
			return 4;
		
		case BLFMT_P2CB:
		case BLFMT_P2LB:
		case BLFMT_P2CL:
		case BLFMT_P2LL:
			return 2;

		case BLFMT_P1B:
		case BLFMT_P1L:
			return 1;

		default:
			return 0;
	}
}

/*
Prepare the block format 
*/

