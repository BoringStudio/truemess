#pragma once

#include <memory>

namespace tms {
class Core;

// Base class
class State {
public:
	typedef int Status;
	typedef std::unique_ptr<State> Ptr;

protected:
	State() = default;
	State(const State&) = default;
	State(State&&) = default;

	friend class Core;

	virtual void init() = 0;

	virtual void update(float dt) = 0;

	virtual void draw() = 0;

	virtual void destroy() = 0;

	Core* m_core;
};
}