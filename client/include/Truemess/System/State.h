#pragma once

#include <memory>

namespace tms {
class Core;

// Base class
class State {
public:
	using Status = int;
	using Ptr = std::unique_ptr<State>;

protected:
	friend class StateManager;

	virtual void init() = 0;

	virtual void update(float dt) = 0;

	virtual void draw() = 0;

	virtual void destroy() = 0;

	Core* m_core;
};
}