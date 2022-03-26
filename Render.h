#pragma once

#include "Game.h"

// As I only need one window and one renderer It seemed easier and more convinient to make them global variables
SDL_Window* Window;
SDL_Renderer* Renderer;
game_t Game;
void Render(void);


