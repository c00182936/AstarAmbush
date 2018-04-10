#pragma once
#include <iostream>
#include "SystemTemplate.h"
#include "ECS.h"
#include "SDL.h"
//#include "BulletHandler.h"
#include "MovementComponent.h"


using namespace std;

class Collisions : public System
{
public:
	Collisions()
	{
		m_removed = false;
	};

	bool getRemoved() override { return m_removed; };
	void setRemove(bool value) override { m_removed = value; };

	void addEntity(Entity * ent)
	{
		m_entities.emplace_back(ent);
	}
	
	void update() override
	{
		refresh();

		for (Entity * A : m_entities)
		{
			if (A == nullptr)
			{
				break;
			}

			for (Entity * B : m_entities)
			{
				if (B == nullptr)
				{
					break;
				}

				if (A == B)
				{
					break;
				}
				
				if ((A->hasGroup(Groups::PlayerGroup) && B->hasGroup(Groups::PlayerGroup)) ||
					(B->hasGroup(Groups::EnemyGroup) && B->hasGroup(Groups::EnemyGroup)))
				{
					break;
				}
				
				SDL_Rect AA = A->getComponent<SpriteComponent>().getScreenCoords();
				SDL_Rect BB = B->getComponent<SpriteComponent>().getScreenCoords();

				if (A->hasGroup(Groups::EnemyGroup))
				{
					if (Collisions::AABB(AA, BB))
					{
						//Bounce back AI entity
						CD_Vector vel = A->getComponent<MovementComponent>().getVelocity();
						vel *= -2.0f;
						A->getComponent<MovementComponent>().setVelocity(vel);

						// Calculate Damage on player entity
						float damage = DamageCal(A->getComponent<StatComponent>().getPower(), B->getComponent<StatComponent>().getDefense());
						B->getComponent<StatComponent>().setHealth(B->getComponent<StatComponent>().getHealth() - damage);
					}
				}
			}
		}
	}

	void WallCollision(vector<SDL_Rect> Walls)
	{
		for (Entity * e : m_entities)
		{
			// Get entity rectangle
			SDL_Rect EntRect = e->getComponent<SpriteComponent>().getScreenCoords();
			CD_Vector velocity = e->getComponent<MovementComponent>().getVelocity();

			SDL_Rect Left = EntRect;
			Left.x -= 4;

			SDL_Rect Up = EntRect;
			Up.y -= 4;

			SDL_Rect Right = EntRect;
			Right.x += 4;

			SDL_Rect Down = EntRect;
			Down.y += 4;

			// Allow only one collision
			//bool collided = false;

			// Loop through the walls
			for (size_t i = 0; i < Walls.size(); i++)
			{
				// Get the walls Rectangle
				SDL_Rect WallRect = Walls.at(i);

				// Check Collision using AABB
				if (AABB(Left, WallRect))
				{
					e->getComponent<PositionComponent>().setPosition(CD_Vector(EntRect.x + 4, EntRect.y));
				}

				if (AABB(Up, WallRect))
				{
					e->getComponent<PositionComponent>().setPosition(CD_Vector(EntRect.x, EntRect.y + 4));
				}

				if (AABB(Right, WallRect))
				{
					e->getComponent<PositionComponent>().setPosition(CD_Vector(EntRect.x - 4, EntRect.y));
				}

				if (AABB(Down, WallRect))
				{
					e->getComponent<PositionComponent>().setPosition(CD_Vector(EntRect.x, EntRect.y - 4));
				}
			}
		}
	}

	static bool BulletWall(SDL_Rect bullet, vector<SDL_Rect> Walls)
	{
		for (size_t i = 0; i < Walls.size(); i++)
		{
			// Get the walls Rectangle
			SDL_Rect WallRect = Walls.at(i);

			if (AABB(bullet, WallRect))
			{
				return true;
			}
		}

		return false;
	}

	//void BulletCollision(Bullet * bullet, string type)
	//{
	///*	SDL_Rect BulletCollider = bullet->m_dst;

	//	for (Entity * e : m_entities)
	//	{
	//		bool collision = false;
	//		SDL_Rect EntCollider = e->getComponent<SpriteComponent>().getScreenCoords();

	//		if (AABB(BulletCollider, EntCollider))
	//		{
	//			if (type == "PlayerBullet")
	//			{
	//				if (e->hasGroup(Groups::EnemyGroup))
	//				{
	//					collision = true;
	//				}
	//			}
	//			else
	//			{
	//				if (e->hasGroup(Groups::PlayerGroup))
	//				{
	//					collision = true;
	//				}
	//			}
	//		}

	//		if (collision)
	//		{
	//			bullet->Reset();
	//			float damage = DamageCal(bullet->calculateDamage(), e->getComponent<StatComponent>().getDefense());
	//			e->getComponent<StatComponent>().setHealth(e->getComponent<StatComponent>().getHealth() - damage);
	//		}
	//	}*/
	//}

	float DamageCal(float power, float defence)
	{
		float Damage;

		Damage = (power * 4.0f) / defence;

		return Damage;
	}

	static bool AABB(SDL_Rect obj1, SDL_Rect obj2)
	{
		if ((obj1.x >= obj2.x && obj1.x <= obj2.x + obj2.w) ||
			(obj1.x + obj1.w >= obj2.x && obj1.x + obj1.w <= obj2.x + obj2.w))
		{
			if ((obj1.y >= obj2.y && obj1.y <= obj2.y + obj2.h) ||
				(obj1.y + obj1.h >= obj2.y && obj1.y + obj1.h <= obj2.y + obj2.h))
			{
				return true;
			}
		}

		return false;
	}

	/// <summary>
	/// Checks for collisions between two position componants
	/// </summary>
	/// <param name="b1">Componant 1</param>
	/// <param name="b2">Componant 2</param>
	/// <returns>Returns true if they are intersecting and false otherwise</returns>
	static bool collisionDetection(PositionComponent b1, PositionComponent b2)
	{
		//perform box collision detection first. If the bounding boxes do not collide then they definitely do not intersect, return false
		//if the bounding boxes do collide do circle collision detection if needed. Saves time on processor intensive circle collision
		if (!((b1.GetPosition().x + b1.GetWidth()) >= b2.GetPosition().x &&
			b1.GetPosition().x <= (b2.GetPosition().x + b2.GetWidth()) &&
			(b1.GetPosition().y + b1.GetHeight()) >= b2.GetPosition().y &&
			b1.GetPosition().y <= (b2.GetPosition().y + b2.GetHeight())))
		{
			return false;
		}
		else
		{
			//if the two objects are boxes we have already done box collision checking so return true
			if (b1.GetIsCircle() == false && b2.GetIsCircle() == false)
			{
				return true;
			}
			//if both are circles check distance between centres 
			else if (b1.GetIsCircle() == true && b2.GetIsCircle() == true)
			{
				//if the distance is less than both radius' combined, they intersect
				//standard dist formula: sqrt((x2-x1)^2 + (y2-y1)^2)
				if (sqrt((b2.GetCentre().x - b1.GetCentre().x)*(b2.GetCentre().x - b1.GetCentre().x) +
					(b2.GetCentre().y - b1.GetCentre().y)*(b2.GetCentre().y - b1.GetCentre().y)
					<= (b1.GetRadius() + b2.GetRadius())))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			//last case scenario is 1 box and 1 circle
			else
			{
				PositionComponent circleComp;
				PositionComponent boxComp;
				//this checks which object is a circle and assigns that to circle comp and the other to boxcomp
				if (b1.GetIsCircle())
				{
					circleComp = b1;
					boxComp = b2;
				}
				else
				{
					circleComp = b2;
					boxComp = b1;
				}

				//these variables will be set to the closest points in the box to the centre of the circle
				float closestX;
				float closestY;

#pragma region SetClosestPoints
				//if the circle is to the left of the box the closest x is the leftmost point in the box
				if (circleComp.GetCentre().x < boxComp.GetPosition().x)
				{
					closestX = boxComp.GetPosition().x;
				}
				//if the circle is to the right of the box the closest x is the rightmost point of the box
				else if (circleComp.GetCentre().x > boxComp.GetPosition().x + boxComp.GetWidth())
				{
					closestX = boxComp.GetPosition().x + boxComp.GetWidth();
				}
				//if the circle is inbetween the closest point is the circle's x value
				else
				{
					closestX = circleComp.GetCentre().x;
				}

				//if the circle is above the box the closest y is the topmost point in the box
				if (circleComp.GetCentre().y < boxComp.GetPosition().y)
				{
					closestY = boxComp.GetPosition().y;
				}
				//if the circle is below the box the closest y is the bottommost point of the box
				else if (circleComp.GetCentre().y > boxComp.GetPosition().y + boxComp.GetHeight())
				{
					closestY = boxComp.GetPosition().y + boxComp.GetHeight();
				}
				//if the circle is inbetween the closest point is the circle's y value
				else
				{
					closestY = circleComp.GetCentre().y;
				}
#pragma endregion SetClosestPoints

				//if the distance to the closest point is less than the radius of the circle they intersect
				//standard dist formula: sqrt((x2-x1)^2 + (y2-y1)^2)
				if (sqrt((closestX - circleComp.GetCentre().x)*(closestX - circleComp.GetCentre().x) +
					(closestY - circleComp.GetCentre().y)*(closestY - circleComp.GetCentre().y)) <= circleComp.GetRadius())
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		//code should not reach here. This is an error message, just in case
		std::cout << "collision detection inconclusive" << std::endl;
		return false;
	}
};
