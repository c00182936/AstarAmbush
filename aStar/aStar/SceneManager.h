//Author: John McGrath
#pragma once

//Enums to represent each gamestate
enum GameStates
{
	GameState = 0,
	MainMenuState = 1,
	MultiPlayerState = 2,
	OptionsState = 3,
	UpgradesMenuState = 4,
	RebindControlsState = 5,
	SelectCharacterState = 6
};

class SceneManager
{
public:
	/// <summary>
	/// Getter method for the current scene
	/// </summary>
	int* getCurrentScene() { return &m_currentScreen; }

	/// <summary>
	/// Setter method for the current scene
	/// </summary>
	void setCurrentScene(int newScene) { m_currentScreen = newScene; }

private:
	//Value to represent the intial scene on start up
	const int START_UP_SCENE = GameStates::MainMenuState;

	//The current scene 
	int m_currentScreen = START_UP_SCENE;
};
