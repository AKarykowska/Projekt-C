#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *menu;
GtkWidget *menu_box, *menu_new_game, *menu_load, *menu_ai, *title;

GtkWidget *main_box; //pionowy
GtkWidget *move; //label
GtkWidget *board; //grid
GtkWidget *color; //na razie label

GtkWidget *event_board;

gboolean change_color (GtkWidget *board, GdkEventButton *event, gpointer data)
{
    int kolumna = (event->x)/100;
    int wiersz = (event->y)/100;
    printf("%d %d ", kolumna, wiersz);
    return TRUE;
}

static void set_main_area(void)
{
    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    move = gtk_label_new("TURA");
    board = gtk_grid_new();

    for (int x=0; x<6; x++)
        for(int y=0; y<6; y++)
        {
            GtkWidget *child;
            child = gtk_frame_new(NULL);
            gtk_widget_set_size_request(child, 100, 100);
            gtk_frame_set_shadow_type(GTK_FRAME(child), GTK_SHADOW_IN);
            gtk_grid_attach(GTK_GRID(board), child, x, y, 1, 1);

        }
    event_board = gtk_event_box_new();
    gtk_container_add (GTK_CONTAINER (event_board), board);

    color = gtk_label_new("KOLOR");

    gtk_box_pack_start(GTK_BOX(main_box),move,1,1,1);
    gtk_box_pack_start(GTK_BOX(main_box),event_board,1,1,1);
    gtk_box_pack_start(GTK_BOX(main_box),color,1,1,1);

    gtk_widget_set_events (event_board, GDK_BUTTON_PRESS);
    g_signal_connect (event_board, "button_press_event", G_CALLBACK(change_color), NULL);

    gtk_container_add(GTK_CONTAINER(window), main_box);
    gtk_widget_show_all(window);
}

static void set_window (GtkWidget *opcja, gpointer data)
{
    gtk_widget_hide(menu);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Order and Chaos");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    set_main_area();
}

static void set_menu (void)
{

    menu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(menu), "Order and Chaos");
    g_signal_connect(menu, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(menu), GTK_WIN_POS_CENTER_ALWAYS);
    menu_box = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    menu_new_game = gtk_button_new_with_label(u8"Nowa gra dla dwóch osób");
    menu_load = gtk_button_new_with_label("Wczytaj grę");
    menu_ai = gtk_button_new_with_label("Nowa gra z komputerem");
    title = gtk_label_new("Order and Chaos");

    gtk_box_pack_start(GTK_BOX(menu_box),title,1,1,1);
    gtk_box_pack_start(GTK_BOX(menu_box),menu_new_game,1,1,1);
    gtk_box_pack_start(GTK_BOX(menu_box),menu_load,1,1,1);
    gtk_box_pack_start(GTK_BOX(menu_box),menu_ai,1,1,1);

    gtk_container_add(GTK_CONTAINER(menu),menu_box);
    gtk_widget_show_all(menu);

    g_signal_connect(menu_new_game, "clicked", G_CALLBACK(set_window), "nowa gra");
    g_signal_connect(menu_load, "clicked", G_CALLBACK(set_window), "wczytaj zapis");
    g_signal_connect(menu_ai, "clicked", G_CALLBACK(set_window), "komputer");


}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    set_menu();

    gtk_main();
    return 0;
}

//dialog
    /* GtkWidget *menu_dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION, GTK_BUTTONS_NONE, "Order and Chaos");
    gtk_dialog_add_buttons(GTK_DIALOG(menu_dialog), u8"Nowa gra dla dwóch osób", GTK_RESPONSE_YES, "Wczytaj grę", GTK_RESPONSE_ACCEPT, "Nowa gra z komputerem", GTK_RESPONSE_NO, NULL);
    int response = gtk_dialog_run(GTK_DIALOG(menu_dialog));
    gtk_widget_destroy(menu_dialog); */
