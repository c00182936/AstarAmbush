#include "LevelLoader.h"


std::map<std::string, std::string> GameData::m_sounds;
std::vector<std::vector<std::vector<int>>> GameData::m_roomLayout;
std::map<std::string, std::string> GameData::m_sprites;
std::vector<GameData::Wave> GameData::m_waveLayout;
std::string GameData::fontFile;
	
////////////////////////////////////////////////////////////
LevelLoader::LevelLoader(std::string const & filename)
{

	loadJSONData(filename);
	m_value = JSON::Parse(m_JSONData.c_str());
	if (NULL == m_value)
	{
		std::string s("Could not parse json in " + filename);
		throw std::exception(s.c_str());
	}
}

////////////////////////////////////////////////////////////
LevelLoader::~LevelLoader() {
	delete m_value;
}

////////////////////////////////////////////////////////////
void LevelLoader::load(std::string const & filename)
{
	loadJSONData(filename);
	m_value = JSON::Parse(m_JSONData.c_str());
	if (NULL == m_value)
	{
		std::string s("Could not parse json in " + filename);
		throw std::exception(s.c_str());
	}
	
}

////////////////////////////////////////////////////////////
void LevelLoader::loadJSONData(std::string const & filename)
{
	m_JSONData.clear();

	// Loads all the data in the file into a std::string.
	std::ifstream myfile(filename);
	std::string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			m_JSONData.append(line);
		}
		myfile.close();
	}
	else
	{
		std::string errorMessage = "Could not open " + filename + " exiting!";
		std::cout << "Could not open " + filename + " exiting!" << std::endl;
		throw std::exception(errorMessage.c_str());
	}
}

////////////////////////////////////////////////////////////
JSONObject LevelLoader::getTopLevelJSONObject() {
	// Retrieve the main (root) object
	JSONObject root;

	if (m_value->IsObject() == false)
	{
		throw std::exception("Problem with root element in json file, exiting");
	}
	root = m_value->AsObject();

	return root;
}

////////////////////////////////////////////////////////////
std::string LevelLoader::wStringToString(std::wstring const & wstr)
{
	std::string s(wstr.begin(), wstr.end());
	return s;
}

void LevelLoader::LoadAll()
{
	loadRoomData();
	loadSounds();
	loadSpriteNames();
	loadWaveData();
}

void LevelLoader::loadSounds()
{
	m_gameData.m_sounds.clear();
	// Retrieve the main (root) object
		JSONObject root = getTopLevelJSONObject();
	
		JSONObject gameData = root[L"general_game_data"]->AsObject();
		JSONArray soundArray = gameData[L"sfx"]->AsArray();
		for (unsigned int i = 0; i < soundArray.size(); i++) 
		{
			JSONObject object = soundArray[i]->AsObject();
			m_gameData.m_sounds.insert(std::pair<std::string, std::string>(
				wStringToString(object[L"name"]->AsString()),
				wStringToString(object[L"file"]->AsString())));
		}

}

void LevelLoader::loadSpriteNames()
{
	m_gameData.m_sprites.clear();
	// Retrieve the main (root) object
	JSONObject root = getTopLevelJSONObject();

	JSONObject gameData = root[L"general_game_data"]->AsObject();
	JSONObject globalVariables = gameData[L"global_variables"]->AsObject();
	JSONArray spriteArray = globalVariables[L"sprites"]->AsArray();
	for (unsigned int i = 0; i < spriteArray.size(); i++)
	{
		JSONObject object = spriteArray[i]->AsObject();

		GameData::m_sprites.insert(std::pair<std::string, std::string>(
			wStringToString(object[L"name"]->AsString()),
			wStringToString(object[L"file"]->AsString())));
	}

}

void LevelLoader::loadTextFont()
{
	m_gameData.m_sounds.clear();
	// Retrieve the main (root) object
	JSONObject root = getTopLevelJSONObject();

	JSONObject gameData = root[L"general_game_data"]->AsObject();
	JSONObject globalVariables = gameData[L"global_variables"]->AsObject();
	GameData::fontFile = wStringToString(globalVariables[L"font_file"]->AsString());
}

void LevelLoader::loadWaveData()
{
	m_gameData.m_waveLayout.clear();

	JSONObject root = getTopLevelJSONObject();

	JSONArray waveData = root[L"wave_layouts"]->AsArray();

	//for every item in wave data
	for (unsigned int i = 0; i < waveData.size(); i++)
	{
		//go into the object and get the array wave
		JSONObject object = waveData.at(i)->AsObject();
		//add an wave object to m_wavelayout
		GameData::m_waveLayout.push_back(GameData::Wave(object[L"dog"]->AsNumber(),
			object[L"pistol"]->AsNumber(), object[L"engineer"]->AsNumber(), 
			object[L"goo"]->AsNumber(), object[L"juggernaut"]->AsNumber(), 
			object[L"tank"]->AsNumber()));
	}
}

void LevelLoader::loadRoomData()
{

	m_gameData.m_roomLayout.clear();

	JSONObject root = getTopLevelJSONObject();

	JSONArray roomData = root[L"room_layouts"]->AsArray();
	//for every item in room data
	for (unsigned int i = 0; i < roomData.size(); i++)
	{
		//go into the object and get the array room
		JSONObject object = roomData.at(i)->AsObject();
		JSONArray room = object[L"room"]->AsArray();
		//add an empty array to m_roomLayout
		GameData::m_roomLayout.push_back(std::vector<std::vector<int>>());
		//fill the new empty array with what is in room
		for (int e = 0; e < room.size(); e++)
		{
			JSONObject row = room.at(e)->AsObject();
			JSONArray rowData = row[L"row"]->AsArray();
			//add an empty array as row
			GameData::m_roomLayout.at(i).push_back(std::vector<int>());
			//fill the empty array with row data
			for (int j = 0; j < rowData.size(); j++)
			{
				GameData::m_roomLayout.at(i).at(e).push_back(rowData.at(j)->AsNumber());
			}
		}
	}

}