#pragma once
#include "GameObject.h"

/********
INTERFACE
********/

class Component {
public:
	virtual ~Component() {};
	virtual void Update(GameObject& in_obj) = 0;
};