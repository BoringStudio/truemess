#pragma once

struct XCursesConfig
{
    XCursesConfig() : 
                    terminalWidth(120),
                    terminalHeight(50),
                    enableCBreak(true),
                    enableEcho(false),
                    enableRaw(true),
                    enableNewLine(false),
                    halfDelay(1)
	{}

	unsigned int terminalWidth;
	unsigned int terminalHeight;
	bool enableCBreak;
	bool enableEcho;
	bool enableRaw;
	bool enableNewLine;
	unsigned int halfDelay;
};