#pragma once

#include "Implement.h"
#include <utility>
#include <mutex>

class ImplementFactory
{
public:
	ImplementFactory() : _idGenerator(1) {}
	~ImplementFactory() {}

	typedef enum { TRACTOR, MOWER, TILLAGE, BALER, SPRAYER } TYPE;
	typedef std::pair<Implement::ID, Implement*> RESULT;

	RESULT CreateImplement(TYPE Type);

private:
	ImplementFactory(const ImplementFactory&) = delete;
	ImplementFactory & operator=(const ImplementFactory&) = delete;

	Implement::ID	_idGenerator;
	std::mutex		_mutex;
};

