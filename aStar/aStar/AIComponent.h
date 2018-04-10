#pragma once
#include "ECS.h"
#include "SDL.h"

class AIComponent : public Component
{
public:
	/// <summary>
	/// Constructor function. 
	/// </summary>
	/// <param name="ai">Desired AI pattern.</param>
	AIComponent(int ai = 0) : aiType(ai) { }



	void setTarget(Entity *ent)
	{
		currentTarget = ent;
	}

	Entity* getTarget()
	{
		if (currentTarget != nullptr)
		{
			if (currentTarget->isActive())
			{
				return currentTarget;
			}
			else
			{
				currentTarget = nullptr;
				return nullptr;
			}
		}

		return nullptr;
	}

	/// <summary>
	/// Returns AI type value.
	/// </summary>
	/// <returns>Number defining this entity's AI pattern.</returns>
	int getAIType()
	{ return aiType; }	
private:
	int aiType; //Defines the AI pattern the owner will use. See the enum in AISystem.
	Entity* currentTarget;
};