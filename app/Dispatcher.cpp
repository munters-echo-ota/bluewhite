#include "Dispatcher.h"

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

Dispatcher::Dispatcher() : _exitRequested(false)
{}

Dispatcher::~Dispatcher()
{}

void Dispatcher::PostCommand(Command* Cmd)
{
	{
		std::unique_lock<std::mutex> lock(_mutex);
		_queue.push(Cmd);
	}

	_signal.notify_one();
}

void Dispatcher::Exit()
{
	_exitRequested = true;
}

void Dispatcher::RunCommandLoop()
{
	while (true)
	{
		Command* cmd = 0;

		{
			std::unique_lock<std::mutex> lock(_mutex);
			_signal.wait(lock, [this] { return _exitRequested || !_queue.empty(); });

			if (_exitRequested && _queue.empty())
				break;

			cmd = _queue.front();
			_queue.pop();
		}

		if (cmd)
		{
			cmd->Execute();
			delete cmd;
		}
	}
}

