#pragma once
#include "ECS.h"
#include "SDL.h"
#include <map>
#include "ComponentList.h"
/// <class> InputComponent </class>
/// <summary>
/// This class inherits from the Component class.
/// The purpose of this class is to read inputs
/// from the keyboard and mouse
/// and make it easily accessable
/// </summary>
/// <author>Dermot Mac Conville</author>
class InputComponent : public Component
{

public:
	enum keyEnum
	{
		leftClick,
		rightClick,
		zero, one, two, three, four, five, six, seven, eight, nine, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, space, enter, keyUp, keyDown, keyLeft, keyRight, esc
	};
	InputComponent()
	{

	}
	/// <summary>
	/// This Method is to initialize the manager
	/// </summary>
	void init() override
	{
		m_Keys[keyEnum::a] = false;
		m_Keys[keyEnum::b] = false;
		m_Keys[keyEnum::c] = false;
		m_Keys[keyEnum::d] = false;
		m_Keys[keyEnum::e] = false;
		m_Keys[keyEnum::f] = false;
		m_Keys[keyEnum::g] = false;
		m_Keys[keyEnum::h] = false;
		m_Keys[keyEnum::i] = false;
		m_Keys[keyEnum::j] = false;
		m_Keys[keyEnum::k] = false;
		m_Keys[keyEnum::l] = false;
		m_Keys[keyEnum::m] = false;
		m_Keys[keyEnum::n] = false;
		m_Keys[keyEnum::o] = false;
		m_Keys[keyEnum::p] = false;
		m_Keys[keyEnum::q] = false;
		m_Keys[keyEnum::r] = false;
		m_Keys[keyEnum::s] = false;
		m_Keys[keyEnum::t] = false;
		m_Keys[keyEnum::u] = false;
		m_Keys[keyEnum::v] = false;
		m_Keys[keyEnum::w] = false;
		m_Keys[keyEnum::x] = false;
		m_Keys[keyEnum::y] = false;
		m_Keys[keyEnum::z] = false;
		m_Keys[keyEnum::zero] = false;
		m_Keys[keyEnum::one] = false;
		m_Keys[keyEnum::two] = false;
		m_Keys[keyEnum::three] = false;
		m_Keys[keyEnum::four] = false;
		m_Keys[keyEnum::five] = false;
		m_Keys[keyEnum::six] = false;
		m_Keys[keyEnum::seven] = false;
		m_Keys[keyEnum::eight] = false;
		m_Keys[keyEnum::nine] = false;
		m_Keys[keyEnum::space] = false;
		m_Keys[keyEnum::enter] = false;
		m_Keys[keyEnum::keyDown] = false;
		m_Keys[keyEnum::keyLeft] = false;
		m_Keys[keyEnum::keyRight] = false;
		m_Keys[keyEnum::keyRight] = false;
		m_Keys[keyEnum::space] = false;
		m_Keys[keyEnum::leftClick] = false;
		m_Keys[keyEnum::rightClick] = false;
		m_Keys[keyEnum::esc] = false;
		m_Keys[keyEnum::esc] = true;
		m_Keys[keyEnum::esc] = false;
	}

	/// <summary>
	/// This method searched for a needed key
	/// and returns if it's pressed down
	/// </summary>
	/// <param name="findKey">An enum of the key to be searched for</param>
	/// <returns>bool. true if pressed, false if not</returns>
	bool GetKeyDown(int findKey)
	{
		keyEnum tempKey = (keyEnum)findKey;
		auto search = m_Keys.find(tempKey);
		bool temp=search->second;
		return temp;
	}
	/// <summary>
	/// Gets the X position of the mouse
	/// </summary>
	/// <returns>the position on the x axis</returns>
	int GetMouseXPos()
	{
		return m_MousePos.x;
	}
	/// <summary>
	/// gets the Y position of the mouse
	/// </summary>
	/// <returns>the position on the Y axis</returns>
	int GetMouseYPos()
	{
		return m_MousePos.y;
	}
	/// <summary>
	/// gets the mouse position as an SDL_Point
	/// </summary>
	/// <returns>the mouse position as an SDL_Point</returns>
	SDL_Point *GetMousePos()
	{
		return &m_MousePos;
	}
	private:
		std::map<keyEnum, bool> m_Keys;
		SDL_Point m_MousePos;



};