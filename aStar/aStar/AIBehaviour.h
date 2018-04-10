#pragma once
#include <cmath>
#include <vector>
#include <memory>
#include <iostream>
#include <array>
#include <limits>
#include "CD_Vector2f.h"


#define CELL_HEIGHT 64
#define CELL_WIDTH 64

#define ROOM_WIDTH 12
#define ROOM_HEIGHT 12

/// <summary>
/// Class used to descibe part of the grid used for A* pathfinding
/// </summary>
class Cell
{
public:
	Cell(int i, int j, bool active)
	{
		m_active = active;
		m_gridPosition.x = i;
		m_gridPosition.y = j;
		m_size.x = CELL_WIDTH;
		m_size.y = CELL_HEIGHT;
		m_position.x = m_gridPosition.x * m_size.x;
		m_position.y = m_gridPosition.y * m_size.y;
		m_origin.x = m_position.x + (CELL_WIDTH / 2);
		m_origin.y = m_position.y + (CELL_HEIGHT / 2);
		parent = nullptr;
		m_f = std::numeric_limits<int>::infinity();
		m_h = std::numeric_limits<int>::infinity();
		m_g = std::numeric_limits<int>::infinity();
	}

	Cell() {};
	~Cell() {};

	bool m_active;

	Cell *parent;
	std::vector<Cell*> neighbours;
	/// <summary>
	/// gets the straight line distance from one point to another
	/// </summary>
	/// <param name="goal">The poistion in the grid of the Target call</param>
	float CalculateH(CD_Vector target)
	{
		//manhatten distance heuristic
		return abs(m_gridPosition.x - target.x) + abs(m_gridPosition.y - target.y);
	}


	/// <summary>
	/// resets the node;
	/// </summary>
	void clear()
	{
		parent = nullptr;
		m_f = std::numeric_limits<int>::infinity();
		m_h = std::numeric_limits<int>::infinity();
		m_g = std::numeric_limits<int>::infinity();
	}

	float getF() { return m_f; };
	float getH() { return m_h; };
	float getG() { return m_g; };
	CD_Vector GetGridPosition() { return m_gridPosition; };
	CD_Vector GetOrigin() { return m_origin; };
	void setF(float f) { m_f = f; };
	void setH(float h) { m_h = h; };
	void setG(float g) { m_g = g; };

	bool operator==(const Cell other)
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
	
	CD_Vector m_gridPosition;
	CD_Vector m_position;
	CD_Vector m_size;
	CD_Vector m_origin;
	float m_f; //g + h
	float m_g; //total cost from start
	float m_h; //heuristic value

};

class PathFinder
{
public:
	PathFinder(std::vector<std::vector<int>> layout);
	PathFinder() {};
	~PathFinder();

	/// <summary>
	/// goes through the grid and resets all nodes and
	/// the open and closed sets
	/// </summary>
	void Reset();

	/// <summary>
	/// Finds the cell the position is in.
	/// ***Recommended to use the center origin of the entity***
	/// </summary>
	/// <param name="Pos">Position to check against</param>
	/// <returns>Pointer to the Cell the position is in </returns>
	Cell* GetNearestCell(CD_Vector Pos);

	void AddLinks();

	/// <summary>
	/// Performs the A* search algorithm
	/// </summary>
	/// <param name="start">Cell the entity is currently in</param>
	/// <param name="target">Cell the target is in</param>
	/// <returns>vector of origins of cells on the path from start cell to target cell</returns>
	std::vector<CD_Vector> AStar(Cell* start, Cell* target);
private:
	Cell* grid[ROOM_WIDTH][ROOM_HEIGHT];
	std::vector<Cell*> openSet;
	std::vector<Cell*> closedSet;
	Cell start;
	Cell target;

	
	void ClearAll()
	{
		start.clear();
		target.clear();
		openSet.clear();
		closedSet.clear();
	}
};

