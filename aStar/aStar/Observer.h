#pragma once
#include "ECS.h"
#include "ObserverList.h"
#include <iostream>

class Observer:public Component
{
private:

public:
	//make into component
	Observer() {};
	virtual ~Observer() {};
	//update event-entity1-entity2(null) so we can have responses between two
	virtual void onNotify(EventCode evt) =0;
	std::vector<EventCode> evtStack;
};
