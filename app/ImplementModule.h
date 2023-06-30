#pragma once

#include "Dispatcher.h"
#include "Implement.h"
#include "Singleton.h"
#include <map>
#include <mutex>

class ImplementModule : public Singleton<ImplementModule>
{
public:
	~ImplementModule();

	void SetDispatcher(Dispatcher* Dispatch);

	bool Register(Implement::ID Id, Implement* Impl);
	void Unregister(Implement::ID Id);

	void TurnOn(Implement::ID Id);
	void TurnOff(Implement::ID Id);
	void OnTelemetry(Implement::ID Id, bool IsOn, Implement::FUEL_LEVEL Level);

private:
	static const Implement::FUEL_LEVEL FUEL_LEVEL_CRITICALLY_LOW = 5;

	class TurnOnOffCommand : public Command
	{
	public:
		TurnOnOffCommand(Implement::ID Id, bool TurnOn) : _id(Id), _turnOn(TurnOn) {}
		virtual void Execute();

	private:
		Implement::ID	_id;
		bool			_turnOn;
	};

	class TelemetryCommand : public Command
	{
	public:
		TelemetryCommand(Implement::ID Id, bool IsOn, Implement::FUEL_LEVEL Level) :
			_id(Id),
			_isOn(IsOn),
			_level(Level)
		{}

		virtual void Execute();

	private:
		Implement::ID			_id;
		bool					_isOn;
		Implement::FUEL_LEVEL	_level;
	};

	friend class Singleton<ImplementModule>;
	ImplementModule() : _dispatcher(0) {}

	ImplementModule(const ImplementModule&) = delete;
	ImplementModule & operator=(const ImplementModule&) = delete;
	
	std::map<Implement::ID, Implement*>	_implements;
	std::mutex							_mutex;
	Dispatcher*							_dispatcher;	
};

