#pragma once
#include<SDL.h>



#define N 3
#define W_WIDTH 1280
#define W_HEIGHT 700

const int WINDOW_WIDTH = W_WIDTH;
const int WINDOW_HEIGHT = W_HEIGHT;
const float CELL_WIDTH = (float)W_WIDTH / N;
const float CELL_HEIGHT = (float)W_HEIGHT / N;

// game_t states 
#define ONGAME 0
#define PLAYER_O_W 1
#define PLAYER_X_W 2
#define TIE 3
// Player and board states :
#define EMPTY 0
#define PLAYER_O 1
#define PLAYER_X 2

typedef struct game_t
{
	Uint8 board[N * N];
	Uint8 player;
	Uint8 state;
} game_t;
