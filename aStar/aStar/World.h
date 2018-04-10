//#pragma once
//#include <SDL.h>
//#include <SDL_image.h>
//#include <iostream>
////#include <TextureHandler.h>
//#include "LevelLoader.h"
//
///// <class>World</class>
///// <summary>
///// This class is used to draw rooms using a 2D
///// array. It will get the 2D array information
///// from the level loader.
///// </summary>
///// <author>Jack Keogh</author>
//
//using namespace std;
//
//class World
//{
//private:
//	vector<vector<int>> m_room;
//	TextureHandler * TextureManager;
//	SDL_Rect m_srcRect;
//	SDL_Rect m_dstRect;
//	vector<SDL_Rect> m_Walls;
//
//	int room;
//public:
//	/// <summary>
//	/// Default constructor method for world
//	/// </summary>
//	World();
//
//	/// <summary>
//	/// default destructor method for world
//	/// </summary>
//	~World();
//
//	/// <summary>
//	/// Initialiser method for world
//	/// </summary>
//	/// <param name="L">int variable to describe what level to initialise</param>
//	void init(int L);
//
//	/// <summary>
//	/// This method is used to loop through the loaded room and draw it
//	/// </summary>
//	/// <param name="Renderer">SDL_Renderer ptr used to render the world</param>
//	void RenderWorld(SDL_Renderer * Renderer);
//
//	/// <summary>
//	/// This method is used to get the position of all the walls.
//	/// </summary>
//	vector<SDL_Rect> getWalls() { 
//		return m_Walls; 
//	}
//
//	SDL_Rect getDimentions();
//	/// <summary>
//	/// Gets the current room number
//	/// </summary>
//	/// <returns>the current room number</returns>
//	int GetRoom();
//	/// <summary>
//	/// loads a specific room, re use of the init function code
//	/// </summary>
//	/// <param name="room">the room number to load</param>
//	void SetRoom(int tempRoom);
//};