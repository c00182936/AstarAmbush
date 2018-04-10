#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>
#include <vector>
#include <map>

/// <summary>
/// Object that hold static variables used  
/// to store variables loaded in by LevelLoader
/// </summary>
class GameData {
public:

	/// <summary>
	/// contains information as to the number of enemies of
	/// different types are to be spawned in a wave
	/// </summary>
	struct Wave
	{
		int dog;
		int pistol;
		int engineeer;
		int slime;
		int juggernaut;
		int tank;
		Wave(int d, int p, int e, int s, int j, int t) :
			dog(d), pistol(p), engineeer(e), slime(s), juggernaut(j), tank(t)
		{
		}
	};
	//font file for on-screen text
	static std::string fontFile;

	//sprite file names.
	static std::map<std::string, std::string> m_sprites;

	//sound file names
	static std::map<std::string, std::string> m_sounds;

	//level data
	static std::vector<Wave> m_waveLayout;
	static std::vector<std::vector<std::vector<int>>> m_roomLayout;

};
#endif