#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *menu;
GtkWidget *menu_box, *menu_new_game, *menu_load, *menu_ai, *title;

GtkWidget *main_box; //pionowy
GtkWidget *move; //label
GtkWidget *board; //grid
GtkWidget *choose_color; //label
GtkWidget *color; //poziomy
GtkWidget *color_button1, *color_button2;
GtkWidget *return_to_menu;

GtkWidget *event_board;

GdkRGBA red, blue, white;
int chosen_color;
int board_state[6][6]={0};
int turn=0;

typedef struct pos {
    int x;
    int y;
} position;

int check_diagonal(int x, int y, int dir)
{
    int count = 0, current = board_state[x][y];
    while(x >= 0 && y >= 0 && x < 6 && y < 6)
    {
        if(board_state[x][y]==current && board_state[x][y]!=0)
            count++;
        else
        {
            count = 1;
            current = board_state[x][y];
        }
        if(count >= 5)
            return 1;
        y += dir;
        x++;
    }
    return 0;
}

void check_win_order(void)
{
    int current, count, win = 0;
    for(int i=0; i<6; i++)
    {
        count = 1;
        for(int j=0; j<6; j++)
        {
            if(j==0)
                current=board_state[i][j];
            else
            {
                if(board_state[i][j]==current && current != 0)
                    count++;
                else
                {
                    if(count >= 5)
                    {
                        win = 1;
                        break;
                    }
                    else
                    {
                        current = board_state[i][j];
                        count = 1;
                    }

                }

            }
        }
        if(count >= 5)
        {
            win = 1;
            break;
        }
    }

    for(int i=0; i<6; i++)
    {
        count = 1;
        for(int j=0; j<6; j++)
        {
            if(j==0)
                current=board_state[j][i];
            else
            {
                if(board_state[j][i]==current && current != 0)
                    count++;
                else
                {
                    if(count >= 5)
                    {
                        win = 1;
                        break;
                    }
                    else
                    {
                        current = board_state[j][i];
                        count = 1;
                    }

                }

            }
        }
        if(count >= 5)
        {
            win = 1;
            break;
        }
    }
    if(win || check_diagonal(0, 0, 1) || check_diagonal(1, 0, 1) || check_diagonal(0, 1, 1) || check_diagonal(0, 5, -1) || check_diagonal(0, 4, -1) || check_diagonal(1, 5, -1))
        gtk_label_set_text(GTK_LABEL(move),u8"Porządek wygrał");
}

void check_win_chaos(void)
{
    for(int i=0; i<6; i++)
        for(int j=0; j<6; j++)
            if(board_state[i][j]==0)
                return;
    gtk_label_set_text(GTK_LABEL(move),u8"Chaos wygrał");
}

static void change_color(GtkToggleButton *button, gpointer data)
{
    int color = GPOINTER_TO_INT(data);
    if(color == 1)
        chosen_color = 1;
    else
        chosen_color = 2;
}

gboolean paint_cell(GtkWidget *child, cairo_t *context, position *cell_position)
{
    guint height, width;
    height = gtk_widget_get_allocated_height(child);
    width = gtk_widget_get_allocated_width(child);
    gtk_render_background(gtk_widget_get_style_context(child), context, 0, 0, width, height);
    cairo_rectangle(context, 0, 0, width, height);
    if(board_state[cell_position->x][cell_position->y]==1)
        gdk_cairo_set_source_rgba(context, &red);
    else
        gdk_cairo_set_source_rgba(context, &blue);
    cairo_fill(context);
    return FALSE;
}

gboolean paint_configuration(GtkWidget *event_board, GdkEventButton *event, gpointer data)
{
    int column = (event->x)/100;
    int row = (event->y)/100;
    if(board_state[column][row]==0)
        {
            board_state[column][row]=chosen_color;
            if(turn == 0)
            {
                turn = 1;
                gtk_label_set_text(GTK_LABEL(move),"Tura: Chaos");
            }
            else
            {
                turn = 0;
                gtk_label_set_text(GTK_LABEL(move),u8"Tura: Porządek");
            }
        }
    else
        return TRUE;
    GtkWidget *child = gtk_grid_get_child_at(GTK_GRID(board), column, row);
    position *cell_position = malloc(sizeof(position));
    cell_position->x = column;
    cell_position->y = row;
    g_signal_connect(child, "draw", G_CALLBACK(paint_cell), cell_position);
    gtk_widget_queue_draw(child);
    check_win_order();
    check_win_chaos();
    return TRUE;
}

gboolean set_cell_color(GtkWidget *child, cairo_t *context, position *cell_position)
{
    guint height, width;
    height = gtk_widget_get_allocated_height(child);
    width = gtk_widget_get_allocated_width(child);
    gtk_render_background(gtk_widget_get_style_context(child), context, 0, 0, width, height);
    cairo_rectangle(context, 0, 0, width, height);
    gdk_cairo_set_source_rgba(context, &white);
    cairo_fill(context);
    return FALSE;
}

static void destroy_window(GtkWidget *widget, gpointer data)
{
    gtk_widget_destroy(window);
}

static void set_main_area(void)
{
    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    move = gtk_label_new(u8"TURA: Porządek");
    board = gtk_grid_new();

    for (int x=0; x<6; x++)
        for(int y=0; y<6; y++)
        {
            GtkWidget *child;
            child = gtk_frame_new(NULL);
            gtk_widget_set_size_request(child, 100, 100);
            gtk_frame_set_shadow_type(GTK_FRAME(child), GTK_SHADOW_IN);
            gtk_grid_attach(GTK_GRID(board), child, x, y, 1, 1);
            position *cell_position = malloc(sizeof(position));
            g_signal_connect(child, "draw", G_CALLBACK(set_cell_color), NULL);
        }
    event_board = gtk_event_box_new();
    gtk_widget_set_valign(event_board, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(event_board, GTK_ALIGN_CENTER);
    gtk_container_add (GTK_CONTAINER (event_board), board);

    choose_color = gtk_label_new("Wybierz kolor: ");
    color = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    color_button1 = gtk_radio_button_new_with_label(NULL, "czerwony");
    color_button2 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_BUTTON(color_button1)), "niebieski");
    gtk_box_pack_start(GTK_BOX(color),choose_color,1,1,1);
    gtk_box_pack_start(GTK_BOX(color),color_button1,1,1,1);
    gtk_box_pack_start(GTK_BOX(color),color_button2,1,1,1);

    return_to_menu = gtk_button_new_with_label(u8"Powrót do menu");
    g_signal_connect(return_to_menu, "clicked", G_CALLBACK(destroy_window), NULL);


    gtk_box_pack_start(GTK_BOX(main_box),move,1,1,1);
    gtk_box_pack_start(GTK_BOX(main_box),event_board,1,1,1);
    gtk_box_pack_start(GTK_BOX(main_box),color,1,1,1);
    gtk_box_pack_start(GTK_BOX(main_box),return_to_menu,1,1,1);

    g_signal_connect(color_button1, "toggled", G_CALLBACK(change_color),GINT_TO_POINTER(1));
    g_signal_connect(color_button2, "toggled", G_CALLBACK(change_color),GINT_TO_POINTER(2));

    gtk_widget_set_events (event_board, GDK_BUTTON_PRESS);
    g_signal_connect (event_board, "button_press_event", G_CALLBACK(paint_configuration), NULL);

    gtk_container_add(GTK_CONTAINER(window), main_box);
    gtk_widget_show_all(window);
}

static void show_menu (GtkWidget *window, gpointer data)
{
    gtk_widget_show_all(menu);
}

static void set_window (GtkWidget *opcja, gpointer data)
{
    gtk_widget_hide(menu);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Order and Chaos");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
    g_signal_connect(window, "destroy", G_CALLBACK(show_menu), NULL);

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

void set_colors(void)
{
    gdk_rgba_parse(&white, "#FFF");
    gdk_rgba_parse(&red, "#FF0000");
    gdk_rgba_parse(&blue, "#0000FF");
    chosen_color = 1;
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    set_colors();
    set_menu();

    gtk_main();
    return 0;
}

//dialog
    /* GtkWidget *menu_dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION, GTK_BUTTONS_NONE, "Order and Chaos");
    gtk_dialog_add_buttons(GTK_DIALOG(menu_dialog), u8"Nowa gra dla dwóch osób", GTK_RESPONSE_YES, "Wczytaj grę", GTK_RESPONSE_ACCEPT, "Nowa gra z komputerem", GTK_RESPONSE_NO, NULL);
    int response = gtk_dialog_run(GTK_DIALOG(menu_dialog));
    gtk_widget_destroy(menu_dialog); */
