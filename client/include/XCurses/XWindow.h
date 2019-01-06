#pragma once

#include <cstdint>
#include <memory>

#include <PDCurses/curses.h>
#include <XCurses/XBorder.h>

class XWindow
{
public:
	using Status = int;
	using Ptr = std::unique_ptr<XWindow>;

    /**
	 * \brief Add character in UTF-8 encoding in { x, y } point
	 * \param ch Character
	 * \param x Coordinate
	 * \param y Coordinate
	 * \return Window status code
	 */
	XWindow::Status addChar(uint32_t ch, int x, int y);

    /**
	 * \brief Set border to window
	 * \param border Border to set
	 * \return Window status code
	 */
	XWindow::Status setBorder(const XBorder& border);
   
    /**
	 * \brief Set border to window
	 * \param borderType Border type from the list of the standard borders 
	 * \return Window status code
	 */
	XWindow::Status setBorder(XBorder::Type borderType);

    /**
	 * \brief Set border to window
	 * \param leftSide Character for left side of border
	 * \param rightSide Character for right side of border
	 * \param topSide Character for top side of border
	 * \param bottomSide Character for bottom side of border
	 * \param topLeftCorner Character for top left corner of border
	 * \param topRightCorner Character for top right corner of border
	 * \param bottomLeftCorner Character for bottom left corner of border
	 * \param bottomRightCorner Character for bottom right corner of border
	 * \return Window status code
	 */
	XWindow::Status setBorder(uint32_t leftSide,
		uint32_t rightSide,
		uint32_t topSide,
		uint32_t bottomSide,
		uint32_t topLeftCorner,
		uint32_t topRightCorner,
		uint32_t bottomLeftCorner,
		uint32_t bottomRightCorner);
	
    /**
     * \brief Refresh PDCurses window
     * \return Window status code
     */
    XWindow::Status refresh() const;

private:
    /**
	 * \brief PDCurses 
	 */
	WINDOW* m_win;
    
    /**
	 * \brief True - nodelay mode is ON, false - OFF
	 */
	bool m_nodelayMode;

    /**
	 * \brief True - keypad mode is ON, false - OFF
	 */
	bool m_keypadMode;

    /**
	 * \brief True - scrollok mode is ON, false - OFF
	 */
	bool m_scrollMode;

    /**
	 * \brief PDCurses window border container
	 */
	XBorder m_border;
};