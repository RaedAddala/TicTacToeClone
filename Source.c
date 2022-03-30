/*
	Creator : Raed Addala
	Project : a TicTacToe clone
	Brief Description :
		This is my first programming project.
		I am making a TicTacToe Clone. No need for further info.
		Update : I made the rendering of the different game states.
		Update : Implemented the ClickOnCell function and the game logic is right
	Date of update : 30/03/2022
*/

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Render.h"

SDL_bool Init(void);
void Quit(void);
void InitGame(void);
void ClickOnCell(Uint8, Uint8);
SDL_bool EmptyCellsCheck(void);
SDL_bool PlayerWonConditionCheck(Uint8);

const int WINDOW_WIDTH = W_WIDTH;
const int WINDOW_HEIGHT = W_HEIGHT;
const float CELL_WIDTH = (float)W_WIDTH / N;
const float CELL_HEIGHT = (float)W_HEIGHT / N;

int main(int argc, char** argv)
{
	atexit(Quit);
	if (Init() == SDL_FALSE) exit(EXIT_FAILURE);
	SDL_bool Working = SDL_TRUE;
	SDL_Event event;
	while (Working)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				Working = SDL_FALSE;
				goto EnDofLoop;
			case SDL_MOUSEBUTTONDOWN:
				ClickOnCell(event.button.y / CELL_HEIGHT, event.button.x / CELL_WIDTH);
				break;
			default:
				break;
			}
		}
		Render();
	EnDofLoop:;
	}
	exit(EXIT_SUCCESS);
}
SDL_bool Init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO))return SDL_FALSE;
	Window = SDL_CreateWindow("TicTacToe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (!Window)
	{
		SDL_Log(SDL_GetError());
		return SDL_FALSE;
	}
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!Renderer)
	{
		SDL_Log(SDL_GetError());
		return SDL_FALSE;
	}
	InitGame();
	return SDL_TRUE;
}
void Quit(void)
{
	if (Renderer) SDL_DestroyRenderer(Renderer);
	if (Window) SDL_DestroyWindow(Window);
	SDL_Quit();
}
void ClickOnCell(Uint8 row, Uint8 col)
{
	if (Game.state == ONGAME)
	{
		if (Game.board[row * N + col] == EMPTY)
		{
			Game.board[row * N + col] = Game.player;

			if (Game.player == PLAYER_O) Game.player = PLAYER_X;
			else Game.player = PLAYER_O;
			// CHECK GAME OVER STATES CONDITIONS :
			if (PlayerWonConditionCheck(PLAYER_O) == SDL_TRUE)
				Game.state = PLAYER_O_W;
			else if (PlayerWonConditionCheck(PLAYER_X) == SDL_TRUE)
				Game.state = PLAYER_X_W;
			else if (EmptyCellsCheck() == SDL_TRUE) Game.state = TIE;
		}
	}
	else InitGame();
}
void InitGame(void)
{
	for (register Uint8 i = 0; i < N * N; i++)
		Game.board[i] = EMPTY;
	Game.player = PLAYER_X;
	Game.state = ONGAME;
}

SDL_bool PlayerWonConditionCheck(Uint8 player)
{

	Uint8 solidCol, solidRow, DiagL, DiagR = DiagL = 0;

	for (Uint8 i = 0; i < N; ++i)
	{
		solidCol = solidRow = 0;
		for (Uint8 j = 0; j < N; ++j)
		{
			if (Game.board[i * N + j] == player) ++solidRow;
			if (Game.board[j * N + i] == player) ++solidCol;
		}
		if (solidRow >= N || solidCol >= N)return SDL_TRUE;
		if (Game.board[i * N + i] == player) ++DiagL;
		if (Game.board[i * N + (N - i - 1)] == player) ++DiagR;
	}
	if (DiagR >= N || DiagL >= N)return SDL_TRUE;
	return SDL_FALSE;
}
SDL_bool EmptyCellsCheck(void)
{
	for (register Uint8 i = 0; i < N * N; i++)
		if (Game.board[i] == EMPTY)	return SDL_FALSE;
	return SDL_TRUE;
}