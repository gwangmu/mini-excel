#ifndef ASSN2_LABEL_H
#define ASSN2_LABEL_H

#include "UI/UIObject.h"
#include "UI/UICallback.h"

using namespace std;

class Label : public UIObject {
public:
	/* Event Handlers */
	UICallback onCaptionChanged;

private:
	string caption;

public:
	/* Constructor */
	Label (string name, unsigned left, unsigned top,
			unsigned width, unsigned height);

	/* Getter/Setter */
	string getCaption ();
	void setCaption (string msg);

	/* Methods */
	virtual void draw ();
	virtual void input (int key);
};

#endif
