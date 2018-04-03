#include "Tile.h"



Tile::Tile()
{
}

Tile::Tile(int xPos, int yPos, float w, float h, bool active)
{
	m_active = true;
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
}


Tile::~Tile()
{
}
