#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <png.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) : width{width}, height{height} {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[5][10]={"#EAF0CE", "#BBBE64", "white", "black", "blue"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 5; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

int Xwindow::getWidth() const { return width; }
int Xwindow::getHeight() const { return height; }

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int colour, int x, int y, string msg) {
  XSetForeground(d, gc, colours[colour]);
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

void Xwindow::drawTile(int r, int c, string piece, bool isWhite){
  string fileName = piece + ".png";
  FILE *fp = fopen(fileName.c_str(), "rb");
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info_ptr = png_create_info_struct(png_ptr);
  png_init_io(png_ptr, fp);
  png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
  int width = png_get_image_width(png_ptr, info_ptr);
  int height = png_get_image_height(png_ptr, info_ptr);
  png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);
  
  char* data = (char*) malloc(width * height * 4);  // 4 bytes for ARGB

  for (int y = 0; y < height; y++) {
    png_bytep row = row_pointers[y];
    for (int x = 0; x < width; x++) {
      png_bytep px = &(row[x * 4]); 
      
      data[(y * width + x) * 4 + 3] = 255;  // A
      data[(y * width + x) * 4 + 2] = (px[0] < 50 ? (isWhite ? 255 : 0) : ((r+c)%2 != 0 ? 187 : 234));  // R
      data[(y * width + x) * 4 + 1] = (px[0] < 50 ? (isWhite ? 255 : 0) : ((r+c)%2 != 0 ? 190 : 240));  // G
      data[(y * width + x) * 4 + 0] = (px[0] < 50 ? (isWhite ? 255 : 0) : ((r+c)%2 != 0 ? 100 : 206));  // B
    }
  }
  XImage *ximg = XCreateImage(d, DefaultVisual(d, 0), 24, ZPixmap, 0, data, width, height, 32, 0);
  GC gc = XCreateGC(d, w, 0, NULL);
  XPutImage(d, w, gc, ximg, 0, 0, r*60, c*60, width, height);
  XFlush(d);
  fclose(fp);
  XFreeGC(d, gc);
  XDestroyImage(ximg);
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  free(data);
}