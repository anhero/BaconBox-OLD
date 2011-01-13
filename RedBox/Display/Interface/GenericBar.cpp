#include "GenericBar.h"

using namespace RedBox;

void GenericBar::clean() {
	if (valueBar) {
		delete valueBar;
		valueBar = NULL;
	}
}

void GenericBar::copyFrom(const GenericBar& src) {
	if (this != &src) {
		clean();
		if (&src) {
			value = src.value;
			shownValue = src.shownValue;
			lastIncrement = src.lastIncrement;
			maxValue = src.maxValue;
			maxBarLength = src.maxBarLength;
			delay = src.delay;
			if(src.valueBar) valueBar = new OpenGLDrawer(*(src.valueBar));
			xCorr = src.xCorr;
			yCorr = src.yCorr;
		}
	}
}

GenericBar::GenericBar(): GraphicObject(), value(0), shownValue(0), lastIncrement(0.0),
maxValue(0), maxBarLength(0.0), delay(GenericBar::DEFAULT_DELAY), valueBar(NULL),
xCorr(0.0), yCorr(0.0), usingFrameHeight(false) {
	valueBar = new OpenGLDrawer();
}

GenericBar::GenericBar(int newMaxValue, double newMaxBarLength, 
		 const std::string& barImgPath, double barWidth, int barFrameWidth,
		 double newXCorr, double newYCorr, bool newFrameOnTop,
		 int newPixelsPerValue, double newDelay): GraphicObject(),
value(0), shownValue(0), lastIncrement(0.0), maxValue(newMaxValue),
maxBarLength(newMaxBarLength),xCorr(newXCorr), yCorr(newYCorr), valueBar(NULL),
frameOnTop(newFrameOnTop), usingFrameHeight(false), delay(newDelay)  {
	if (newPixelsPerValue <= 0) {
		newPixelsPerValue = 1;
	}
	//OpenGLDrawer(double x, double y, double width, double height, double angle, const char* imagePath, int pixelWidth, int PixelHeight);
	valueBar = new OpenGLDrawer(0.0, 0.0, barWidth, 0.0, 0.0, barImgPath.c_str(), barFrameWidth, newPixelsPerValue);
}

GenericBar::GenericBar(const GenericBar& src): GraphicObject(src), valueBar(NULL), usingFrameHeight(false) {
	copyFrom(src);
}

GenericBar::~GenericBar() {
	clean();
}

GenericBar& GenericBar::operator=(const GenericBar& src) {
	GraphicObject::operator=(src);
	copyFrom(src);
	return *this;
}

void GenericBar::update() {
	GraphicObject::update();
	double sinceEpoch = TimeHelper::getSinceEpoch();
	valueBar->setFrame(0);
	int tmpValue = static_cast<int>(static_cast<double>(value) / static_cast<double>(maxValue) * maxBarLength);
	// We update the health bar's animation.
	if (shownValue != tmpValue && sinceEpoch - lastIncrement > delay) {
		// If the remaining difference is too small to have the division work on it.
		if(abs(tmpValue - shownValue) <= GenericBar::VALUE_ANIM_DIV - 1)
			shownValue += (tmpValue > shownValue)?(1):(-1);
		// If the remaining difference is too big and would make a choppy animation, we make it smaller.
		else if(abs(tmpValue - shownValue) <= GenericBar::MAX_VALUE_DIFF)
			shownValue += (tmpValue - shownValue) / GenericBar::VALUE_ANIM_DIV;
		// If the remaining difference is okay.
		else
			shownValue += GenericBar::MAX_VALUE_MOVE * ((tmpValue > shownValue)?(1):(-1));
		if (usingFrameHeight) {
			valueBar->setFrameHeight(shownValue);
		} else {
			// We set the position and size of the health bar.
			valueBar->setHeight(static_cast<double>(shownValue));
		}
		refreshBarPosition();
		lastIncrement += delay;
	}
}

void GenericBar::render() {
	if (frameOnTop) {
		valueBar->render();
		GraphicObject::render();
	} else {
		GraphicObject::render();
		valueBar->render();
	}
}

int GenericBar::getMaxValue() const {
	return maxValue;
}

void GenericBar::setMaxValue(int newMaxValue) {
	if (newMaxValue >= 0) {
		maxValue = newMaxValue;
		if (value > maxValue) {
			value = maxValue;
		}
	}
}

int GenericBar::getValue() const {
	return value;
}

void GenericBar::setValue(int newValue) {
	if (value > maxValue) {
		value = maxValue;
	} else if (value < 0) {
		value = 0;
	} else {
		value = newValue;
	}
}

GenericBar& GenericBar::operator+=(int aValue) {
	if (value + aValue < 0) {
		value = 0;
	} else if (value + aValue > maxValue) {
		value = maxValue;
	} else {
		value += aValue;
	}
	return *this;
}
GenericBar& GenericBar::operator-=(int aValue) {
	if (value - aValue < 0) {
		value = 0;
	} else if (value - aValue > maxValue) {
		value = maxValue;
	} else {
		value -= aValue;
	}
	return *this;
}

void GenericBar::refreshBarPosition() {
	valueBar->setPosition(getXPosition() + xCorr * cos(DEGREES_TO_RADIANS(getAngle())) + (getHeight() * -0.5 + yCorr + static_cast<double>(shownValue / 2)) * sin(DEGREES_TO_RADIANS(getAngle())) * -1.0, getYPosition() + (getHeight() * -0.5 + yCorr + static_cast<double>(shownValue / 2)) * cos(DEGREES_TO_RADIANS(getAngle())) +
						  xCorr * sin(DEGREES_TO_RADIANS(getAngle())));
}
void GenericBar::setPosition(double x, double y) {
	GraphicObject::setPosition(x, y);
	refreshBarPosition();
}
void GenericBar::setXPosition(double x) {
	GraphicObject::setXPosition(x);
	refreshBarPosition();
}
void GenericBar::setYPosition(double y) {
	GraphicObject::setYPosition(y);
	refreshBarPosition();
}
void GenericBar::setPositionCorrection(double newXCorr, double newYCorr) {
	xCorr = newXCorr;
	yCorr = newYCorr;
}
void GenericBar::setXPositionCorrection(double newXCorr) {
	xCorr = newXCorr;
}
void GenericBar::setYPositionCorrection(double newYCorr) {
	yCorr = newYCorr;
}
double GenericBar::getXPositionCorrection() const {
	return xCorr;
}
double GenericBar::getYPositionCorrection() const {
	return yCorr;
}
void GenericBar::setAngle(double angle) {
	GraphicObject::setAngle(angle);
	valueBar->setAngle(angle);
}
void GenericBar::setFrameOnTop() {
	frameOnTop = true;
}
void GenericBar::setBarOnTop() {
	frameOnTop = false;
}
void GenericBar::useFrameHeight() {
	usingFrameHeight = true;
}
void GenericBar::useHeight() {
	usingFrameHeight = false;
}
