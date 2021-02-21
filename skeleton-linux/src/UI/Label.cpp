#include "UI/Label.h"

using namespace std;

Label::Label (string name, unsigned left,
		unsigned top, unsigned width, unsigned height) :
	UIObject (name, left, top, width, height, false) {
	this->caption = string ("");
};


string Label::getCaption () {
	return caption;
}

void Label::setCaption (string msg) {
	string old_caption = caption;

	caption = msg;

	if (caption != old_caption) {
		onCaptionChanged.emit (this);
	}
}


void Label::draw () {
	if (caption == string ("")) {
		gterm_whprintf (getLeft (), getTop(), getWidth (), getHeight (),
				" ", caption.c_str ());
	}
	else {
		gterm_whprintf (getLeft (), getTop(), getWidth (), getHeight (),
				"%s", caption.c_str ());
	}
}

void Label::input (int key) {
	// Nothing to be done
}
