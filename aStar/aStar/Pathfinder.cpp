#include "Pathfinder.h"


Pathfinder::Pathfinder(std::vector<std::vector<int>> &layout, int selectedGrid, float &gridX, float &gridY):gridSize(selectedGrid)
{
	//for every row of the level Y
	
	for (int i = 0; i < layout.size(); i++)
	{
		//for every position in row X
		for (int j = 0; j < layout.at(i).size(); j++)
		{
			int num = layout.at(i).at(j);

			if (num == 7) //if the Tile is empty activate the Tile
			{
				if (gridSize == 1)
				{
					smallGrid[i][j] = new Tile(j, i,gridX,gridY, true);
				}
				else if (gridSize == 2)
				{
					medGrid[i][j] = new Tile(j, i, gridX, gridY, true);
				}
				else if (gridSize == 3)
				{
					largeGrid[i][j] = new Tile(j, i, gridX, gridY, true);
				}
				else
				{
					//error
				}

			}
			else //wrong number given so just turn off the Tile
			{

				if (gridSize == 1)
				{
					smallGrid[i][j] = new Tile(j, i, gridX, gridY, false);
				}
				else if (gridSize == 2)
				{
					medGrid[i][j] = new Tile(j, i, gridX, gridY, false);
				}
				else if (gridSize == 3)
				{
					largeGrid[i][j] = new Tile(j, i, gridX, gridY, false);
				}
				else
				{
					//error
				}

			}
		}
	}
}

Pathfinder::~Pathfinder()
{

}

void Pathfinder::Reset()
{
	ClearAll();
	int temp;
	switch (gridSize)
	{
	case(1):
		temp = sizeSmall;
		break;
	case(2):
		temp = sizeMed;
		break;
	case(3):
		temp = sizeLarge;
		break;
	default:
		break;
	}
	for (int i = 0; i < temp; i++)
	{
		for (int j = 0; j < temp; j++)
		{
			switch (gridSize)
			{
			case(1):
				smallGrid[i][j]->clear();
				break;
			case(2):
				medGrid[i][j]->clear();
				break;
			case(3):
				largeGrid[i][j]->clear();
				break;
			default:
				break;
			}
		}
	}
}

Tile* Pathfinder::GetNearestTile(CD_Vector pos)
{
	//map the position to the grid
	int tempi = (pos.x / cellW);
	int tempj = (pos.y / cellH);
	//if there is a remainder
	//if (((int)pos.x % Tile_WIDTH) > 0)
	//{
	//	tempi++;
	//}
	//if (((int)pos.y % Tile_HEIGHT) > 0)
	//{
	//	tempj++;
	//}
	//return the Tile at that position
	Tile* tile=new Tile();

	switch (gridSize)
	{
	case(1):
		tile = smallGrid[tempi][tempj];
		break;
	case(2):
		tile = medGrid[tempi][tempj];
		break;
	case(3):
		tile = largeGrid[tempi][tempj];
		break;
	default:
		break;
	}
	
	return tile;
}

std::vector<CD_Vector> Pathfinder::AStar(Tile* start, Tile* target)
{
	Reset();

	openSet.push_back(start);
	//while the openset is not empty
	while (openSet.size() > 0)
	{
		int smallest = 0;
		for (int i = 0; i < openSet.size(); i++)
		{
			if (openSet.at(i)->getF() < openSet.at(smallest)->getF())
			{
				smallest = i;
			}
		}

		Tile* current = openSet.at(smallest);

		//std::cout << current->GetGridPosition().x << " " << current->GetGridPosition().y << std::endl;

		//if the search has reached the target
		if (*current == *target)
		{
			std::vector<CD_Vector> path;
			path.push_back(current->GetOrigin());
			//std::cout << "Found target" << std::endl;
			//std::cout << "Path: " << current->GetGridPosition().x << " " << current->GetGridPosition().y << std::endl;
			//follow back through all the parent pointers to the first Tile
			//First Tile should be the only Tile in the 
			while (current->parent != nullptr)
			{
				current = current->parent;
				//std::cout << "Path: " << current->GetGridPosition().x << " " << current->GetGridPosition().y << std::endl;
				path.push_back(current->GetOrigin());
			}

			return path;
		}

		openSet.erase(openSet.begin() + smallest);
		closedSet.push_back(current);

		//for every neighbour of the current node
		for each(Tile* link in current->neighbours)
		{
			//if neighbour Tile is not in closedset and the Tile is active
			if (std::find(closedSet.begin(), closedSet.end(), link) == closedSet.end() && link->m_active == true)
			{
				int tempg = current->getG() + 1;
				//if neighbour is not in the openset(not evaluated yet)
				if (std::find(openSet.begin(), openSet.end(), link) == openSet.end())
				{
					link->parent = current; //may break here
					link->setG(tempg);
					openSet.push_back(link);
				}
				else
				{
					if (link->getG() > tempg)
					{
						link->parent = current;
						link->setG(tempg);
					}
				}

				link->setH(link->CalculateH(target->GetGridPosition()));
				link->setF(link->getG() + link->getH());
			}
		}
	}

	std::cout << "Unable to find path" << std::endl;
	std::vector<CD_Vector> err;
	return err;
}

void Pathfinder::AddLinks()
{
	int roomSize;
	switch (gridSize)
	{
	case(1):
		SmallLinks();
		break;
	case(2):
		MedLinks();
		break;
	case(3):
		LargeLinks();
		break;
	default:
		break;
	}
	//for (int i = 0; i < roomSize; i++)
	//{
	//	for (int j = 0; j < roomSize; j++)
	//	{
	//		//right
	//		if (temp[i][j]->GetGridPosition().x < roomSize - 1)
	//		{
	//			if (grid[i + 1][j]->m_active)
	//			{
	//				grid[i][j]->neighbours.emplace_back(grid[i + 1][j]);
	//			}
	//		}
	//		//bottom
	//		if (grid[i][j]->GetGridPosition().x < roomSize - 1)
	//		{
	//			if (grid[i][j + 1]->m_active)
	//				grid[i][j]->neighbours.emplace_back(grid[i][j + 1]);
	//		}
	//		//left
	//		if (grid[i][j]->GetGridPosition().x > 0)
	//		{
	//			if (grid[i - 1][j]->m_active)
	//				grid[i][j]->neighbours.emplace_back(grid[i - 1][j]);
	//		}
	//		//top
	//		if (grid[i][j]->GetGridPosition().y > 0)
	//		{
	//			if (grid[i][j - 1]->m_active)
	//				grid[i][j]->neighbours.emplace_back(grid[i][j - 1]);
	//		}
			////top-left
			//if (grid[i][j]->GetGridPosition().x > 0 && grid[i][j]->GetGridPosition().x > 0)
			//{
			//	if (grid[i - 1][j - 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i - 1][j - 1]);
			//}
			////bottom-left
			//if (grid[i][j]->GetGridPosition().x < ROOM_HEIGHT - 1 && grid[i][j]->GetGridPosition().y < ROOM_WIDTH - 2)
			//{
			//	if (grid[i + 1][j + 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i + 1][j + 1]);
			//}
			////top-right
			//if (grid[i][j]->GetGridPosition().x < ROOM_HEIGHT - 1 && grid[i][j]->GetGridPosition().y > 0)
			//{
			//	if (grid[i + 1][j - 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i + 1][j - 1]);
			//}
			////bottom-right
			//if (grid[i][j]->GetGridPosition().x > 0 && grid[i][j]->GetGridPosition().y < ROOM_HEIGHT - 1)
			//{
			//	if (grid[i - 1][j + 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i - 1][j + 1]);
			//}
//}
	//}
}

void Pathfinder::SmallLinks()
{
	for (int i = 0; i < sizeSmall; i++)
	{
		for (int j = 0; j < sizeSmall; j++)
		{
			//right
			if (smallGrid[i][j]->GetGridPosition().x < sizeSmall - 1)
			{
				if (smallGrid[i + 1][j]->m_active)
				{
					smallGrid[i][j]->neighbours.emplace_back(smallGrid[i + 1][j]);
				}
			}
			//bottom
			if (smallGrid[i][j]->GetGridPosition().x < sizeSmall - 1)
			{
				if (smallGrid[i][j + 1]->m_active)
					smallGrid[i][j]->neighbours.emplace_back(smallGrid[i][j + 1]);
			}
			//left
			if (smallGrid[i][j]->GetGridPosition().x > 0)
			{
				if (smallGrid[i - 1][j]->m_active)
					smallGrid[i][j]->neighbours.emplace_back(smallGrid[i - 1][j]);
			}
			//top
			if (smallGrid[i][j]->GetGridPosition().y > 0)
			{
				if (smallGrid[i][j - 1]->m_active)
					smallGrid[i][j]->neighbours.emplace_back(smallGrid[i][j - 1]);
			}
			////top-left
			//if (grid[i][j]->GetGridPosition().x > 0 && grid[i][j]->GetGridPosition().x > 0)
			//{
			//	if (grid[i - 1][j - 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i - 1][j - 1]);
			//}
			////bottom-left
			//if (grid[i][j]->GetGridPosition().x < ROOM_HEIGHT - 1 && grid[i][j]->GetGridPosition().y < ROOM_WIDTH - 2)
			//{
			//	if (grid[i + 1][j + 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i + 1][j + 1]);
			//}
			////top-right
			//if (grid[i][j]->GetGridPosition().x < ROOM_HEIGHT - 1 && grid[i][j]->GetGridPosition().y > 0)
			//{
			//	if (grid[i + 1][j - 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i + 1][j - 1]);
			//}
			////bottom-right
			//if (grid[i][j]->GetGridPosition().x > 0 && grid[i][j]->GetGridPosition().y < ROOM_HEIGHT - 1)
			//{
			//	if (grid[i - 1][j + 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i - 1][j + 1]);
			//}
		}
	}
}

void Pathfinder::MedLinks()
{
	for (int i = 0; i < sizeMed; i++)
	{
		for (int j = 0; j < sizeMed; j++)
		{
			//right
			if (medGrid[i][j]->GetGridPosition().x < sizeMed - 1)
			{
				if (medGrid[i + 1][j]->m_active)
				{
					medGrid[i][j]->neighbours.emplace_back(medGrid[i + 1][j]);
				}
			}
			//bottom
			if (medGrid[i][j]->GetGridPosition().x < sizeMed - 1)
			{
				if (medGrid[i][j + 1]->m_active)
					medGrid[i][j]->neighbours.emplace_back(medGrid[i][j + 1]);
			}
			//left
			if (medGrid[i][j]->GetGridPosition().x > 0)
			{
				if (medGrid[i - 1][j]->m_active)
					medGrid[i][j]->neighbours.emplace_back(medGrid[i - 1][j]);
			}
			//top
			if (medGrid[i][j]->GetGridPosition().y > 0)
			{
				if (medGrid[i][j - 1]->m_active)
					medGrid[i][j]->neighbours.emplace_back(medGrid[i][j - 1]);
			}
			////top-left
			//if (grid[i][j]->GetGridPosition().x > 0 && grid[i][j]->GetGridPosition().x > 0)
			//{
			//	if (grid[i - 1][j - 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i - 1][j - 1]);
			//}
			////bottom-left
			//if (grid[i][j]->GetGridPosition().x < ROOM_HEIGHT - 1 && grid[i][j]->GetGridPosition().y < ROOM_WIDTH - 2)
			//{
			//	if (grid[i + 1][j + 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i + 1][j + 1]);
			//}
			////top-right
			//if (grid[i][j]->GetGridPosition().x < ROOM_HEIGHT - 1 && grid[i][j]->GetGridPosition().y > 0)
			//{
			//	if (grid[i + 1][j - 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i + 1][j - 1]);
			//}
			////bottom-right
			//if (grid[i][j]->GetGridPosition().x > 0 && grid[i][j]->GetGridPosition().y < ROOM_HEIGHT - 1)
			//{
			//	if (grid[i - 1][j + 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i - 1][j + 1]);
			//}
		}
	}
}

void Pathfinder::LargeLinks()
{
	for (int i = 0; i < sizeLarge; i++)
	{
		for (int j = 0; j < sizeLarge; j++)
		{
			//right
			if (largeGrid[i][j]->GetGridPosition().x < sizeLarge - 1)
			{
				if (largeGrid[i + 1][j]->m_active)
				{
					largeGrid[i][j]->neighbours.emplace_back(largeGrid[i + 1][j]);
				}
			}
			//bottom
			if (largeGrid[i][j]->GetGridPosition().x < sizeLarge - 1)
			{
				if (largeGrid[i][j + 1]->m_active)
					largeGrid[i][j]->neighbours.emplace_back(largeGrid[i][j + 1]);
			}
			//left
			if (largeGrid[i][j]->GetGridPosition().x > 0)
			{
				if (largeGrid[i - 1][j]->m_active)
					largeGrid[i][j]->neighbours.emplace_back(largeGrid[i - 1][j]);
			}
			//top
			if (largeGrid[i][j]->GetGridPosition().y > 0)
			{
				if (largeGrid[i][j - 1]->m_active)
					largeGrid[i][j]->neighbours.emplace_back(largeGrid[i][j - 1]);
			}
			////top-left
			//if (grid[i][j]->GetGridPosition().x > 0 && grid[i][j]->GetGridPosition().x > 0)
			//{
			//	if (grid[i - 1][j - 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i - 1][j - 1]);
			//}
			////bottom-left
			//if (grid[i][j]->GetGridPosition().x < ROOM_HEIGHT - 1 && grid[i][j]->GetGridPosition().y < ROOM_WIDTH - 2)
			//{
			//	if (grid[i + 1][j + 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i + 1][j + 1]);
			//}
			////top-right
			//if (grid[i][j]->GetGridPosition().x < ROOM_HEIGHT - 1 && grid[i][j]->GetGridPosition().y > 0)
			//{
			//	if (grid[i + 1][j - 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i + 1][j - 1]);
			//}
			////bottom-right
			//if (grid[i][j]->GetGridPosition().x > 0 && grid[i][j]->GetGridPosition().y < ROOM_HEIGHT - 1)
			//{
			//	if (grid[i - 1][j + 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i - 1][j + 1]);
			//}
		}
	}
}
