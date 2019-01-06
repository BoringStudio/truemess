#include <Truemess/System/Core.h>
#include <Truemess/System/Vector.h>

#include <exception>

namespace tms {
Core::Core() : m_isRunning(false), m_logger()
{
}

void Core::run()
{
	m_logger.init("log.txt", "ru");
	m_xcursesSupervisor.init();

	try {
		
	}
	catch (const std::exception& e) {
		std::cout << e.what();
		system("pause");
	}
}

void Core::exit()
{
	m_isRunning = false;
}

bool Core::isRunning() const
{
	return m_isRunning;
}

Truelogger* Core::logger()
{
	return &m_logger;
}
}
