#pragma once
#include "Observer.h"
#include "ComponentList.h"
#include "InputComponent.h"
#include "ObserverList.h"
class InputObserver :public Observer
{
public:
	InputObserver() {};
	~InputObserver() override {};
	void onNotify(EventCode evt)override
	{
		evtStack.push_back(evt);
		switch (evt)
		{
		case BUTTON_CLICKED:
			
			break;
		default:
			break;
		}
	}
	void testCall()
	{
		std::cout << "call" << std::endl;
	}
private:

};