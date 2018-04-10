#pragma once
#include "Tile.h"
#include "CD_Vector2f.h"
const int sizeSmall = 30;
const int sizeMed = 100;
const int sizeLarge = 1000;
class Pathfinder
{
public:
	Pathfinder(std::vector<std::vector<int>>& layout, int selectedGrid, float &gridX,float &gridY);
	Pathfinder() {};
	~Pathfinder();
	int gridSize;//1=small,2=med,3=large
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
	Tile* GetNearestTile(CD_Vector Pos);

	void AddLinks();

	/// <summary>
	/// Performs the A* search algorithm
	/// </summary>
	/// <param name="start">Cell the entity is currently in</param>
	/// <param name="target">Cell the target is in</param>
	/// <returns>vector of origins of cells on the path from start cell to target cell</returns>
	std::vector<CD_Vector> AStar(Tile* start, Tile* target);
private:
	float cellW, cellH;
	Tile* smallGrid[sizeSmall][sizeSmall];
	Tile* medGrid[sizeMed][sizeMed];
	Tile* largeGrid[sizeLarge][sizeLarge];
	
	//std::vector<std::vector<Tile>> grid;
	std::vector<Tile*> openSet;
	std::vector<Tile*> closedSet;
	Tile start;
	Tile target;

	void SmallLinks();
	void MedLinks();
	void LargeLinks();
	void ClearAll()
	{
		start.clear();
		target.clear();
		openSet.clear();
		closedSet.clear();
	}
};

