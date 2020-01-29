#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
GtkWidget *window;

static void set_window (GtkWidget *menu, gpointer data)
{
    gtk_widget_hide(gtk_widget_get_parent_window(menu));
    GtkWidget *test;
    test = gtk_label_new("a kuku");
    gtk_container_add(GTK_CONTAINER(window),test);
    gtk_widget_show_all(window);
}
int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Order and Chaos");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //dialog
    /* GtkWidget *menu_dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION, GTK_BUTTONS_NONE, "Order and Chaos");
    gtk_dialog_add_buttons(GTK_DIALOG(menu_dialog), u8"Nowa gra dla dwóch osób", GTK_RESPONSE_YES, "Wczytaj grę", GTK_RESPONSE_ACCEPT, "Nowa gra z komputerem", GTK_RESPONSE_NO, NULL);
    int response = gtk_dialog_run(GTK_DIALOG(menu_dialog));
    gtk_widget_destroy(menu_dialog); */

    GtkWidget *menu;
    GtkWidget *menu_box, *menu_nowa_gra, *menu_wczytaj_zapis, *menu_komputer, *tytul;

    menu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(menu), "Order and Chaos");
    g_signal_connect(menu, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    menu_box = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    menu_nowa_gra = gtk_button_new_with_label(u8"Nowa gra dla dwóch osób");
    menu_wczytaj_zapis = gtk_button_new_with_label("Wczytaj grę");
    menu_komputer = gtk_button_new_with_label("Nowa gra z komputerem");
    tytul = gtk_label_new("Order and Chaos");

    gtk_box_pack_start(GTK_BOX(menu_box),tytul,1,1,1);
    gtk_box_pack_start(GTK_BOX(menu_box),menu_nowa_gra,1,1,1);
    gtk_box_pack_start(GTK_BOX(menu_box),menu_wczytaj_zapis,1,1,1);
    gtk_box_pack_start(GTK_BOX(menu_box),menu_komputer,1,1,1);

    gtk_container_add(GTK_CONTAINER(menu),menu_box);
    gtk_widget_show_all(menu);

    g_signal_connect(menu_nowa_gra, "clicked", G_CALLBACK(set_window), "a kuku");
    //g_signal_connect(menu_wczytaj_zapis, "clicked", G_CALLBACK(set_window);
    //g_signal_connect(menu_komputer, "clicked", G_CALLBACK(set_window));

    gtk_main();
    return 0;
}
