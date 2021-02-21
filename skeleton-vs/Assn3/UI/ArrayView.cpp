#include "UI/ArrayView.h"

using namespace std;

ArrayView::ArrayView (string name, unsigned left,
		unsigned top, unsigned xcells, unsigned ycells,
		unsigned wcell, unsigned nrow, unsigned ncol) :
	UIObject (name, left, top, xcells * (wcell + 1) + 1, ycells * 2 + 1, true),
	cellwidth (wcell), xcells (xcells), ycells (ycells) {
	this->focusX = 0;
	this->focusY = 0;
	this->orgX = 0;
	this->orgY = 0;

	if (nrow < 1) nrow = 1;
	if (ncol < 1) ncol = 1;

	for (unsigned i = 0; i < nrow; i++) {
		tblCells.push_back (ColorLabelVector ());
		ColorLabelVector &column = tblCells[i];

		for (unsigned j = 0; j < ncol; j++) {
			column.push_back (new ColorLabel ("label", left + (wcell + 1) * j + 1, 
				top + 2 * i + 1, wcell, 1));
		}
	}

	uobjFCell = new ColorLabel ("focused", left + 1, top + 1, wcell, 1);
	uobjFCell->setColor (COLOR_YELLOW);
};

ArrayView::~ArrayView () {
	for (unsigned i = 0; i < tblCells.size (); i++) {
		for (unsigned j = 0; j < tblCells[i].size (); j++) {
			delete tblCells[i][j];
		}
	}

	delete uobjFCell;
}


string ArrayView::getCaption (unsigned row, unsigned col) {
	if (row >= tblCells.size () || col >= tblCells[row].size ())
		return string ();

	return tblCells[row][col]->getCaption ();
}

void ArrayView::setCaption (unsigned row, unsigned col, string msg) {
	if (row >= tblCells.size () || col >= tblCells[row].size ()) return;

	ColorLabel *uobjLabel = tblCells[row][col];
	string old_caption = uobjLabel->getCaption ();
	uobjLabel->setCaption (msg);

	if (row == focusY && col == focusX)
		uobjFCell->setCaption (msg);
}

void ArrayView::setCaptionColor (unsigned row, unsigned col, unsigned color) {
	if (row >= tblCells.size () || col >= tblCells[row].size ()) return;

	tblCells[row][col]->setColor (color);
}


unsigned ArrayView::getFocusedRow () {
	return focusY;
}

unsigned ArrayView::getFocusedColumn () {
	return focusX;
}


void ArrayView::drawBorder () {
	for (unsigned i = 1; i < getHeight () - 1; i++) {
		gterm_printf (getLeft (), getTop () + i, "|");
		gterm_printf (getLeft () + getWidth () - 1, getTop () + i, "|");
	}
	for (unsigned i = 0; i < getWidth (); i++) {
		gterm_printf (getLeft () + i, getTop (), "-");
		gterm_printf (getLeft () + i, getTop () + getHeight () - 1, "-");
	}

	for (unsigned i = 1; i < getHeight () - 1; i++) {
		if (i % 2 == 0) continue;
		for (unsigned xoff = cellwidth + 1; xoff < getWidth () - (cellwidth + 1); xoff += (cellwidth + 1)) 
			gterm_printf (getLeft () + xoff, getTop () + i, "|");
	}
	for (unsigned i = 1; i < getWidth () - 1; i++) {
		if (i % (cellwidth + 1) == 0) continue;
		for (unsigned yoff = 2; yoff < getHeight () - 2; yoff += 2) 
			gterm_printf (getLeft () + i, getTop () + yoff, "-");
	}

	for (unsigned xoff = cellwidth + 1; xoff < getWidth () - (cellwidth + 1); xoff += (cellwidth + 1)) {
		for (unsigned yoff = 2; yoff < getHeight () - 2; yoff += 2) {
			gterm_printf (getLeft () + xoff, getTop () + yoff, "+");
		}
	}
}


void ArrayView::drawCells () {
	for (unsigned i = orgX; i < orgX + xcells && i < tblCells.size (); i++) {
		for (unsigned j = orgY; j < orgY + ycells && j < tblCells[i].size (); j++) {
			tblCells[j][i]->setLeft (getLeft () + 1 + (i - orgX) * (cellwidth + 1));
			tblCells[j][i]->setTop (getTop () + 1 + (j - orgY) * 2);
			tblCells[j][i]->draw ();
		}
	}
}

void ArrayView::drawFocusedCell () {
	if (isFocused ())
		uobjFCell->setColor (COLOR_YELLOW);
	else
		uobjFCell->setColor (COLOR_WHITE);

	uobjFCell->setCaption (tblCells[focusY][focusX]->getCaption ());
	uobjFCell->setLeft (getLeft () + 1 + (focusX - orgX) * (cellwidth + 1));
	uobjFCell->setTop (getTop () + 1 + (focusY - orgY) * 2);
	uobjFCell->draw ();
}

void ArrayView::draw () {
	drawBorder ();
	drawCells ();
	drawFocusedCell ();
}

void ArrayView::input (int key) {
	int old_focusX = focusX;
	int old_focusY = focusY;
	bool redraw_cells = false;

	switch (key) {
		case GTERM_KEY_LEFT:
			if (focusX - 1 >= 0) focusX--;
			if (focusX < orgX) {
				orgX--;
				redraw_cells = true;
			}
			break;
		case GTERM_KEY_RIGHT:
			if (focusX + 1 < tblCells.size ()) focusX++;
			if (focusX >= orgX + xcells) {
				orgX++;
				redraw_cells = true;
			}
			break;
		case GTERM_KEY_UP:
			if (focusY - 1 >= 0) focusY--;
			if (focusY < orgY) {
				orgY--;
				redraw_cells = true;
			}
			break;
		case GTERM_KEY_DOWN:
			if (focusY + 1 < tblCells[0].size ()) focusY++;
			if (focusY >= orgY + ycells) {
				orgY++;
				redraw_cells = true;
			}
			break;			
		default:
			return;
	}

	if (old_focusX != focusX || old_focusY != focusY) {
		if (redraw_cells)
			drawCells ();
		else 
			tblCells[old_focusY][old_focusX]->draw ();
		
		drawFocusedCell ();

		onFocusChanged.emit (this);
	}
}

