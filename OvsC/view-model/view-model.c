#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "../view/graphic.h"
#include "view-model.h"
#include "../model/logic.h"

void change_color(GtkToggleButton *button, gpointer data)
{
    int color = GPOINTER_TO_INT(data);
    if(color == 1)
        chosen_color = 1;
    else
        chosen_color = 2;
}
