#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);
    GtkWidget *window;
    GtkWidget *menu_box, *menu_nowa_gra, *menu_wczytaj_zapis, *menu_komputer, *tytul;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Order and Chaos");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    menu_box = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    menu_nowa_gra = gtk_button_new_with_label(u8"Nowa gra dla dwóch osób");
    menu_wczytaj_zapis = gtk_button_new_with_label("Wczytaj grę");
    menu_komputer = gtk_button_new_with_label("Nowa gra z komputerem");
    tytul = gtk_label_new("Order and Chaos");

    gtk_box_pack_start(GTK_BOX(menu_box),tytul,1,1,1);
    gtk_box_pack_start(GTK_BOX(menu_box),menu_nowa_gra,1,1,1);
    gtk_box_pack_start(GTK_BOX(menu_box),menu_wczytaj_zapis,1,1,1);
    gtk_box_pack_start(GTK_BOX(menu_box),menu_komputer,1,1,1);

    gtk_container_add(GTK_CONTAINER(window),menu_box);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
