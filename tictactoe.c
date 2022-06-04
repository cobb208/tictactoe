/**
 * Author: cobb208
 * Date: 04June2022
 * Description: A simple tic-tac-toe game, first C program I have built.
 * Version: 0.1.1
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "tictactoe.h"

#define PLAYER_1 "Player 1"
#define PLAYER_1_SYM 'X'
#define PLAYER_2 "Player 2"
#define PLAYER_2_SYM 'O'
#define EMPTY_LOCATION '-'
#define BOARD_SIZE 10


typedef struct Game {
    int board_size;
    int winner;
    char current_player;
    char empty_location;
    char current_player_name[9];
    char board[];
} Game;



Game *Create_game()
{
    Game *g = malloc(sizeof(Game) + (sizeof(char[BOARD_SIZE])));
    assert(g != NULL);
    g->board_size = BOARD_SIZE;
    g->winner = 0;
    g->current_player = PLAYER_1_SYM;
    strcpy(g->current_player_name, PLAYER_1);
    g->current_player_name[8] = '\0';
    g->empty_location = EMPTY_LOCATION;
    g->board[g->board_size - 1] = '\0';
    return g;
}

void Destroy_game(Game *game)
{
    assert(game != NULL);
    free(game);
}

void Print_board(Game *game)
{
    int game_board_index = 0;
    for(int i = 0; i < 3; i++)
    {
        char row[6];
        row[5] = '\0';

        int column_index = 0;
        int board_sym_toggle = 1;

        int j = 0;
        while(j < 3)
        {
            if(board_sym_toggle == 1)
            {
                row[column_index] = game->board[game_board_index];
                j++;
                column_index++;
                game_board_index++;
                board_sym_toggle = 0;
            } else {
                row[column_index] = '|';
                column_index++;
                board_sym_toggle = 1;
            }
        }
        printf("%s\n", row);
    }

}

void Start_game(Game *game, int board_size, char start_player_symbol)
{
    for(int i = 0; i < (board_size - 1); i++)
    {
        game->board[i] = game->empty_location;
    }
    game->current_player = start_player_symbol;

    Print_board(game);

}

int Get_player_input()
{
    char line_buffer[1024];
    line_buffer[0] = '\0';

    fgets(line_buffer, 1024, stdin);

    int number = 0;

    sscanf(line_buffer, "%d", &number);

    return number;
}

int Validate_player_input(int player_input)
{
    if(player_input > 0 && player_input <= 9)
    {
        return 1;
    }
    return 0;
}

void Change_player(Game *game)
{
    if(game->current_player == PLAYER_1_SYM)
    {
        game->current_player = PLAYER_2_SYM;
        strcpy(game->current_player_name, PLAYER_2);
        return;
    }
    game->current_player = PLAYER_1_SYM;
    strcpy(game->current_player_name, PLAYER_1);
}

void Place_player_choice(Game *game, int index)
{
    int valid_number = Validate_player_input(index);
    if(valid_number)
    {
        if(game->board[index - 1] == game->empty_location)
        {
            game->board[index - 1] = game->current_player;
            Change_player(game);
            return;
        }
        printf("Spot is taken try again!\n");
        return;
    }
    printf("Invalid input try again!\n");
}

int Check_Row(char a, char b, char c, char player_symbol)
{
    if(a == player_symbol && b == player_symbol && c == player_symbol)
    {
        return 1;
    }

    return 0;
}


int Check_Results(Game *game, char player_symbol)
{
    char top_left = game->board[0];
    char top_mid = game->board[1];
    char top_right = game->board[2];
    char mid_left = game->board[3];
    char mid_mid = game->board[4];
    char mid_right = game->board[5];
    char bot_left = game->board[6];
    char bot_mid = game->board[7];
    char bot_right = game->board[8];

    int results[] = {
            Check_Row(top_left, top_mid, top_right, player_symbol),
            Check_Row(mid_left, mid_mid, mid_right, player_symbol),
            Check_Row(bot_left, bot_mid, bot_right, player_symbol),
            Check_Row(top_left, mid_left, bot_left, player_symbol),
            Check_Row(top_mid, mid_mid, bot_mid, player_symbol),
            Check_Row(top_right, mid_right, bot_right, player_symbol),
            Check_Row(top_left, mid_mid, bot_right, player_symbol),
            Check_Row(bot_left, mid_mid, top_right, player_symbol)
    };

    int results_size = sizeof(results) / sizeof(int);

    for(int i = 0; i < results_size; i++)
    {
        if(results[i] == 1)
        {
            return 1;
        }
    }

    return 0;
}

int Check_for_winner(Game *game)
{
    if(Check_Results(game, PLAYER_1_SYM) == 1)
    {
        printf("%s Wins!\n", PLAYER_1);
        return 1;
    }

    if(Check_Results(game, PLAYER_2_SYM) == 1)
    {
        printf("%s Wins!\n", PLAYER_2);
        return 1;
    }

    return 0;
}

int Check_for_tie(Game *game)
{

    for(int i = 0; i < game->board_size; i++)
    {
        if(game->board[i] == game->empty_location)
        {
            return 0;
        }
    }
    printf("Cats game!\n");
    return 1;
}

void Game_loop()
{
    Game *game = Create_game();


    Start_game(game, BOARD_SIZE, PLAYER_1_SYM);

    do
    {
        printf("%s, enter your choice: ", game->current_player_name);
        int n = Get_player_input();

        Place_player_choice(game, n);

        if(Check_for_winner(game) == 1)
        {
            game->winner = 1;
        }

        if(Check_for_tie(game) == 1)
        {
            game->winner = 1;
        }

        Print_board(game);
    } while(game->winner == 0);

    Destroy_game(game);

}

int Play_again()
{
    printf("Play again? Y?");

    char line_buffer[1024];
    line_buffer[0] = '\0';

    fgets(line_buffer, 1024, stdin);

    if(line_buffer[0] == 'y' || line_buffer[0] == 'Y')
    {
        return 1;
    }

    return 0;
}

void Main_game_loop()
{
    int play_again = 1;

    while(play_again == 1)
    {
        Game_loop();
        play_again = Play_again();
    }
}