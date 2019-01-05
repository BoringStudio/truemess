#include <XCurses/XCurses.h>

#include <PDCurses/curses.h>

XCurses::XCurses()
{
	initscr();
}

XCurses::~XCurses()
{
	endwin();
}

void XCurses::init()
{
	this->init(XCursesConfig());
}

void XCurses::init(const XCursesConfig& config)
{
	this->setCBrake(config.enableCBreak);
	this->setEcho(config.enableEcho);
	this->setRaw(config.enableRaw);
	this->setNewLine(config.enableNewLine);
	this->setHalfDelay(config.halfDelay);
	this->setTerminalSize(config.terminalWidth, config.terminalHeight);
}

int XCurses::setCBrake(bool v)
{
	m_config.enableCBreak = v;
    if (v) {
		return cbreak();
    }
	else {
		return nocbreak();
	}
}

int XCurses::setEcho(bool v)
{
	m_config.enableEcho = v;
	if (v) {
		return echo();
	}
	else {
		return noecho();
	}
}

int XCurses::setRaw(bool v)
{
	m_config.enableRaw = v;
	if (v) {
		return raw();
	}
	else {
		return noraw();
	}
}

int XCurses::setNewLine(bool v)
{
	m_config.enableNewLine = v;
	if (v) {
		return nl();
	}
	else {
		return nonl();
	}
}

int XCurses::setHalfDelay(unsigned int delay)
{
	m_config.halfDelay = delay;
	return halfdelay(delay);
}

int XCurses::setTerminalSize(unsigned int width, unsigned int height)
{
	m_config.terminalWidth = width;
	m_config.terminalHeight = height;
	return resize_term(height, width);
}
