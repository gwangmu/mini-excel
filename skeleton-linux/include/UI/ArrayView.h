#ifndef ASSN2_ARRAY_VIEW_H
#define ASSN2_ARRAY_VIEW_H

#include "UI/UIObject.h"
#include "UI/ColorLabel.h"
#include <vector>

using namespace std;

class ArrayView : public UIObject {
public:
	/* Event Handlers */
	UICallback onFocusChanged;

private:
	typedef vector<ColorLabel *> ColorLabelVector;

	const unsigned cellwidth;
	const unsigned xcells, ycells;

	vector<ColorLabelVector> tblCells;
	ColorLabel *uobjFCell;
	int focusX, focusY;
	int orgX, orgY;

	void drawBorder ();
	void drawCells ();
	void drawFocusedCell ();

public:
	/* Constructor/Destructor */
	ArrayView (string name, unsigned left, unsigned top,
			unsigned xcells, unsigned ycells, unsigned wcell,
			unsigned nrow, unsigned ncol);
	~ArrayView ();

	/* Getter/Setter */
	unsigned getNumRows ();
	unsigned getNumColumns ();
	unsigned setNumRows ();
	unsigned setNumColumns ();

	unsigned getFocusedRow ();
	unsigned getFocusedColumn ();

	string getCaption (unsigned row, unsigned col);
	void setCaption (unsigned row, unsigned col, string msg);
	void setCaptionColor (unsigned row, unsigned col, unsigned color);

	/* Methods */
	virtual void draw ();
	virtual void input (int key);
};

#endif
