#include "ImplementController.h"
#include "ImplementFactory.h"
#include "ImplementModule.h"

ImplementController::~ImplementController()
{
}

void ImplementController::SetDispatcher(Dispatcher * Dispatch)
{
	_dispatcher = Dispatch;
}

void ImplementController::CreateImplements()
{
	ImplementFactory factory;
	auto im = ImplementModule::Instance();

	auto res = factory.CreateImplement(ImplementFactory::TRACTOR);
	im->Register(res.first, res.second);

	res = factory.CreateImplement(ImplementFactory::MOWER);
	im->Register(res.first, res.second);

	res = factory.CreateImplement(ImplementFactory::TILLAGE);
	im->Register(res.first, res.second);

	res = factory.CreateImplement(ImplementFactory::BALER);
	im->Register(res.first, res.second);

	res = factory.CreateImplement(ImplementFactory::SPRAYER);
	im->Register(res.first, res.second);
}

void ImplementController::OnTelemetry(Implement::ID Id, bool IsOn, Implement::FUEL_LEVEL Level)
{
}

