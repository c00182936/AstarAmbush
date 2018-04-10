#ifndef LEVElLOADER_H
#define LEVElLOADER_H

#include "GameData.h"
#include "JSON.h"
#include <fstream>
#include <iostream>
////////////////////////////////////////////////////////////
/// \brief A class to load all the configuration data
///        required by the game. 
///
////////////////////////////////////////////////////////////
class LevelLoader {
public:
	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// This constructor initialises the JSON parser and loads
	/// the menu and game level data.
	///
	/// \param filename The path and filename of the JSON file.
	///
	////////////////////////////////////////////////////////////
	LevelLoader(std::string const & filename);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	/// Frees resources acquired by the JSON parser.
	///
	////////////////////////////////////////////////////////////
	~LevelLoader();

	////////////////////////////////////////////////////////////
	/// \brief Loads the JSON data from the specified file.
	///
	/// \param filename The path and filename of the JSON file.
	///
	////////////////////////////////////////////////////////////
	void load(std::string const & filename);

	/// <summary>
	/// Loads all available variables from the json
	/// (i.e. Sprites, music, level layout)
	/// </summary>
	void LoadAll();

private:
	JSONValue *m_value;
	std::string m_JSONData;
	GameData m_gameData;

	void loadJSONData(std::string const & filename);

	void loadRoomData();
	void loadSounds();
	void loadSpriteNames();
	void loadWaveData();
	void loadTextFont();

	// Utility methods.
	JSONObject getTopLevelJSONObject();
	std::string wStringToString(std::wstring const & wstr);

};

#endif