#pragma once

class Implement
{
public:
	Implement() : _id(WRONG_ID) {}
	virtual ~Implement() {}

	typedef unsigned int ID;
	typedef unsigned int FUEL_LEVEL;
	static const Implement::ID WRONG_ID = 0;

	virtual void TurnOn() = 0;
	virtual void TurnOff() = 0;
	virtual ID GetId() { return _id; }

protected:
	ID	_id;
};