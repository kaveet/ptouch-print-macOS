//  gd.h
//  ptouch-print
//
//  Created by David Phillip Oster on 12/16/23.
//

#ifndef gd_h
#define gd_h

enum {
  GD_FALSE,
  GD_TRUE
};

static const char *VERSION = "0.02";

/// used in gdImageSetStyle() to define a transparent pixel in a dashed line style.
static const int gdTransparent = 256;

/// used in gdImageLine() to specify a previously defines style.
static const int gdStyled = 257;

typedef struct CGContext CGImage;

/// A  gdImage is implemented by a CGContext
typedef CGImage gdImage;

/// does nothing in this implementation
/// @return GD_TRUE
int gdFTUseFontConfig(int flag);

/// this implementation only works on 0…255 grayscale
/// @param im - the input input image
/// @param index - the color table index 0 for black, 255 for white.
/// @return index - it's input
int gdImageBlue(gdImage *im, int index);

/// @return grayscale color index: just the average of the 3 components.
int gdImageColorAllocate(gdImage *im, int red, int green, int blue);

/// Copy a rectangle of pixels from src to dest.
///
/// @param dst - destination
/// @param src - source
/// @param dstX - destination X
/// @param dstY - destination Y
/// @param srcX - source X
/// @param srcY - source Y
/// @param w - Width
/// @param h - Height
void gdImageCopy(gdImage * dst, gdImage * src, int dstX, int dstY, int srcX, int srcY, int w, int h);

/// @return newly malloced image reading png from file.  nil on failure.
gdImage *gdImageCreateFromPng(FILE *inFile);

/// @return newly malloced white image, size [x,y] nil on failure.
gdImage *gdImageCreatePalette(int x, int y);

/// reclaiims memory of the image. im is dead after this.
void gdImageDestroy(gdImage *im);

/// undefined if x, y, outside of the bounds of the image.
/// @param im - input image
/// @return color index 0=black, 255=white of pixel at x,y.
int gdImageGetPixel(gdImage *im, int x, int y);

/// this implementation only works on 0…255 grayscale
/// @param im - the input input image
/// @param index - the color table index 0 for black, 255 for white.
/// @return index - it's input
int gdImageGreen(gdImage *im, int index);

/// Draws a line 1 pixel wide on image
/// @param im -  image
/// @param color - the color table index 0 for black, 255 for white. gdStyled for dashed lines.
void gdImageLine(gdImage *im, int x1, int y1, int x2, int y2, int color);

/// write image as a png
/// @return 0 on success, nonzero on error.
int gdImagePng(gdImage *im,FILE *outFile);

/// this implementation only works on 0…255 grayscale
/// @param im - the input input image
/// @param index - the color table index 0 for black, 255 for white.
/// @return index - it's input
int gdImageRed(gdImage *im, int index);

/// @param im - source image.
/// @param scale - positive scale factor. new image is ceil(x*scale), ceil(y*scale)
/// @return a newly created gdImage that is original image rescaled
gdImage *gdImageCreateScaled(gdImage *im, float scale);

/// Define a dashed line style for a later gdImageLine() - implemented just enough for this program.
/// @param im	The image to draw onto.
/// @param style array of pixel colors
/// @param styleLength number of items in style array
void gdImageSetStyle(gdImage *im, int *style, int styleLength);

/// Draws text or measures text or both.
/// @param im	 If non nil,  the image to draw onto.
/// @param brect  If non nil, output: the bounding rectangle as array of 8 integers where each pair represents the x- and y-coordinate of a point.  The points specify the lower left, lower right, upper right and upper left corner.
/// @param fg	The font color.
/// @param fontname	The font
/// @param ptsize	The height of the font in typographical points (pt).
/// @param angle	The angle in radian to rotate the font counter-clockwise. Ignored in this implementatiion
/// @param x	The x-coordinate of the basepoint (roughly the lower left corner) of the first letter.
/// @param y	The y-coordinate of the basepoint (roughly the lower left corner) of the first letter.
/// @param string	The string to render.
/// @return nil on success,  errorString on failure
char *gdImageStringFT(gdImage *im, int *brect, int fg, char *fontname, double ptsize, double angle, int x, int y, char *string);

/// @return width in pixels of image
int gdImageSX(gdImage *im);

/// @return height in pixels of image
int gdImageSY(gdImage *im);

#endif /* gd_h */
