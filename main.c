/**
 * Author: cobb208
 * Date: 03June2022
 * Description: A simple tic-tac-toe game, first C program I have built.
 */

#include <stdio.h>
#include <string.h>

#define PLAYER_1 "Player 1"
#define PLAYER_1_SYM 'X'
#define PLAYER_2 "Player 2"
#define PLAYER_2_SYM 'O'

char play_board[20];
int player_one_turn = 1;

void Initialize_State();
void Print_board();
int Spot_taken(const char board[], int choice);
void Toggle_player_turn();
void Initiate_Slot(int choice);
int Winner_validation(char **arr, char player_sym);
int Check_for_win();
void GameLoop();


int main()
{
    GameLoop();
    printf("Play again y/n?");

    char choice = '\0';
    fgets(&choice, 2, stdin);
    if(choice == 'y' || choice == 'Y') {
        fflush(stdin);
        GameLoop();
    }
    if(choice == 'n' || choice == 'N')
    {
        return 0;
    }

    return 0;
}

void Initialize_State()
{
    strcpy(play_board, "-|-|-\n-|-|-\n-|-|-\n");
    player_one_turn = 1;
}

void Print_board()
{
    for(int i = 0; i < sizeof(play_board); i++)
    {
        printf("%c", play_board[i]);
    }

    printf("\n");
}

int Spot_taken(const char board[], int choice)
{
    if(board[choice] != '-')
    {
        printf("Spot is taken\n");
        return 1;
    }

    return 0;
}


void Toggle_player_turn()
{
    if(player_one_turn == 1)
    {
        player_one_turn = 0;
        return;
    }

    player_one_turn = 1;
}

void Initiate_Slot(int choice)
{
    if(!Spot_taken(play_board, choice))
    {
        if(player_one_turn == 1)
        {
            play_board[choice] = PLAYER_1_SYM;
            Toggle_player_turn();
        } else {
            play_board[choice] = PLAYER_2_SYM;
            Toggle_player_turn();
        }
    }

    Print_board();
}


int Winner_validation(char **arr, char player_sym)
{
    int arr_size = sizeof(arr) / sizeof(void);


    for(int i = 0; i < arr_size; i++)
    {
        int sub_arr = 3;
        int won = 1;

        for(int j = 0; j < sub_arr; j++)
        {
            if(arr[i][j] != player_sym)
            {
                won = 0;
            }
        }

        if(won == 1)
        {
            return 1;
        }

    }

    return 0;
}



int Check_for_win()
{
    char position1 = play_board[0]; // Upper Left
    char position2 = play_board[2]; // Upper Mid
    char position3 = play_board[4]; // Upper Right
    char position4 = play_board[6]; // Mid Left
    char position5 = play_board[8]; // Mid Mid
    char position6 = play_board[10]; // Mid Right
    char position7 = play_board[12]; // Bottom Left
    char position8 = play_board[14]; // Bottom Mid
    char position9 = play_board[16];

    char left_vertical_row[] = {
            position1,
            position4,
            position7
    };

    char mid_vertical_row[] = {
            position2,
            position5,
            position8
    };
    char right_vertical_row[] = {
            position3,
            position6,
            position9
    };

    char top_horizontal_row[] = {
            position1,
            position2,
            position3
    };
    char mid_horizontal_row[] = {
            position4,
            position5,
            position6
    };
    char bottom_horizontal_row[] = {
            position7,
            position8,
            position9
    };

    char diagonal_left_to_right[] = {
            position1,
            position5,
            position9
    };

    char diagonal_right_to_left[] = {
            position3,
            position5,
            position7
    };

    char *win_conditions[] = {
            left_vertical_row,
            mid_vertical_row,
            right_vertical_row,
            top_horizontal_row,
            mid_horizontal_row,
            bottom_horizontal_row,
            diagonal_left_to_right,
            diagonal_right_to_left
    };
    int player_1_victory = Winner_validation(win_conditions, PLAYER_1_SYM);
    int player_2_victory = Winner_validation(win_conditions, PLAYER_2_SYM);

    if(player_1_victory == 1)
    {
        printf("%s wins!\n", PLAYER_1);
        return 0;
    }
    if(player_2_victory)
    {
        printf("%s wins!\n", PLAYER_2);
        return 0;
    }

    return 1;
}

void GameLoop()
{
    Initialize_State();
    Print_board();

    int running = 1;

    while(running == 1)
    {
        if(player_one_turn)
        {
            printf("\n%s enter your choice: ", PLAYER_1);
        } else {
            printf("\n%s enter your choice: ", PLAYER_2);
        }


        char choice = '\0';

        fgets(&choice, 2, stdin);

        switch(choice) {
            case '1':
                Initiate_Slot(0);
                break;
            case '2':
                Initiate_Slot(2);
                break;
            case '3':
                Initiate_Slot(4);
                break;
            case '4':
                Initiate_Slot(6);
                break;
            case '5':
                Initiate_Slot(8);
                break;
            case '6':
                Initiate_Slot(10);
                break;
            case '7':
                Initiate_Slot(12);
                break;
            case '8':
                Initiate_Slot(14);
                break;
            case '9':
                Initiate_Slot(16);
                break;
            default:
                printf("Incorrect value try again!");
                break;
        }
        fflush(stdin);
        running = Check_for_win();
    }
}