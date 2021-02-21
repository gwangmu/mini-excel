#include <cstdlib>
#include "UI/UIObject.h"

using namespace std;

UIObject::UIObject (string name, unsigned left, unsigned top,
		unsigned width, unsigned height, bool focusible) {
	this->name = name;
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
	this->redrawAll = NULL;

	this->visible = true;
	this->focusible = focusible;
	this->focused = false;

	this->onMoved = UICallback ();
	this->onShowed = UICallback ();
	this->onHidden = UICallback ();
}


bool UIObject::isVisible () {
	return visible;
}

void UIObject::show () {
	visible = true;
	if (redrawAll) (uiman->*redrawAll) ();
	onShowed.emit (this);
}

void UIObject::hide () {
	visible = false;
	if (redrawAll) (uiman->*redrawAll) ();
	onHidden.emit (this);
}


bool UIObject::isFocusible () {
	return focusible;
}

bool UIObject::isFocused () {
	return (focusible && focused);
}

void UIObject::setFocus () {
	focused = true;
}

void UIObject::unsetFocus () {
	focused = false;
}


string UIObject::getName () {
	return name;
}


void UIObject::setLeft (unsigned val) {
	left = val;
	if (redrawAll) (uiman->*redrawAll) ();
	onMoved.emit (this);
}

void UIObject::setTop (unsigned val) {
	top = val;
	if (redrawAll) (uiman->*redrawAll) ();
	onMoved.emit (this);
}

void UIObject::setWidth (unsigned val) {
	width = val;
	if (redrawAll) (uiman->*redrawAll) ();
	onMoved.emit (this);
}

void UIObject::setHeight (unsigned val) {
	height = val;
	if (redrawAll) (uiman->*redrawAll) ();
	onMoved.emit (this);
}


unsigned UIObject::getLeft () {
	return left;
}

unsigned UIObject::getTop () {
	return top;
}

unsigned UIObject::getWidth () {
	return width;
}

unsigned UIObject::getHeight () {
	return height;
}
