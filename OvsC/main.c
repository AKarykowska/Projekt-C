#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);
    GtkWidget *window; //name all widgets

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL); //add window
    gtk_window_set_title(GTK_WINDOW(window), "Order and Chaos"); //set title of the window
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); //destroy window

    gtk_widget_show_all(window); //show all widgets
    gtk_main(); //start the main loop
    return 0;
}
