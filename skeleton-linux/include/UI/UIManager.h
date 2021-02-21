#ifndef ASSN2_UI_MANAGER_H
#define ASSN2_UI_MANAGER_H

#include "UI/UIObject.h"
#include <list>

using namespace std;

class UIManager {
private:
	list<UIObject *> lstUObjs;

	/* Manager States */
	int esccount;
	list<UIObject *>::iterator iuobjFocused;

	/* Private Methods */
	void redraw ();
	void moveFocus ();

public:
	/* Constructor/Destructor */
	UIManager ();
	~UIManager ();

	/* UIObject Manager Methods */
	void addUIObject (UIObject *uobj);
	UIObject* getUIObject (string name);
	void removeUIObject (UIObject *uobj);
	void removeUIObjectByName (string name);
	void clearUIObjects ();

	/* UI Manager Methods */
	void run ();
};

#endif
