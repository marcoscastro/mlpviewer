#include <gui/gui.h>
#include <math.h>

void nearestResize(Byte* in, Byte* out,
				   int src_width, int src_height, int src_components, int src_stride,
				   int dest_width, int dest_height, int dest_components, int dest_stride)
{
	int i, j, x, y;
	float tx = (float) src_width / dest_width;
	float ty = (float) src_height / dest_height;
	Byte *src_pPixel, * dest_pPixel;
	for (i = 0; i < dest_height; i++)
	{
		y = ty * i;
		for (j = 0; j < dest_width; j++)
		{
			x = tx * j;
			src_pPixel = &in[y * src_stride + x * src_components];
			dest_pPixel = &out[i * dest_stride + j * dest_components];
			dest_pPixel[0] = src_pPixel[0];
			dest_pPixel[1] = src_pPixel[1];
			dest_pPixel[2] = src_pPixel[2];
			if(dest_components == 4)
				dest_pPixel[3] = src_pPixel[3];
		}
	}
}

void bilinearResize(Byte* in, Byte* out,
				   int src_width, int src_height, int src_components, int src_stride,
				   int dest_width, int dest_height, int dest_components, int dest_stride)
{
	int i, j, x0, y0;
	double x, y;
	double dx, dy;
	double tx = (double)src_width / dest_width;
	double ty = (double)src_height / dest_height;
	double a, b, c, d;
	Byte * src_pixel[4];
	Byte * src_pPixel, * dest_pPixel;
	for (i = 0; i < dest_height; i++)
	{
		y = ty * (i + 0.5) - 0.5;
		y0 = floor(y);
		dy = y - y0;
		if (y0 < 0)
			y0 = 0;
		else if(y0 >= src_height - 1)
			y0 = src_height - 2;
		for (j = 0; j < dest_width; j++)
		{
			x = tx * (j + 0.5) - 0.5;
			x0 = floor(x);
			dx = x - x0;
			if (x0 < 0)
				x0 = 0;
			else if(x0 >= src_width - 1)
				x0 = src_width - 2;
			src_pPixel = &in[y0 * src_stride + x0 * src_components];
			// get neigbors
			src_pixel[0] = src_pPixel;
			src_pixel[1] = src_pPixel + src_components;
			src_pixel[2] = src_pPixel + src_stride;
			src_pixel[3] = src_pPixel + src_stride + src_components;
			// optimization
			a = (1.0 - dx) * (1.0 - dy);
			b = dx         * (1.0 - dy);
			c = dy         * (1.0 - dx);
			d = dx         * dy;
			// get out pixel and set it
			dest_pPixel = &out[i * dest_stride + j * dest_components];
			dest_pPixel[0] = (Byte)(
					   src_pixel[0][0] * a +
					   src_pixel[1][0] * b +
					   src_pixel[2][0] * c +
					   src_pixel[3][0] * d);
			dest_pPixel[1] = (Byte)(
					   src_pixel[0][1] * a +
					   src_pixel[1][1] * b +
					   src_pixel[2][1] * c +
					   src_pixel[3][1] * d);
			dest_pPixel[2] = (Byte)(
					   src_pixel[0][2] * a +
					   src_pixel[1][2] * b +
					   src_pixel[2][2] * c +
					   src_pixel[3][2] * d);
   			if(dest_components == 4)
		    {
				dest_pPixel[3] = (Byte)(
						   src_pixel[0][3] * a +
						   src_pixel[1][3] * b +
						   src_pixel[2][3] * c +
						   src_pixel[3][3] * d);
		    }
		}
	}
}

inline Byte adjustByte(double v)
{
	if (v < 0) 
		return 0;
	if (v > 255) 
		return 255;
	return (int)round(v);
}

void bicubicResize(Byte* in, Byte* out,
				   int src_width, int src_height, int src_components, int src_stride,
				   int dest_width, int dest_height, int dest_components, int dest_stride)
{
	int i, j, x, y;
	double dx, dy;
	double tx = (double)src_width / dest_width;
	double ty = (double)src_height / dest_height;
	Byte * src_pPixel, * dest_pPixel;
	for (i = 0; i < dest_height; i++)
	{
		y = ty * i;
		dy = ty * i - y;
		for (j = 0; j < dest_width; j++)
		{
			x = tx * j;
			dx = tx * j - x;
			// get source pixel
			src_pPixel = &in[y * src_stride + x * src_components];
			// set out pixel
			dest_pPixel = &out[i * dest_stride + j * dest_components];
		}
	}
}

Image * nearestResize(Image* img, int new_width, int new_height)
{
	if(new_width == img->getWidth() && new_height == img->getHeight())
		return new Image(*img);
	Image * new_img = new Image(new_width, new_height, img->getColors());
	nearestResize(img->getData(), new_img->getData(),
			img->getWidth(), img->getHeight(), img->getColors() / 8, img->getStride(),
			new_img->getWidth(), new_img->getHeight(), img->getColors() / 8, new_img->getStride());
	new_img->apply();
	return new_img;
}

Image * bilinearResize(Image* img, int new_width, int new_height)
{
	if(new_width == img->getWidth() && new_height == img->getHeight())
		return new Image(*img);
	Image * new_img = new Image(new_width, new_height, img->getColors());
	bilinearResize(img->getData(), new_img->getData(),
			img->getWidth(), img->getHeight(), img->getColors() / 8, img->getStride(),
			new_img->getWidth(), new_img->getHeight(), img->getColors() / 8, new_img->getStride());
	new_img->apply();
	return new_img;
}
