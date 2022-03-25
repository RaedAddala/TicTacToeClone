#include "Render.h"

void Render(void)
{
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_RenderClear(Renderer);
	switch (Game.state)
	{
	case ONGAME: RenderRunningGame(); break;
	case PLAYER_O_W: RenderGameOver(PLAYER_O_WIN_Color); break;
	case PLAYER_X_W: RenderGameOver(PLAYER_X_WIN_Color); break;
	case TIE: RenderGameOver(TIE_Color); break;
	}
	SDL_RenderPresent(Renderer);
}

void RenderRunningGame(void)
{

}
void RenderGameOver(SDL_Color color) 
{

}