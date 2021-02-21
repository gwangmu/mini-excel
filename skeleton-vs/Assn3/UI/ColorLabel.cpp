#include "UI/ColorLabel.h"

using namespace std;

ColorLabel::ColorLabel (string name, unsigned left,
		unsigned top, unsigned width, unsigned height) :
	Label (name, left, top, width, height) {
	this->color = COLOR_BLACK;
};


unsigned ColorLabel::getColor () {
	return color;
}

void ColorLabel::setColor (unsigned value) {
	unsigned old_color = color;
	color = value;

	if (old_color != color) {
		onColorChanged.emit (this);
	}
}


void ColorLabel::draw () {
	gterm_whcprintf (getLeft (), getTop(), getWidth (), getHeight (), color,
			"%*c", getWidth (), ' ');

	if (getCaption () != string (""))
		gterm_whcprintf (getLeft (), getTop(), getWidth (), getHeight (), color,
				"%s", getCaption().c_str ());
}

void ColorLabel::input (int key) {
	// Nothing to be done
}
