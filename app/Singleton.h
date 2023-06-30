#pragma once

#include <mutex>

template <class T>
class Singleton
{
public:
	static T* Instance()
	{
		static T* volatile _instance = 0;

		if (_instance == 0)
		{
			std::mutex _mutex;

			_mutex.lock();
			
			if (_instance == 0)
				_instance = new T();

			_mutex.unlock();
		}

		return _instance;
	}
};
