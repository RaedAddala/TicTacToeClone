#pragma once
#include "Game.h"

SDL_Window* Window;
SDL_Renderer* Renderer;
game_t Game;
const SDL_Color PLAYER_X_WIN_Color = {.r=0,.g=0,.b=0};
const SDL_Color PLAYER_O_WIN_Color = { .r = 0,.g = 0,.b = 0 };
const SDL_Color TIE_Color = { .r = 0,.g = 0,.b = 0 };


void Render(void);
void RenderRunningGame(void);
void RenderGameOver(SDL_Color);
