#include "Render.h"
#include "SDL2_gfxPrimitives.h"

void RenderRunningGame(void);
void RenderGameOver(const SDL_Color const*);
void RenderGrid(const SDL_Color const*);
void RenderBoard(const SDL_Color const*, const SDL_Color const*);
void RenderO(const SDL_Color const*, Uint8 , Uint8);
void RenderX(const SDL_Color const*, Uint8 , Uint8);

const SDL_Color PLAYER_X_Color = { .r = 255,.g = 10,.b = 10 };
const SDL_Color PLAYER_O_Color = { .r = 10,.g = 10,.b = 255 };
const SDL_Color TIE_Color = { .r = 78,.g = 70,.b = 75 }; // I used paint to get the rgb of a grey color
const SDL_Color GRID_LINES_Color = { .r = 255,.g = 255,.b = 255 };


void Render(void)
{
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_RenderClear(Renderer);
	switch (Game.state)
	{
		case ONGAME:	 RenderRunningGame();			  break;
		case PLAYER_O_W: RenderGameOver(&PLAYER_O_Color); break;
		case PLAYER_X_W: RenderGameOver(&PLAYER_X_Color); break;
		case TIE:		 RenderGameOver(&TIE_Color);	  break;
	}
	SDL_RenderPresent(Renderer);
}

void RenderRunningGame(void)
{
	RenderGrid(&GRID_LINES_Color);
	RenderBoard(&PLAYER_O_Color, &PLAYER_X_Color);
}
void RenderGameOver(const SDL_Color const* color)
{
	RenderGrid(color);
	RenderBoard(color,color);
}

void RenderGrid(const SDL_Color const* color)
{
	SDL_SetRenderDrawColor(Renderer, color->r, color->g, color->b, 255);
	int x,y;
	for (Uint8 i = 1; i < N; ++i)
	{
		x = CELL_WIDTH  * i;
		y = CELL_HEIGHT * i;
		SDL_RenderDrawLine(Renderer, x  , 0, x  , WINDOW_HEIGHT);
		SDL_RenderDrawLine(Renderer, x-1, 0, x-1, WINDOW_HEIGHT);
		SDL_RenderDrawLine(Renderer, x+1, 0, x+1, WINDOW_HEIGHT);

		SDL_RenderDrawLine(Renderer, 0, y  , WINDOW_WIDTH, y  );
		SDL_RenderDrawLine(Renderer, 0, y-1, WINDOW_WIDTH, y-1);
		SDL_RenderDrawLine(Renderer, 0, y+1, WINDOW_WIDTH, y+1);

	}
}
void RenderBoard(const SDL_Color const* colorO, const SDL_Color const* colorX)
{
	for (Uint8 i = 0; i < N; ++i)
	{
		for (Uint8 j = 0; j < N; ++j)
		{
			switch (Game.board[i * N + j])
			{
			case PLAYER_O: RenderO(colorO,i,j); break;
			case PLAYER_X: RenderX(colorX,i,j); break;
			default: ;
			}
		}
	}
}
void RenderO(const SDL_Color const* colorO,Uint8 r,Uint8 c)
{
	const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
	const float centerX = CELL_WIDTH * (c + 0.5);
	const float centerY = CELL_HEIGHT * (r + 0.5);
	filledCircleRGBA(Renderer,centerX,centerY,half_box_side + 7 , colorO->r,colorO->g,colorO->b,255);
	filledCircleRGBA(Renderer,centerX,centerY,half_box_side - 7, 0, 0, 0, 255);
}
void RenderX(const SDL_Color const* colorX, Uint8 r, Uint8 c)
{
	const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
	const float centerX = CELL_WIDTH *(c + 0.5);
	const float centerY = CELL_HEIGHT *(r + 0.5);
	thickLineRGBA(Renderer
		, centerX - half_box_side, centerY - half_box_side
		, centerX + half_box_side, centerY + half_box_side
		,12, colorX->r,colorX->g,colorX->b, 255);
	thickLineRGBA(Renderer
		, centerX + half_box_side, centerY - half_box_side
		, centerX - half_box_side, centerY + half_box_side
		, 12, colorX->r, colorX->g, colorX->b, 255);
}