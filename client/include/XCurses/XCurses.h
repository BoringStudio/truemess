#pragma once

#include "XCursesConfig.h"

class XCurses
{
public:
	XCurses();
	~XCurses();

	void init(const XCursesConfig& config);
	int setCBrake(bool v);
	int setEcho(bool v);
	int setRaw(bool v);
	int setNewLine(bool v);
	int setHalfDelay(unsigned int delay);
	int setTerminalSize(unsigned int width, unsigned int height);

private:
	XCursesConfig m_config;
};