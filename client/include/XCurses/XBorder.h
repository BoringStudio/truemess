#pragma once

class XBorder
{
public:
    enum Type
    {
		None,
		Standard
    };

	XBorder(uint32_t _leftSide,
		uint32_t _rightSide,
		uint32_t _topSide,
		uint32_t _bottomSide,
		uint32_t _topLeftCorner,
		uint32_t _topRightCorner,
		uint32_t _bottomLeftCorner,
		uint32_t _bottomRightCorner) :
        leftSide(_leftSide),
        rightSide(_rightSide),
        topSide(_topSide),
        bottomSide(_bottomSide),
        topLeftCorner(_topLeftCorner),
        topRightCorner(_topRightCorner),
        bottomLeftCorner(_bottomLeftCorner),
        bottomRightCorner(_bottomRightCorner)
	{
	}

	XBorder(XBorder::Type type)
	{
		switch (type) {
		case XBorder::Type::None:
		{
			this->fill(' ');
			break;
		}
		case XBorder::Type::Standard:
		{
            leftSide = '|';
			rightSide = '|';
			topSide = '-';
			bottomSide = '-';
			topLeftCorner = '+';
			topRightCorner = '+';
			bottomLeftCorner = '+';
			bottomRightCorner = '+';
			break;
		}
		}
	}

	void fill(uint32_t c)
	{
	    leftSide = c;
	    rightSide = c;
	    topSide = c;
	    bottomSide = c;
	    topLeftCorner = c;
	    topRightCorner = c;
	    bottomLeftCorner = c;
	    bottomRightCorner = c;
	}

	uint32_t leftSide;
	uint32_t rightSide;
	uint32_t topSide;
	uint32_t bottomSide;
	uint32_t topLeftCorner;
	uint32_t topRightCorner;
	uint32_t bottomLeftCorner;
	uint32_t bottomRightCorner;
};