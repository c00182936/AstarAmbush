#pragma once
#include <cmath>
#include <vector>
#include <memory>
#include <iostream>
#include <array>
#include <limits>
#include "CD_Vector2f.h"
#include "SDL.h"

class Tile
{
public:
	Tile();

	Tile(int xPos, int yPos, float w, float h, bool active);
	~Tile();
	bool m_active;

	Tile *parent;
	std::vector<Tile*> neighbours;
	float CalculateH(CD_Vector target)
	{
		//manhatten distance heuristic
		return abs(m_gridPosition.x - target.x) + abs(m_gridPosition.y - target.y);
	}
	void clear()
	{
		parent = nullptr;
		m_f = std::numeric_limits<int>::infinity();
		m_h = std::numeric_limits<int>::infinity();
		m_g = std::numeric_limits<int>::infinity();
	}
	void Render(SDL_Renderer * renderer);
	float getF() { return m_f; };
	float getH() { return m_h; };
	float getG() { return m_g; };
	CD_Vector GetGridPosition() { return m_gridPosition; };
	CD_Vector GetOrigin() { return m_origin; };
	void setF(float f) { m_f = f; };
	void setH(float h) { m_h = h; };
	void setG(float g) { m_g = g; };
	CD_Vector m_gridPosition;
	CD_Vector m_position;
	CD_Vector m_size;
	CD_Vector m_origin;
	SDL_Rect rectangle;
	bool operator==(const Tile other)
	{
		if (this->m_position == other.m_position)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	float m_f; //g + h
	float m_g; //total cost from start
	float m_h; //heuristic value
};

