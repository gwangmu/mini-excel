#include "UI/LabeledStrip.h"

using namespace std;

LabeledStrip::LabeledStrip (string name, unsigned left,
		unsigned top, unsigned wlabel, unsigned wmsg) :
	UIObject (name, left, top, wlabel + wmsg, 1, false) {
	uobjLabel = new ColorLabel ("label", left, top, wlabel, 1);
	uobjMsg = new ColorLabel ("msg", left + wlabel, top, wmsg, 1);
};

LabeledStrip::~LabeledStrip () {
	delete uobjLabel;
	delete uobjMsg;
}


string LabeledStrip::getLabel () {
	return uobjLabel->getCaption ();
}

string LabeledStrip::getCaption () {
	return uobjMsg->getCaption ();
}


void LabeledStrip::setLabel (string lbl) {
	string old_label = uobjLabel->getCaption ();
	uobjLabel->setCaption (lbl);

	if (old_label != uobjLabel->getCaption ()) {
		onLabelChanged.emit (this);
	}
}

void LabeledStrip::setCaption (string msg) {
	string old_caption = uobjMsg->getCaption ();
	uobjMsg->setCaption (msg);

	if (old_caption != uobjMsg->getCaption ()) {
		onCaptionChanged.emit (this);
	}
}

void LabeledStrip::setLabelColor (unsigned color) {
	uobjLabel->setColor (color);
}

void LabeledStrip::setCaptionColor (unsigned color) {
	uobjMsg->setColor (color);
}


void LabeledStrip::draw () {
	uobjLabel->draw ();
	uobjMsg->draw ();
}

void LabeledStrip::input (int key) {
	// Nothing to be done
}
