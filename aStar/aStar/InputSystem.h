#pragma once
#include "SystemTemplate.h"
#include "SDL.h"
#include <map>
#include "InputComponent.h"
#include "Observer.h"
#include "ObserverList.h"
#include <vector>
#include "ECS.h"
//#include "BulletHandler.h"
enum keyEnum
{
	leftClick,
	rightClick,
	zero, one, two, three, four, five, six, seven, eight, nine, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, space, enter, keyUp, keyDown, keyLeft, keyRight, esc
};
class InputSystem:System
{

public:
	int test = 0;
	InputSystem() { up = w; down = s; left = a; right = d; fire = leftClick; initKeyMap(); m_removed = false; };
	~InputSystem()override {};

	bool getRemoved() override { return m_removed; };
	void setRemove(bool value) override { m_removed = value; };

	/// <summary>
	/// update loop, calls functions to handle input and response
	/// </summary>
	void update() override {

		refresh();

		checkKeyPresses();
		rotatePlayer();
		/// <summary>
		/// Logic should be in a .cpp file not a .h file.
		/// </summary>

		for (int i = 0; i < m_entities.size(); i++)
		{
			MovementComponent *tempMove = &m_entities[i]->getComponent<MovementComponent>();

			auto search = m_Keys.find(up);
			if (search->second)
			{
				tempMove->setUp(true);
				//std::cout << "up pressed" << std::endl;
			}
			else
			{
				tempMove->setUp(false);
			}
			search = m_Keys.find(down);
			if (search->second)
			{
				tempMove->setDown(true);
				//std::cout << "down pressed" << std::endl;
			}
			else
			{
				tempMove->setDown(false);
			}
			search = m_Keys.find(left);
			if (search->second)
			{
				tempMove->setLeft(true);
				//std::cout << "left pressed" << std::endl;
			}
			else
			{
				tempMove->setLeft(false);
			}
			search = m_Keys.find(right);
			if (search->second)
			{
				tempMove->setRight(true);
				//std::cout << "right pressed" << std::endl;
			}
			else
			{
				tempMove->setRight(false);
			}






			search = m_Keys.find(fire);

			//If the mouse is clicked
			if (search->second)
			{
				m_entities.at(i)->getComponent<AnimationComponent>().fire();
				m_entities.at(i)->getComponent<SoundComponent>().Play("Gun");
				//If the Option is Hold
				if (m_toggleHoldFire)
				{
					//m_BulletHandler->SetFiring(true);
				}
				//If option is toggle
				else if ((!m_toggleHoldFire) && (!m_leftClickOnce))
				{
					m_leftClickOnce = true;
					m_keepFiring = !m_keepFiring;
					/*if (m_keepFiring)
					{
						m_BulletHandler->SetFiring(true);
					}
					else
					{
						m_BulletHandler->SetFiring(false);
					}*/
				}
			}
			//If the click is released
			else
			{
				//If the Option is Hold
				if (m_toggleHoldFire)
				{
					//m_BulletHandler->SetFiring(false);
				}
				//If option is toggle
				if (!m_toggleHoldFire)
				{
					if (m_keepFiring)
					{
						//m_BulletHandler->SetFiring(true);
					}
					else
					{
						//m_BulletHandler->SetFiring(false);
					}
				}
				if ((!m_toggleHoldFire) && (m_leftClickOnce))
				{
					m_leftClickOnce = false;
				}
			}
		}
	};





	/// <summary>
	/// Adds an entity to the m_entity list
	/// Should only be used for entities with controls
	/// </summary>
	/// <param name="ent">pointer to the entity instance</param>
	void addEntity(Entity *ent) { 
		m_entities.push_back(ent);  
		
	};
	/// <summary>
	/// recieves a pointer for the bullet handler object
	/// for use in creating bullets
	/// </summary>
	/// <param name="bull">pointer to the bulletHandler instance</param>
	//void SetBulletHandler(BulletHandler *bull)
	//{
	//	m_BulletHandler = bull;
	//}
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

	bool GetToggleHold() { return m_toggleHoldFire; }
	void SetToggleHold(bool newVal) { m_toggleHoldFire = newVal; }

	/// <summary>
	/// rebinds an action to a new key
	/// </summary>
	/// <param name="Action">integer to rebind. 1=up,2=down,3=left,4=right,5=Fire</param>
	/// <param name="newKey">the new key to bind the action to</param>
	void RebindControls(int Action, keyEnum newKey)
	{
		switch (Action)
		{
		case(1):
			up = newKey;
			break;
		case(2):
			down = newKey;
			break;
		case(3):
			left = newKey;
			break;
		case(4):
			right = newKey;
			break;
		case(5):
			fire = newKey;
			break;
		default:
			break;
		}
	}

	keyEnum GetPressedKey()
	{
		for (int i = 0; i < m_Keys.size(); i++)
		{
			for (std::map<keyEnum, bool>::iterator temp = m_Keys.begin(); temp != m_Keys.end(); ++temp)
			{
				if (temp->first != keyEnum::leftClick)
				{
					if (temp->second == true)
					{
						std::cout << "Key Hit" << std::endl;
						return temp->first;
						break;
					}
				}

			}
		}
	}
	bool getKeyDown(keyEnum key)
	{
		auto search = m_Keys.find(key);
		return search->second;
	}
	/// <summary>
	/// Checks all key inputs and stores mouse position
	/// </summary>
	void checkKeyPresses() {
		//resets all m_Keys to a down state

		/*for (auto iter = m_Keys.begin(); iter != m_Keys.end(); ++iter)
		{
		iter->second = false;
		}*/


		SDL_Event e;

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{

				case SDLK_0:
					m_Keys[keyEnum::zero] = true;
					break;
				case SDLK_1:
					m_Keys[keyEnum::one] = true;
					break;
				case SDLK_2:
					m_Keys[keyEnum::two] = true;
					break;
				case SDLK_3:
					m_Keys[keyEnum::three] = true;
					break;
				case SDLK_4:
					m_Keys[keyEnum::four] = true;
					break;
				case SDLK_5:
					m_Keys[keyEnum::five] = true;
					break;
				case SDLK_6:
					m_Keys[keyEnum::six] = true;
					break;
				case SDLK_7:
					m_Keys[keyEnum::seven] = true;
					break;
				case SDLK_8:
					m_Keys[keyEnum::eight] = true;
					break;
				case SDLK_9:
					m_Keys[keyEnum::nine] = true;
					break;
				case SDLK_a:
					m_Keys[keyEnum::a] = true;
					break;
				case SDLK_b:
					m_Keys[keyEnum::b] = true;
					break;
				case SDLK_c:
					m_Keys[keyEnum::c] = true;
					break;
				case SDLK_d:
					m_Keys[keyEnum::d] = true;
					break;
				case SDLK_e:
					m_Keys[keyEnum::e] = true;
					break;
				case SDLK_f:
					m_Keys[keyEnum::f] = true;
					break;
				case SDLK_g:
					m_Keys[keyEnum::g] = true;
					break;
				case SDLK_h:
					m_Keys[keyEnum::h] = true;
					break;
				case SDLK_i:
					m_Keys[keyEnum::i] = true;
					break;
				case SDLK_j:
					m_Keys[keyEnum::j] = true;
					break;
				case SDLK_k:
					m_Keys[keyEnum::k] = true;
					break;
				case SDLK_l:
					m_Keys[keyEnum::l] = true;
					break;
				case SDLK_m:
					m_Keys[keyEnum::m] = true;
					break;
				case SDLK_n:
					m_Keys[keyEnum::n] = true;
					break;
				case SDLK_o:
					m_Keys[keyEnum::o] = true;
					break;
				case SDLK_p:
					m_Keys[keyEnum::p] = true;
					break;
				case SDLK_q:
					m_Keys[keyEnum::q] = true;
					break;
				case SDLK_r:
					m_Keys[keyEnum::r] = true;
					break;
				case SDLK_s:
					m_Keys[keyEnum::s] = true;
					break;
				case SDLK_t:
					m_Keys[keyEnum::t] = true;
					break;
				case SDLK_u:
					m_Keys[keyEnum::u] = true;
					break;
				case SDLK_v:
					m_Keys[keyEnum::v] = true;
					break;
				case SDLK_w:
					m_Keys[keyEnum::w] = true;
					break;
				case SDLK_x:
					m_Keys[keyEnum::x] = true;
					break;
				case SDLK_y:
					m_Keys[keyEnum::y] = true;
					break;
				case SDLK_z:
					m_Keys[keyEnum::z] = true;
					break;
				case SDLK_SPACE:
					m_Keys[keyEnum::seven] = true;
					break;
				case SDLK_BACKSPACE:
					m_Keys[keyEnum::enter] = true;
					break;
				case SDLK_UP:
					m_Keys[keyEnum::keyUp] = true;
					break;
				case SDLK_DOWN:
					m_Keys[keyEnum::keyDown] = true;
					std::cout << "down pressed" << std::endl;
					break;
				case SDLK_LEFT:
					m_Keys[keyEnum::keyLeft] = true;
					break;
				case SDLK_RIGHT:
					m_Keys[keyEnum::keyRight] = true;
					break;
				case SDLK_ESCAPE:
					m_Keys[keyEnum::esc] = true;
					break;
				default:
					break;

				}
			}
			if (e.type == SDL_KEYUP)
			{
				switch (e.key.keysym.sym)
				{

				case SDLK_0:
					m_Keys[keyEnum::zero] = false;
					break;
				case SDLK_1:
					m_Keys[keyEnum::one] = false;
					break;
				case SDLK_2:
					m_Keys[keyEnum::two] = false;
					break;
				case SDLK_3:
					m_Keys[keyEnum::three] = false;
					break;
				case SDLK_4:
					m_Keys[keyEnum::four] = false;
					break;
				case SDLK_5:
					m_Keys[keyEnum::five] = false;
					break;
				case SDLK_6:
					m_Keys[keyEnum::six] = false;
					break;
				case SDLK_7:
					m_Keys[keyEnum::seven] = false;
					break;
				case SDLK_8:
					m_Keys[keyEnum::eight] = false;
					break;
				case SDLK_9:
					m_Keys[keyEnum::nine] = false;
					break;
				case SDLK_a:
					m_Keys[keyEnum::a] = false;
					break;
				case SDLK_b:
					m_Keys[keyEnum::b] = false;
					break;
				case SDLK_c:
					m_Keys[keyEnum::c] = false;
					break;
				case SDLK_d:
					m_Keys[keyEnum::d] = false;
					break;
				case SDLK_e:
					m_Keys[keyEnum::e] = false;
					break;
				case SDLK_f:
					m_Keys[keyEnum::f] = false;
					break;
				case SDLK_g:
					m_Keys[keyEnum::g] = false;
					break;
				case SDLK_h:
					m_Keys[keyEnum::h] = false;
					break;
				case SDLK_i:
					m_Keys[keyEnum::i] = false;
					break;
				case SDLK_j:
					m_Keys[keyEnum::j] = false;
					break;
				case SDLK_k:
					m_Keys[keyEnum::k] = false;
					break;
				case SDLK_l:
					m_Keys[keyEnum::l] = false;
					break;
				case SDLK_m:
					m_Keys[keyEnum::m] = false;
					break;
				case SDLK_n:
					m_Keys[keyEnum::n] = false;
					break;
				case SDLK_o:
					m_Keys[keyEnum::o] = false;
					break;
				case SDLK_p:
					m_Keys[keyEnum::p] = false;
					break;
				case SDLK_q:
					m_Keys[keyEnum::q] = false;
					break;
				case SDLK_r:
					m_Keys[keyEnum::r] = false;
					break;
				case SDLK_s:
					m_Keys[keyEnum::s] = false;
					break;
				case SDLK_t:
					m_Keys[keyEnum::t] = false;
					break;
				case SDLK_u:
					m_Keys[keyEnum::u] = false;
					break;
				case SDLK_v:
					m_Keys[keyEnum::v] = false;
					break;
				case SDLK_w:
					m_Keys[keyEnum::w] = false;
					break;
				case SDLK_x:
					m_Keys[keyEnum::x] = false;
					break;
				case SDLK_y:
					m_Keys[keyEnum::y] = false;
					break;
				case SDLK_z:
					m_Keys[keyEnum::z] = false;
					break;
				case SDLK_SPACE:
					m_Keys[keyEnum::seven] = false;
					break;
				case SDLK_BACKSPACE:
					m_Keys[keyEnum::enter] = false;
					break;
				case SDLK_UP:
					m_Keys[keyEnum::keyUp] = false;
					break;
				case SDLK_DOWN:
					m_Keys[keyEnum::keyDown] = false;
					std::cout << "down pressed" << std::endl;
					break;
				case SDLK_LEFT:
					m_Keys[keyEnum::keyLeft] = false;
					break;
				case SDLK_RIGHT:
					m_Keys[keyEnum::keyRight] = false;
					break;
				case SDLK_ESCAPE:
					m_Keys[keyEnum::esc] = false;
					break;
				default:
					break;

				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				switch (e.button.button)
				{

				case SDL_BUTTON_LEFT:
					m_Keys[keyEnum::leftClick] = true;
					break;
				case SDL_BUTTON_RIGHT:
					m_Keys[keyEnum::rightClick] = true;
					break;
				default:
					break;
				}
			}
			if (e.type == SDL_MOUSEBUTTONUP) {
				switch (e.button.button)
				{
				case SDL_BUTTON_LEFT:
					m_Keys[keyEnum::leftClick] = false;
					break;
				case SDL_BUTTON_RIGHT:
					m_Keys[keyEnum::rightClick] = false;
					break;
				default:
					break;
				}
			}
		}
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				std::cout << "key down:";
				switch (e.key.keysym.sym)
				{

				case SDLK_UP:
					std::cout << " up ";
					break;
				case SDLK_1:
					std::cout << " 1 ";
					break;
				case SDLK_2:
					std::cout << " 2 ";
					break;
				case SDLK_3:
					std::cout << " 3 ";
					break;
				default:
					break;
				}

				std::cout << " " << std::endl;
			}
		}

		/*if (SDL_MOUSEBUTTONDOWN) {
		switch (e.button.button)
		{

		case SDL_BUTTON_LEFT:
		m_Keys[keyEnum::leftClick] = true;
		break;
		case SDL_BUTTON_RIGHT:
		m_Keys[keyEnum::rightClick] = true;
		break;
		default:
		break;
		}
		}*/
		//m_owner->getComponent<InputObserver>().onNotify(BUTTON_CLICKED);
		//m_owner->getComponent<InputObserver>().onNotify(BUTTON_CLICKED);

		//m_owner->getComponent<InputObserver>().testCall();
		//obsv = m_owner->getComponent<InputObserver>();
		//std::cout << m_owner->getComponent<InputObserver>().a << std::endl;
		//m_MousePos.x = e.button.x;
		//m_MousePos.y = e.button.y;
		SDL_GetMouseState(&m_MousePos.x, &m_MousePos.y);
		
	}
private:
	//BulletHandler * m_BulletHandler = &BulletHandler();
	keyEnum up, down, left, right, fire;
	std::map<keyEnum, bool> m_Keys;
	SDL_Point m_MousePos;
	SDL_Point m_playPos;
	bool m_toggleHoldFire = true;
	bool m_keepFiring = false;
	bool m_leftClickOnce = false;
	/// <summary>
	/// initializes all the key values to false on init
	/// </summary>
	void initKeyMap()
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
		m_Keys[keyEnum::keyUp] = false;
		m_Keys[keyEnum::space] = false;
		m_Keys[keyEnum::leftClick] = false;
		m_Keys[keyEnum::rightClick] = false;
		m_Keys[keyEnum::esc] = false;
	}
	
	void rotatePlayer()
	{

		float rotation, tempX, tempY;
		for (int i = 0; i < m_entities.size(); i++)
		{
			tempX = m_MousePos.x;
			tempY =m_MousePos.y;
			tempX -= m_entities[i]->getComponent<PositionComponent>().GetXPosition();
			tempY -= m_entities[i]->getComponent<PositionComponent>().GetYPosition();
			rotation = atan2(tempX, -tempY);

			//std::cout << "rot: " << rotation << std::endl;
			rotation = rotation * 180 / M_PI;
			//std::cout << "rot: " << rotation << std::endl;
			m_entities[i]->getComponent<PositionComponent>().setRotation(rotation);
		}
	}

	//InputObserver obsv;
};
