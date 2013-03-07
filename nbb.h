/*
libnbb - Nothing But Blits

Copyright (C) Ben "GreaseMonkey" Russell, 2013
All rights reserved.
See LICENCE-libnbb.txt for full licence (it's 2-clause BSD).
*/
typedef struct blimg
{
	int w,h;
	int pitch;
	int pixfmt;
	int magic;
	int palfmt;
	int pallen;
	char *pal;
	char *data;
} blimg_t;

typedef struct blfmt
{
	int (*fn_conv)(blimg_t *src, blimg_t *dest, int sx, int sy, int sw, int sh, int dx, int dy); 
	int chain;
} blfmt_t;

enum
{
	BLFMT_NONE = 0,

	/* RGB colourspace */
	BLFMT_BGRA8,
	BLFMT_RGBA8,
	BLFMT_ABGR8,
	BLFMT_ARGB8,
	
	BLFMT_BGRX8,
	BLFMT_RGBX8,
	BLFMT_XBGR8,
	BLFMT_XRGB8,
	BLFMT_BGR8,
	BLFMT_RGB8,

	BLFMT_16RGBL,
	BLFMT_16RGBB,
	BLFMT_16BGRL,
	BLFMT_16BGRB,

	BLFMT_15XRGBL,
	BLFMT_15XRGBB,
	BLFMT_15ARGBL,
	BLFMT_15ARGBB,
	BLFMT_15RGBXL,
	BLFMT_15RGBXB,
	BLFMT_15RGBAL,
	BLFMT_15RGBAB,

	/* direct colour */
	BLFMT_P8,

	BLFMT_P4CB,
	BLFMT_P4LB,
	BLFMT_P2CB,
	BLFMT_P2LB,
	BLFMT_P1B,

	BLFMT_P4CL,
	BLFMT_P4LL,
	BLFMT_P2CL,
	BLFMT_P2LL,
	BLFMT_P1L,

	BLFMT_COUNT
};

int blfmt_blklen(int fmt);

void blimg_free(blimg_t *img);
void blimg_prep(blimg_t *img, int w, int h, int pitch, int pixfmt, int magic, int palfmt, int pallen, char *data, char *pal);
blimg_t *blimg_new(int w, int h, int pitch, int pixfmt, int magic, int palfmt, int pallen);

blimg_t *bltmp_acquire(int w, int h, int pitch, int pixfmt, int magic, int palfmt, int pallen, char *pal);
void bltmp_release(blimg_t *img);
void bltmp_free_unused(void);
void bltmp_free_all(void);

void blit_prep_start(blimg_t *img, int *x, int *y, int *w, int *h, int *ax, int *ay, char **ptr, int *subptr, int *pixlen);

void blit_direct_aligned(blimg_t *dest, blimg_t *src, int sx, int sy, int sw, int sh, int dx, int dy);
void blit_direct_aligned_magic(blimg_t *dest, blimg_t *src, int sx, int sy, int sw, int sh, int dx, int dy);
void blit_mapped_aligned(blimg_t *dest, blimg_t *src, int sx, int sy, int sw, int sh, int dx, int dy);

int blconv_rgb8_brswap(blimg_t *dest, blimg_t *src, int sx, int sy, int sw, int sh, int dx, int dy);

