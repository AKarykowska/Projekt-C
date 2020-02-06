#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

int chosen_color;
int board_state[6][6];
int turn;
int end;

void erase_board(void);
void load_file(char *filename);
void save_to_file(char *filename);
void check_win_chaos(void);
void check_win_order(void);
int check_diagonal(int x, int y, int dir);

#endif // LOGIC_H_INCLUDED
