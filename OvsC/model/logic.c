#include <stdio.h>
#include <stdlib.h>

#include "../view/graphic.h"
#include "logic.h"
#include "../view-model/view-model.h"

void erase_board(void)
{
    for(int i=0; i<6; i++)
        for(int j=0; j<6; j++)
            board_state[i][j]=0;
    turn = 0;
    end = 0;
    chosen_color = 1;
}

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
    {
        change_label_win(1);
        end = 1;
    }
}

void check_win_chaos(void)
{
    for(int i=0; i<6; i++)
        for(int j=0; j<6; j++)
            if(board_state[i][j]==0)
                return;
    change_label_win(2);
    end = 2;
}

void save_to_file(char *filename)
{
    FILE *file = fopen(filename, "w");
    if(file == NULL)
        return;
    fprintf(file, "%d\n", turn);
    fprintf(file, "%d\n", end);
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<6; j++)
        {
            fprintf(file, "%d ", board_state[j][i]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void load_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    if(file == NULL)
        return;
    fscanf(file, "%d", &turn);
    fscanf(file, "%d", &end);
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<6; j++)
        {
            fscanf(file, "%d", &board_state[j][i]);
        }
    }
    fclose(file);
}
