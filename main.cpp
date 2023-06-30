#include "ImplementModule.h"
#include "ImplementFactory.h"
#include "ImplementController.h"

int main()
{
	Dispatcher d;
	ImplementModule::Instance()->SetDispatcher(&d);

	auto controller = ImplementController::Instance();
	controller->SetDispatcher(&d);
	controller->CreateImplements();

	d.RunCommandLoop();
}