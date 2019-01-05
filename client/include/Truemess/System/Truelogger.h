#pragma once

#include <iostream>
#include <fstream>
#include <clocale>
#include <string>
#include <mutex>
#include <ctime>

namespace tms {
class Truelogger
{
public:
	enum Stream
	{
		File,
		Console,
		All
	};

	enum DataType
	{
		Debug,
		Info,
		Warning,
		Error
	};

	Truelogger()
	{
	}

    void init(const std::string& logPath, const std::string& logLocale)
	{
		m_logFile.open(logPath);

		if (!m_logFile.is_open()) {
			throw std::runtime_error("");
		}

		m_logLocale = std::locale(logLocale);

		std::setlocale(LC_ALL, m_logLocale.c_str());
		m_logFile.imbue(m_logLocale);	    
	}

	template<typename ArgType, typename ... ArgTypes>
	void write(Truelogger::DataType type, Truelogger::Stream streamType, const std::string& format, const ArgType& value, const ArgTypes& ... args)
	{
		std::string formatedStr = format;
		for (std::string::iterator it = formatedStr.begin(); it != formatedStr.end(); it++) {
			//if (*it == )
			// TODO: finish write function
		}

		this->write(type, formatedStr, args...);
	}

	void write(Truelogger::DataType type, Truelogger::Stream streamType, const std::string& format)
	{

	}

private:
	std::wofstream m_logFile;
	std::mutex m_logMutex;

	std::locale m_logLocale;
};
}