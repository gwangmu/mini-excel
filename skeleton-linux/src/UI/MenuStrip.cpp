#include "UI/MenuStrip.h"
#include "UI/gterm.h"
#include <cassert>

using namespace std;

MenuStrip::MenuStrip (string name, unsigned width) :
	UIObject (name, 0, 0, width, 1, true) {
	uobjBack = new ColorLabel ("back", 0, 0, width, 1);
	uobjBack->setColor (COLOR_WHITE);

	sizeXOff = 1;
	focus = MENUSTRIP_FOCUS_NONE;
};

MenuStrip::~MenuStrip () {
	delete uobjBack;
	for (vector<ColorLabel *>::iterator it = vecUObjButtons.begin ();
			 it != vecUObjButtons.end (); it++) {
		delete (*it);
	}
}


void MenuStrip::addButton (string name) {
	ColorLabel *uobjNButton = new ColorLabel ("group", sizeXOff, 0, name.length (), 1);

	uobjNButton->setCaption (name);
	uobjNButton->setColor (COLOR_WHITE);
	vecUObjButtons.push_back (uobjNButton);
	sizeXOff += (name.length () + 1);

	if (focus == MENUSTRIP_FOCUS_NONE) {
		focus = 0;
		uobjNButton->setColor (COLOR_BLACK);
	}
}

void MenuStrip::removeButton (string name) {
	vecUObjButtons[focus]->setColor (COLOR_WHITE);

	vector<ColorLabel *>::iterator it = vecUObjButtons.begin ();
	while (it != vecUObjButtons.end ()) {
		if ((*it)->getCaption () == name) {
			delete (*it);
			vecUObjButtons.erase (it);
			break;
		}
		else
			it++;
	}

	// Renew 'sizeXOff'.
	sizeXOff = 1;
	for (it = vecUObjButtons.begin ();
			 it != vecUObjButtons.end (); it++) {
		sizeXOff += ((*it)->getCaption().length () + 1);
	}

	focus = MENUSTRIP_FOCUS_NONE;
}

void MenuStrip::clearButtons () {
	for (vector<ColorLabel *>::iterator it = vecUObjButtons.begin ();
			 it != vecUObjButtons.end (); it++) {
		delete (*it);
	}

	vecUObjButtons.clear ();

	sizeXOff = 1;
	focus = MENUSTRIP_FOCUS_NONE;
}


string MenuStrip::getFocusedButton () {
	if (focus != MENUSTRIP_FOCUS_NONE)
		return vecUObjButtons[focus]->getCaption ();
	else
		return string ();
}


void MenuStrip::draw () {
	uobjBack->draw ();
	for (unsigned i = 0; i < vecUObjButtons.size (); i++) {
		vecUObjButtons[i]->draw ();
	}

	if (isFocused ()) {
		gterm_cprintf (getLeft (), getTop (), COLOR_BLUE, " ");
	}
}

void MenuStrip::input (int key) {
	if (key == GTERM_KEY_LEFT) {
		if (focus - 1 >= 0) {
			vecUObjButtons[focus]->setColor (COLOR_WHITE);
			vecUObjButtons[focus - 1]->setColor (COLOR_BLACK);
			focus--;

			onFocusChanged.emit (this);
		}
	}
	else if (key == GTERM_KEY_RIGHT) {
		if (focus + 1 < vecUObjButtons.size ()) {
			vecUObjButtons[focus]->setColor (COLOR_WHITE);
			vecUObjButtons[focus + 1]->setColor (COLOR_BLACK);
			focus++;

			onFocusChanged.emit (this);
		}
	}
	else if (key == GTERM_KEY_ENTER) {
		onSelected.emit (this);
	}

	draw ();
}
