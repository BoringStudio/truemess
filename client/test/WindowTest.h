#pragma once

#include <PDCurses/curses.h>
#include <string>

class WindowTest
{
public:
    WindowTest()
    {
		// Init curses console
		initscr();

		// Set size of terminal
		resize_term(50, 120);

		// For change colors
		start_color();

		// Don't print symbols during writing
		noecho();

		// Allow input CTRL+Z, CTRL+C etc.
		raw();

		// Set no new line
		nonl();

		// Refresh stdscr
		refresh();
    }

    void exec()
    {
		WINDOW* win = newwin(50, 50, 0, 0);

		std::string a;

		while (true) {
			int m_key = wgetch(win);

			if (m_key != ERR) {
				wclear(win);
				a = std::to_string(m_key);
				mvwprintw(win, 0, 0, a.c_str());
			}

			wrefresh(win);
		}
    }

    ~WindowTest()
    {
		endwin();
    }
};