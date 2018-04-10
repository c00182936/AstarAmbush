#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_mixer.h>
#include "GameData.h"

/// <class>Music</class>
/// <summary>
/// This class will be used to handle
/// background music in the game.
/// </summary>
/// <author>Jack Keogh</author>

using namespace std;

class Music
{
private:
	vector<Mix_Music*> m_tracks;
	int currentTrack;

public:
	/// <summary>
	/// Default constructor loads information from
	/// GameData and inserts it into vector.
	/// </summary>
	Music();

	/// <summary>
	/// Update loop
	/// </summary>
	void Update();
};