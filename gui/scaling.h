#ifndef _SCALING_H_
#define _SCALING_H_
#include <gui/gui.h>

typedef void (*ScalingFn)(Byte*, Byte*, int, int, int, int, int, int, int, int);

Image * nearestResize(Image* img, int new_width, int new_height);
void nearestResize(Byte* in, Byte* out,
				   int src_width, int src_height, int src_components, int src_stride,
				   int dest_width, int dest_height, int dest_components, int dest_stride);

Image * bilinearResize(Image* img, int new_width, int new_height);
void bilinearResize(Byte* in, Byte* out,
				   int src_width, int src_height, int src_components, int src_stride,
				   int dest_width, int dest_height, int dest_components, int dest_stride);

void bicubicResize(Byte* in, Byte* out,
				   int src_width, int src_height, int src_components, int src_stride,
				   int dest_width, int dest_height, int dest_components, int dest_stride);

#endif