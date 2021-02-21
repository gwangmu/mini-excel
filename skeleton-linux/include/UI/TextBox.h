#ifndef ASSN2_TEXT_BOX_H
#define ASSN2_TEXT_BOX_H

#include "UI/UIObject.h"
#include "UI/ColorLabel.h"
#include "UI/UICallback.h"

using namespace std;

class TextBox : public UIObject {
public:
	/* Event Handlers */
	UICallback onTextChanged;
	UICallback onEnterKeyPressed;

private:
	string text;
	ColorLabel *uobjBox;
	int curpos;

public:
	/* Constructor */
	TextBox (string name, unsigned left, unsigned top,
			unsigned width);

	/* Getter/Setter */
	string getText ();
	void setText (string text);

	/* Methods */
	virtual void draw ();
	virtual void input (int key);
};

#endif
