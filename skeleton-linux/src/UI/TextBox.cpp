#include <cctype>
#include "UI/TextBox.h"

using namespace std;

TextBox::TextBox (string name, unsigned left,
		unsigned top, unsigned width) :
	UIObject (name, left, top, width, 1, true) {
	this->text = string ();
	this->uobjBox = new ColorLabel ("box", left, top, width, 1);
	this->curpos = 0;

	uobjBox->setColor (COLOR_WHITE);
};


string TextBox::getText () {
	return text;
}

void TextBox::setText (string t) {
	string old_text = text;
	text = t;
	curpos = text.length ();

	if (old_text != text) {
		onTextChanged.emit (this);
	}
}


void TextBox::draw () {
	uobjBox->setCaption (text);
	uobjBox->draw ();

	if (isFocused () && text.length () < getWidth ()) {
		if (curpos >= 0 && curpos < text.length ()) {
			gterm_cprintf (getLeft () + curpos, getTop (), COLOR_BLACK, 
				"%c", text[curpos]);
		}
		else {
			gterm_cprintf (getLeft () + text.length (), getTop (), COLOR_BLACK, " ");
		}
	}
}

void TextBox::input (int key) {
	string old_text = text;

	if (key == GTERM_KEY_BACKSPACE) {
		if (curpos > 0) {
			text.erase (curpos - 1, 1);
			curpos--;
		}
	}
	else if (key == GTERM_KEY_LEFT) {
		if (curpos - 1 >= 0)
			curpos--;
	}
	else if (key == GTERM_KEY_RIGHT) {
		if (curpos + 1 <= old_text.length ())
			curpos++;
	}
	else if (key == GTERM_KEY_ENTER) {		/**< KEY: enter */
		onEnterKeyPressed.emit (this);
	}
	else if (isprint (key)) {
		text.insert (curpos, 1, key);
		curpos++;
	}

	if (old_text != text) {
		onTextChanged.emit (this);
	}

	draw ();
}
