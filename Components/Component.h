#pragma once
class GameObject;

/********
INTERFACE
********/

class Component {
public:
	virtual ~Component() {};
	virtual void Update(GameObject& in_obj) = 0;
};