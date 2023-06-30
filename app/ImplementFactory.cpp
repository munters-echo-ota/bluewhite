#include "ImplementFactory.h"
#include "Tractor.h"
#include "Mower.h"
#include "Baler.h"
#include "Tillage.h"
#include "Sprayer.h"
#include <mutex>

ImplementFactory::RESULT ImplementFactory::CreateImplement(TYPE Type)
{
	std::unique_lock<std::mutex> lock(_mutex);

	Implement* impl = 0;

	switch (Type)
	{
		case TRACTOR:	impl = new Tractor(_idGenerator);	break;
		case MOWER:		impl = new Mower(_idGenerator);		break;
		case TILLAGE:	impl = new Tillage(_idGenerator);	break;
		case BALER:		impl = new Baler(_idGenerator);		break;
		case SPRAYER:	impl = new Sprayer(_idGenerator);	break;
		default:  break;
	}
	
	if (impl)
	{
		auto res = std::make_pair(impl ? _idGenerator : Implement::WRONG_ID, impl);
		_idGenerator++;
		return res;
	}

	return std::make_pair(Implement::WRONG_ID, impl);
}
