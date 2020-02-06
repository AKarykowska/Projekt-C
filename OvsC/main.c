#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

#include "view/graphic.h"
#include "view-model/view-model.h"
#include "model/logic.h"

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    turn=0;
    end=0;
    set_colors();
    set_menu();

    gtk_main();
    return 0;
}
