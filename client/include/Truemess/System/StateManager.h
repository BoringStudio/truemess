#pragma once

#include <mutex>
#include <list>

#include <Truemess/System/State.h>

namespace tms {
class Core;


class StateManager {
public:
	void init();

    template<typename StateType, typename ... Args>
	void push(const Args& ... args);

private:
	std::list<State::Ptr> m_states;
};
}