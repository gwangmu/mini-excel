#ifndef ASSN2_MENU_STRIP_H
#define ASSN2_MENU_STRIP_H

#include "UI/UIObject.h"
#include "UI/ColorLabel.h"
#include "UI/UICallback.h"
#include <vector>

#define MENUSTRIP_FOCUS_NONE (-1)

using namespace std;

class MenuStrip : public UIObject {
public:
	/* Event Handlers */
	UICallback onFocusChanged;
	UICallback onSelected;

private:
	ColorLabel *uobjBack;
	vector<ColorLabel *> vecUObjButtons;
	unsigned sizeXOff;
	int focus;

public:
	/* Constructor */
	MenuStrip (string name, unsigned width);
	~MenuStrip ();

	/* Methods */
	void addButton (string name);
	void removeButton (string name);
	void clearButtons ();

	string getFocusedButton ();

	/* Common Methods */
	virtual void draw ();
	virtual void input (int key);
};

#endif
