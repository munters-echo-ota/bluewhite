#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

class Command
{
public:
	virtual ~Command() {}
	virtual void Execute() = 0;
};

class Dispatcher
{
public:
	Dispatcher();
	~Dispatcher();

	void RunCommandLoop();
	void PostCommand(Command* Cmd);
	void Exit();

private:
	std::queue<Command*>	_queue;
	std::mutex				_mutex;
	std::condition_variable	_signal;
	volatile bool			_exitRequested;
};
