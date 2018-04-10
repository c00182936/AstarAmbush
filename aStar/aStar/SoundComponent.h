#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include "stdafx.h"
#include "ECS.h"

/// <class> SoundComponent </class>
/// <summary>
/// This class inherits from the Component class.
/// The purpose of this class is to load in the relevant
/// sound files and play the correct sound file when
/// the play method is called.
/// </summary>
/// <author>Jack Keogh</author>
/// 
/// 
class SoundComponent : public Component
{
public:
	SoundComponent();
	~SoundComponent();

	/// <summary>
	/// This method is used to load in sounds to a map storage.
	/// </summary>
	/// <param name="Name">string variable refers to the name of the sound file and the name it will be stored as.</param>
	/// <param name="Vol">int variable to determine the preferred sound.</param>
	void AddSound(string Name, int Vol = 10);

	/// <summary>
	/// This method will play the chosen sound only once, it will not loop.
	/// </summary>
	/// <param name="Name">string variable to select the chosen sound </param>
	void Play(string Name, int channel = -1, int loop=0);

private:
	map<string, Mix_Chunk*> m_Sounds;
};