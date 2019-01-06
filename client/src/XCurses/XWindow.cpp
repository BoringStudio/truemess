#include <XCurses/XWindow.h>

XWindow::Status XWindow::addChar(uint32_t ch, int x, int y)
{
	return mvaddch(y, x, ch);
}

XWindow::Status XWindow::setBorder(const XBorder& border)
{
	m_border = border;
	return wborder(m_win, 
		border.leftSide, 
		border.rightSide, 
		border.topSide,
		border.bottomSide,
		border.topLeftCorner,
		border.topRightCorner,
		border.bottomLeftCorner,
		border.bottomRightCorner);
}

XWindow::Status XWindow::setBorder(XBorder::Type borderType)
{
	return this->setBorder(XBorder(borderType));
}

XWindow::Status XWindow::setBorder(uint32_t leftSide,
	uint32_t rightSide,
	uint32_t topSide,
	uint32_t bottomSide,
	uint32_t topLeftCorner,
	uint32_t topRightCorner,
	uint32_t bottomLeftCorner,
	uint32_t bottomRightCorner)
{
	return this->setBorder(XBorder(leftSide,
		rightSide,
		topSide,
		bottomSide,
		topLeftCorner,
		topRightCorner,
		bottomLeftCorner,
		bottomRightCorner));
}

XWindow::Status XWindow::refresh() const
{
	return wrefresh(m_win);
}
