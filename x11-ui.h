#ifndef X11_UI_H
#define X11_UI_H

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <pango/pangocairo.h>
#include <librsvg/rsvg.h>

struct Area {
	int x, y, w, h;
};

struct Point {
	int x, y;
};


struct UI {
	Display *dpy;
	int screen;
	GC gc;
	Window win;
	Window root;
	XSetWindowAttributes swa;
	XIC xic;
	Pixmap canvas;
	XVisualInfo vinfo;
	cairo_surface_t *cs;
	cairo_t *c;
	int font_height_actual;		/* used to centre text vertically */
	PangoLayout *pangolayout;
	PangoFontDescription *pangofont;
};

struct UI *ui;

void ui_clear_canvas(void);
void grabkeyboard(void);
void grabpointer(void);
void ui_init_cairo(int canvas_width, int canvas_height, const char *font);
void ui_init(void);
void ui_get_screen_res(int *x0, int *y0, int *width, int *height);
void ui_init_canvas(int max_width, int max_height);
void ui_create_window(int x, int y, int w, int h);
void ui_draw_rectangle_rounded_at_top(double x, double y, double w, double h, double radius, double line_width, int fill, double *rgba);
void ui_draw_rectangle(double x, double y, double w, double h, double radius, double line_width, int fill, double *rgba);
void ui_draw_line(int x0, int y0, int x1, int y1, double line_width, double *rgba);
void ui_insert_text(char *s, int x, int y, int h, double *rgba);
int ui_get_text_height(const char *fontdesc);
int ui_is_point_in_area(struct Point p, struct Area a);
void ui_map_window(unsigned int w, unsigned int h);
void ui_cleanup(void);
cairo_surface_t *ui_get_png_icon(const char *filename);
RsvgHandle *ui_get_svg_icon(const char *filename);
void ui_insert_svg(RsvgHandle *svg, double x, double y, double size);
void ui_insert_image(cairo_surface_t *image, double x, double y, double size);

#endif /* X11_UI_H */
