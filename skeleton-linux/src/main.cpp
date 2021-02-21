/**
 * OOP Assignment 3: Mini Excel
 * skeleton by gwangmu (iss300@postech.ac.kr)
 ***/

#include "UI/gterm.h"
#include "UI/UIManager.h"
#include "UI/ColorLabel.h"
#include "UI/MenuStrip.h"
#include "UI/TextBox.h"
#include "UI/ArrayView.h"

#include <cstdlib>
#include <cassert>
#include <cstdio>

UIManager *uimanager;
MenuStrip *uobjMenu;
ColorLabel *uobjColorLabel;
TextBox *uobjTextBox;
ArrayView *uobjArray;

void onFocusChangedAtArrayView (UIObject *emitter);
void onEnterKeyPressedAtTextBox (UIObject *emitter);
void onSelectedAtMenuStrip (UIObject *emitter);
static void initializeUI ();

int main () {
	uimanager = new UIManager ();
	initializeUI ();

	uimanager->run ();

	delete uimanager;
	return 0;
}

static void initializeUI () {
	uobjMenu = new MenuStrip ("menu", 71);
	uobjMenu->addButton ("New");
	uobjMenu->addButton ("Load");
	uobjMenu->addButton ("Save");
	uobjMenu->addButton ("Exit");
	uobjMenu->onSelected.bind<onSelectedAtMenuStrip> ();
	uimanager->addUIObject (uobjMenu);
	
	uobjColorLabel = new ColorLabel ("fx", 0, 1, 8, 1);
	uobjColorLabel->setCaption ("(all)");
	uobjColorLabel->setColor (COLOR_CYAN);
	uimanager->addUIObject (uobjColorLabel);

	uobjTextBox = new TextBox ("textbox", 8, 1, 63);
	uobjTextBox->onEnterKeyPressed.bind<onEnterKeyPressedAtTextBox> ();
	uimanager->addUIObject (uobjTextBox);

	uobjArray = new ArrayView ("array", 0, 2, 7, 10, 9, 24, 24);
	uobjArray->setCaptionColor (0, 0, COLOR_CYAN);
	for (unsigned i = 1; i < 24; i++) {
		uobjArray->setCaptionColor (0, i, COLOR_GREEN);
		uobjArray->setCaption (0, i, string (1, 'A' + i - 1));
	}
	for (unsigned j = 1; j < 24; j++) {
		char buf[30];
		sprintf (buf, "%d", j);

		uobjArray->setCaptionColor (j, 0, COLOR_GREEN);
		uobjArray->setCaption (j, 0, string (buf));
	}
	uobjArray->onFocusChanged.bind<onFocusChangedAtArrayView> ();
	uimanager->addUIObject (uobjArray);
}


void onFocusChangedAtArrayView (UIObject *emitter) {
	/**
	 * TODO: implement here. Following 4 methods would come in handy.
	 *
	 *  @ uobjArray->getFocusedColumn ()
	 *    - Return the index of a focused column.
	 *  @ uobjArray->getFocusedRow ()
	 *    - Return the index of a focused row.
	 *  @ uobjColorLabel->setCaption (string S)
	 *    - Set ColorLabel's caption to a given string S.
	 *  @ uobjTextBox->setText (string S)
	 *    - Set TextBox's text to a given string S.
	 *
	 * You can also use the public methods of UIObjects as you please.
	 * **/

	uobjColorLabel->draw ();
	uobjTextBox->draw ();
}

void onEnterKeyPressedAtTextBox (UIObject *emitter) {
	/**
	 * TODO: implement here, Following 4 methods would come in handy.
	 *
	 *  @ uobjArray->getFocusedColumn ()
	 *    - Return the index of a focused column.
	 *  @ uobjArray->getFocusedRow ()
	 *    - Return the index of a focused row.
	 *  @ uobjTextBox->getText ()
	 *    - Get TextBox's text as a string.
	 *  @ uobjArray->setCaption (unsigned ROW, unsigned COL, string S)
	 *    - Set the (ROW, COL) cell's caption to a given string S.
	 *
	 * You can also use the public methods of UIObjects as you please.
	 * **/

	uobjArray->draw ();
}

void onSelectedAtMenuStrip (UIObject *emitter) {
	string selected = uobjMenu->getFocusedButton ();

	if (selected == "Exit") {
		delete uimanager;
		exit (100);
	}
	else if (selected == "New") {
		/* TODO: implement here */
	}
	else if (selected == "Load") {
		/* TODO: implement here */
	}
	else if (selected == "Save") {
		/* TODO: implement here */
	}	
}
