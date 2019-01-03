#pragma once
#include <Truemess/System/Truelogger.h>

namespace tms {
class Core
{
public:
	Core();

	void run();
	void exit();

	bool isRunning() const;
	Truelogger* logger();

private:
	bool m_isRunning;
	Truelogger m_logger;
};
}