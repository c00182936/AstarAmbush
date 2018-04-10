#include "Music.h"

Music::Music()
{
	string path = GameData::m_sounds["Track_01"];

	if (Mix_LoadMUS(path.c_str()))
	{
		m_tracks.push_back(Mix_LoadMUS(path.c_str()));
		cout << "Track_01 loaded successfully..." << endl;
	}

	path = GameData::m_sounds["Track_02"];

	if (Mix_LoadMUS(path.c_str()))
	{
		m_tracks.push_back(Mix_LoadMUS(path.c_str()));
		cout << "Track_02 loaded successfully..." << endl;
	}

	path = GameData::m_sounds["Track_03"];

	if (Mix_LoadMUS(path.c_str()))
	{
		m_tracks.push_back(Mix_LoadMUS(path.c_str()));
		cout << "Track_03 loaded successfully..." << endl;
	}

	path = GameData::m_sounds["Track_04"];

	if (Mix_LoadMUS(path.c_str()))
	{
		m_tracks.push_back(Mix_LoadMUS(path.c_str()));
		cout << "Track_04 loaded successfully..." << endl;
	}

	currentTrack = 0;

	Mix_PlayMusic(m_tracks.at(currentTrack), 0);

	if (Mix_PlayingMusic())
	{
		cout << "Playing music..." << endl;
	}
}

void Music::Update()
{
	if (Mix_PlayingMusic())
	{
		
	}
	else
	{
		cout << "----------------------------" << endl;
		cout << "----------------------------" << endl;
		cout << "----------------------------" << endl;
		cout << "-------Changing-Track-------" << endl;
		cout << "----------------------------" << endl;
		cout << "----------------------------" << endl;
		cout << "----------------------------" << endl;

		if (currentTrack < m_tracks.size() - 1)
		{
			currentTrack++;
		}
		else
		{
			currentTrack = 0;
		}

		cout << "Track #: " << currentTrack << endl << endl;

		Mix_PlayMusic(m_tracks.at(currentTrack), 0);
	}
}
