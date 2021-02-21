#ifndef ASSN2_COLOR_LABEL_H
#define ASSN2_COLOR_LABEL_H

#include "UI/Label.h"
#include "UI/UICallback.h"

using namespace std;

class ColorLabel : public Label {
public:
	/* Event Handlers */
	UICallback onColorChanged;

private:
	unsigned color;

public:
	/* Constructor */
	ColorLabel (string name, unsigned left, unsigned top,
			unsigned width, unsigned height);

	/* Getter/Setter */
	unsigned getColor ();
	void setColor (unsigned value);

	/* Methods */
	virtual void draw ();
	virtual void input (int key);
};

#endif
