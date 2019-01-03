#include <Truemess/System/Core.h>

#include <exception>

#include "../test/WindowTest.h"

namespace tms {
Core::Core() : m_isRunning(false), m_logger()
{
}

void Core::run()
{
	m_logger.init("log.txt", "ru");

	try {
		WindowTest test1;
		test1.exec();
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
