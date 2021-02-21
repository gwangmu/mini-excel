#ifndef ASSN2_UI_OBJECT_H
#define ASSN2_UI_OBJECT_H

#include <string>
#include "UI/UICallback.h"
#include "UI/gterm.h"

using namespace std;

class UIManager;

class UIObject {
friend class UIManager;
public:
	/* Event Handlers */
	UICallback onMoved;
	UICallback onShowed;
	UICallback onHidden;

private:
	unsigned left, top, width, height;
	UIManager *uiman;
	void (UIManager::*redrawAll) ();

	bool visible;
	bool focusible;
	bool focused;
	string name;

public:
	/* Constructor */
	UIObject (string name, unsigned left, unsigned top,
			unsigned width, unsigned height, bool focusible);

	/* Methods */
	bool isVisible ();
	void show ();
	void hide ();
	
	bool isFocusible ();
	bool isFocused ();
	void setFocus ();
	void unsetFocus ();

	string getName ();

	void setLeft (unsigned val);
	void setTop (unsigned val);
	void setWidth (unsigned val);
	void setHeight (unsigned val);

	unsigned getLeft ();
	unsigned getTop ();
	unsigned getWidth ();
	unsigned getHeight ();

	/* Interfaces */
	virtual void draw () = 0;
	virtual void input (int key) = 0;
};

#endif
