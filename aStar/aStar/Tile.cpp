#include "Tile.h"


Tile::Tile()
{
}


Tile::Tile(int xPos, int yPos, float w, float h, bool active)
{
	m_active = active;
	m_gridPosition.x = xPos;
	m_gridPosition.y = yPos;
	m_size.x = w;
	m_size.y = h;
	m_position.x = m_gridPosition.x*m_size.x;
	m_position.y = m_gridPosition.y*m_size.y;
	m_origin.x = m_position.x + (m_size.x / 2);
	m_origin.y = m_position.y + (m_size.y / 2);
	parent = nullptr;
	m_f = std::numeric_limits<int>::infinity();
	m_h = std::numeric_limits<int>::infinity();
	m_g = std::numeric_limits<int>::infinity();
	rectangle.x = m_position.x;
	rectangle.y = m_position.y;
	rectangle.w = m_size.x;
	rectangle.h = m_size.y;
	
}

void Tile::Render(SDL_Renderer * renderer)
{
	if (m_active)
	{
		SDL_SetRenderDrawColor(renderer, 180, 100, 180, 255);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 100, 180, 180, 255);//change drawing colour if the tile is blocked or not
	}
	SDL_RenderFillRect(renderer, &rectangle);//draw rectangle
	SDL_SetRenderDrawColor(renderer, 255,255, 255, 1);
	SDL_RenderDrawRect(renderer, &rectangle);//draw rectangle
	//draw outlines
	//SDL_RenderDrawLine(renderer, rectangle.x, rectangle.y, rectangle.w + rectangle.x, rectangle.y);
	//SDL_RenderDrawLine(renderer, rectangle.w + rectangle.x, rectangle.y, rectangle.w + rectangle.x, rectangle.y + rectangle.h);
	//SDL_RenderDrawLine(renderer, rectangle.x, rectangle.y + rectangle.h, rectangle.w + rectangle.x, rectangle.y + rectangle.h);
	//SDL_RenderDrawLine(renderer, rectangle.x, rectangle.y, rectangle.x, rectangle.y + rectangle.w);
}
Tile::~Tile()
{
}
