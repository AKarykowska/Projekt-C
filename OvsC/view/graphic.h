#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

#include <gtk/gtk.h>

typedef struct pos {
    int x;
    int y;
} position;

GtkWidget *window;
GtkWidget *menu;
GtkWidget *menu_box, *menu_new_game, *menu_load, *title;

GtkWidget *main_box; //pionowy
GtkWidget *move; //label
GtkWidget *board; //grid
GtkWidget *choose_color; //label
GtkWidget *color; //poziomy
GtkWidget *color_button1, *color_button2;
GtkWidget *return_to_menu;
GtkWidget *save;

GtkWidget *event_board;
GdkRGBA white, red, blue;

void set_colors(void);
void set_menu(void);
void set_window(GtkWidget *opcja, gpointer data);
void show_menu(GtkWidget *window, gpointer data);
void set_main_area(void);
void save_game(GtkWidget *button, gpointer data);
void load_game(GtkWidget *button, gpointer data);
void destroy_window(GtkWidget *widget, gpointer data);
gboolean set_cell_color(GtkWidget *child, cairo_t *context, position *cell_position);
gboolean paint_configuration(GtkWidget *event_board, GdkEventButton *event, gpointer data);
gboolean paint_cell(GtkWidget *child, cairo_t *context, position *cell_position);

#endif // GRAPHIC_H_INCLUDED
