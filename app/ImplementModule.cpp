#include "ImplementModule.h"
#include "ImplementController.h"

ImplementModule::~ImplementModule()
{
	std::unique_lock<std::mutex> lock(_mutex);
	_implements.clear();
}

void ImplementModule::SetDispatcher(Dispatcher* Dispatch)
{
	_dispatcher = Dispatch;
}

void ImplementModule::TurnOn(Implement::ID Id)
{
	_dispatcher->PostCommand(new TurnOnOffCommand(Id, true));
}

void ImplementModule::TurnOff(Implement::ID Id)
{
	_dispatcher->PostCommand(new TurnOnOffCommand(Id, false));
}

void ImplementModule::OnTelemetry(Implement::ID Id, bool IsOn, Implement::FUEL_LEVEL Level)
{
	_dispatcher->PostCommand(new TelemetryCommand(Id, IsOn, Level));
}

bool ImplementModule::Register(Implement::ID Id, Implement * Impl)
{
	std::unique_lock<std::mutex> lock(_mutex);
	return _implements.insert(std::make_pair(Id, Impl)).second;
}

void ImplementModule::Unregister(Implement::ID Id)
{
	std::unique_lock<std::mutex> lock(_mutex);
	_implements.erase(Id);
}

void ImplementModule::TurnOnOffCommand::Execute()
{
	auto implModule = ImplementModule::Instance();
	std::unique_lock<std::mutex> lock(implModule->_mutex);

	auto i = implModule->_implements.find(_id);
	if (i != implModule->_implements.end())
	{
		if (_turnOn)
			i->second->TurnOn();
		else
			i->second->TurnOff();
	}
}

void ImplementModule::TelemetryCommand::Execute()
{
	auto implModule = ImplementModule::Instance();
	std::unique_lock<std::mutex> lock(implModule->_mutex);

	auto i = implModule->_implements.find(_id);
	if (i != implModule->_implements.end())
	{
		if (_level <= FUEL_LEVEL_CRITICALLY_LOW)
			i->second->TurnOff();

		ImplementController::Instance()->OnTelemetry(_id, _isOn, _level);
	}
}
