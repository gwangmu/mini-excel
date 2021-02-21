#include <cassert>
#include "UI/UIManager.h"
#include "UI/gterm.h"

UIManager::UIManager () {
	gterm_begin ();
	esccount = 0;
}

UIManager::~UIManager () {
	clearUIObjects ();
	gterm_end ();
}


/* @detail redraw all UIObjects. */
void UIManager::redraw () {
	gterm_clear ();
	for (list<UIObject *>::iterator it = lstUObjs.begin ();
			 it != lstUObjs.end (); it++) {
		if ((*it)->isVisible ()) {
			(*it)->draw ();
		}
	}
}

void UIManager::moveFocus () {
	(*iuobjFocused)->unsetFocus ();

	for (iuobjFocused++; iuobjFocused != lstUObjs.end (); iuobjFocused++) {
		if ((*iuobjFocused)->isFocusible ())
			break;
	}

	if (iuobjFocused == lstUObjs.end ())
		iuobjFocused = lstUObjs.begin ();

	(*iuobjFocused)->setFocus ();
}


void UIManager::addUIObject (UIObject *uobj) {
	uobj->uiman = this;
	uobj->redrawAll = &UIManager::redraw;
	lstUObjs.insert (lstUObjs.end (), uobj);

	redraw ();
}

/* @detail get a UIObject named 'name'. */
UIObject* UIManager::getUIObject (string name) {
	for (list<UIObject *>::iterator it = lstUObjs.begin ();
			 it != lstUObjs.end (); it++) {
		if ((*it)->getName () == name)
			return (*it);
	}

	return NULL;
}

/* @detail remove the UIObject 'uobj'. */
void UIManager::removeUIObject (UIObject *uobj) {
	list<UIObject *>::iterator it = lstUObjs.begin ();

	while (it != lstUObjs.end ()) {
		if ((*it) == uobj) {
			delete (*it);
			lstUObjs.erase (it);
			break;
		}
		else
			it++;
	}

	redraw ();
}

/* @detail remove the UIObject, whose name is 'name'. */
void UIManager::removeUIObjectByName (string name) {
	removeUIObject (getUIObject (name));
}

/* @detail clear all registered UIObjects. */
void UIManager::clearUIObjects () {
	for (list<UIObject *>::iterator it = lstUObjs.begin ();
			 it != lstUObjs.end (); it++) {
		delete (*it);
	}

	lstUObjs.clear ();

	redraw ();
}


/* @detail run UIManager, monopolizing program control
 *  until the program terminates */
void UIManager::run () {
	esccount = 0;
	iuobjFocused = lstUObjs.begin ();
	(*iuobjFocused)->setFocus ();
	redraw ();

	while (esccount < 2) {
		char c = gterm_getch ();
		
		if (c == 9) {					// KEY: tab
			moveFocus ();
			esccount = 0;
			redraw ();
		}
		//else if (c == 27) {
		//	esccount++;
		//}
		else {
			(*iuobjFocused)->input (c);
			esccount = 0;
		}
	}
}
