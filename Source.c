/*
	Creator : Raed Addala
	Project : a TicTacToe clone
	Brief Description :
		This is my first programming project.
		I am making a TicTacToe Clone. No need for further info.
	Date of update : 24/03/2022
*/

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "Game.h"

SDL_bool Init(void);
void Quit(void);
void Render(void);
void InitGame(void);
void ClickOnCell(Uint8 row, Uint8 col);

SDL_Window* Window;
SDL_Renderer* Renderer;
game_t Game;

int main(int argc, char** argv)
{
	atexit(Quit);
	if(Init() == SDL_FALSE ) exit(EXIT_FAILURE);

	SDL_bool Working = SDL_TRUE;
	SDL_Event event;
	while (Working)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT :
				Working = SDL_FALSE;
				goto EnDofLoop;
			case SDL_MOUSEBUTTONDOWN :
				ClickOnCell( event.button.x/CELL_WIDTH , event.button.y/CELL_HEIGHT );
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

void Render(void)
{
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_RenderClear(Renderer);
	SDL_RenderPresent(Renderer);
}
void ClickOnCell(Uint8 row, Uint8 col)
{

}
void InitGame(void)
{
	for (register Uint8 i = 0; i < N * N; i++)
		Game.board[i] = EMPTY;
	Game.player = PLAYER_X;
	Game.state = ONGAME;
}
