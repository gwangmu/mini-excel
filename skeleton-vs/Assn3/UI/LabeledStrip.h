#ifndef ASSN2_LABELED_STRIP_H
#define ASSN2_LABELED_STRIP_H

#include "UI/UIObject.h"
#include "UI/ColorLabel.h"
#include "UI/UICallback.h"

using namespace std;

class LabeledStrip : public UIObject {
public:
	/* Event Handlers */
	UICallback onLabelChanged;
	UICallback onCaptionChanged;

private:
	ColorLabel *uobjLabel;
	ColorLabel *uobjMsg;

public:
	/* Constructor/Destructor */
	LabeledStrip (string name, unsigned left, unsigned top,
			unsigned wlabel, unsigned wmsg);
	~LabeledStrip ();

	/* Getter/Setter */
	string getLabel ();
	string getCaption ();
	void setLabel (string lbl);
	void setCaption (string msg);
	void setLabelColor (unsigned color);
	void setCaptionColor (unsigned color);

	/* Methods */
	virtual void draw ();
	virtual void input (int key);
};

#endif
