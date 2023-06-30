#pragma once
#include "Dispatcher.h"
#include "Implement.h"
#include "Singleton.h"

class ImplementController : public Singleton<ImplementController>
{
public:
	~ImplementController();

	void SetDispatcher(Dispatcher* Dispatch);
	void CreateImplements();
	void OnTelemetry(Implement::ID Id, bool IsOn, Implement::FUEL_LEVEL Level);

protected:
	friend class Singleton<ImplementController>;
	ImplementController() : _dispatcher(0) {}

	ImplementController(const ImplementController&) = delete;
	ImplementController & operator=(const ImplementController&) = delete;

	Dispatcher*	_dispatcher;
};

