#ifndef GRAPHIC_TERMINAL_H
#define GRAPHIC_TERMINAL_H

#if defined(__linux__) || defined(__MINGW32__)
# define HAS_CURSES
#	include <ncurses.h>
#elif defined(_MSC_VER)
#	define HAS_WINTERM
#	include <conio.h>
#	include <Windows.h>
#	include <stdio.h>
#else
#	error "Platform not supported"
#endif

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#if defined(HAS_CURSES)
#	define GTERM_KEY_LEFT 		 4
# define GTERM_KEY_RIGHT 		 5
# define GTERM_KEY_UP 			 3
# define GTERM_KEY_DOWN 		 2
# define GTERM_KEY_BACKSPACE 127
# define GTERM_KEY_ENTER		'\n'
#elif defined(HAS_WINTERM)
# define GTERM_KEY_LEFT			2
# define GTERM_KEY_RIGHT		3
# define GTERM_KEY_UP			4
# define GTERM_KEY_DOWN			5
# define GTERM_KEY_BACKSPACE	'\b'
# define GTERM_KEY_ENTER		'\r'
#endif

#if defined(HAS_WINTERM)
#	define COLOR_BLACK   0
#	define COLOR_RED     1
#	define COLOR_GREEN   2
#	define COLOR_YELLOW  3
#	define COLOR_BLUE    4
#	define COLOR_MAGENTA 5
#	define COLOR_CYAN    6
#	define COLOR_WHITE   7
#	define NR_COLORS	 8

static const WORD GTERM_COLORS[NR_COLORS] = {
	FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,
	BACKGROUND_RED | BACKGROUND_INTENSITY,
	FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN,
	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY
};
#endif

inline void gterm_begin () {
	#if defined(HAS_CURSES)
	initscr ();
	noecho ();
	start_color ();
	use_default_colors ();
	curs_set (0);
	keypad (stdscr, 1);

	for (unsigned i = 0; i < 8; i++)
		init_pair (i + 1, COLOR_WHITE, i);
	init_pair (COLOR_RED + 1, COLOR_BLACK, COLOR_RED);
	init_pair (COLOR_YELLOW + 1, COLOR_BLACK, COLOR_YELLOW);
	init_pair (COLOR_CYAN + 1, COLOR_BLACK, COLOR_CYAN);
	init_pair (COLOR_WHITE + 1, COLOR_BLACK, COLOR_WHITE);
	#endif
}

inline int gterm_getch () {
	#if defined(HAS_CURSES)
	return getch ();
	#elif defined(HAS_WINTERM)
	int c = getch ();
	if (c == 0x00 || c == 0xE0) {
		c = getch ();
		if (c == 72) return GTERM_KEY_UP;
		else if (c == 80) return GTERM_KEY_DOWN;
		else if (c == 75) return GTERM_KEY_LEFT;
		else if (c == 77) return GTERM_KEY_RIGHT;
		else return 0;
	}
	else {
		return c;
	}
	#endif
}	

inline void gterm_clear () {
	#if defined(HAS_CURSES)
	clear ();
	#elif defined(HAS_WINTERM)
	system ("cls");
	#endif
}

inline void gterm_end () {
	#if defined(HAS_CURSES)
	endwin ();
	#endif
}

#if defined(HAS_CURSES)
#	define gterm_printf(x, y, ...) {	\
		mvprintw (y, x, __VA_ARGS__);		\
		refresh ();											\
	}
#elif defined(HAS_WINTERM)
#	define gterm_printf(x, y, ...) {	\
		HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);		\
		_COORD coord = { x, y };								\
		SetConsoleCursorPosition(hconsole, coord);				\
		printf (__VA_ARGS__);									\
	}
#endif

#if defined(HAS_CURSES)
#	define gterm_cprintf(x, y, c, ...) {	\
		attron (COLOR_PAIR (c + 1));		\
		mvprintw (y, x, __VA_ARGS__);		\
		attroff (COLOR_PAIR (c + 1));		\
		refresh ();											\
	}
#elif defined(HAS_WINTERM)
#	define gterm_cprintf(x, y, c, ...) {	\
		HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);		\
		_COORD coord = { x, y };								\
		SetConsoleCursorPosition(hconsole, coord);				\
		SetConsoleTextAttribute(hconsole, GTERM_COLORS[c]);	\
		printf (__VA_ARGS__);									\
		SetConsoleTextAttribute(hconsole, GTERM_COLORS[COLOR_BLACK]);	\
	}
#endif

#if defined(HAS_CURSES)
#	define gterm_whprintf(x, y, w, h, ...) {	\
		if (h > 0) {														\
			char buf[4096];												\
			char *ptr;														\
			unsigned hoff = 0;										\
																						\
			sprintf (buf, __VA_ARGS__);						\
			ptr = strtok (buf, "\n");							\
			do { 																								\
				mvprintw (y + hoff, x, "%-*.*s", w, w, ptr);						\
				hoff++;																						\
			}	while ((ptr = strtok (NULL, "\n")) && hoff < h);	\
			refresh ();														\
		}																				\
	}
#elif defined(HAS_WINTERM)
#	define gterm_whprintf(x, y, w, h, ...) {	\
		HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);		\
		_COORD coord;								\
		if (h > 0) {														\
			char buf[4096];												\
			char *ptr;														\
			unsigned hoff = 0;										\
																						\
			sprintf (buf, __VA_ARGS__);						\
			ptr = strtok (buf, "\n");							\
			do { 																								\
				coord.X = x; coord.Y = y + hoff;								\
				SetConsoleCursorPosition(hconsole, coord);				\
				printf ("%-*.*s", w, w, ptr);									\
				hoff++;																						\
			}	while ((ptr = strtok (NULL, "\n")) && hoff < h);	\
		}																				\
	}
#endif

#if defined(HAS_CURSES)
#	define gterm_whcprintf(x, y, w, h, c, ...) {	\
		if (h > 0) {														\
			char buf[4096];												\
			char *ptr;														\
			unsigned hoff = 0;										\
																						\
			attron (COLOR_PAIR (c + 1));					\
			sprintf (buf, __VA_ARGS__);						\
			ptr = strtok (buf, "\n");							\
			do { 																								\
				mvprintw (y + hoff, x, "%-*.*s", w, w, ptr);						\
				hoff++;																						\
			}	while ((ptr = strtok (NULL, "\n")) && hoff < h);	\
			for (; hoff < h; hoff++) {						\
				mvprintw (y + hoff, x, "%*c", w, ' ');	\
			}																			\
			attroff (COLOR_PAIR (c + 1));					\
			refresh ();														\
		}																				\
	}
#elif defined(HAS_WINTERM)
#	define gterm_whcprintf(x, y, w, h, c, ...) {	\
		HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);		\
		_COORD coord;								\
		if (h > 0) {														\
			char buf[4096];												\
			char *ptr;														\
			unsigned hoff = 0;										\
																						\
			SetConsoleTextAttribute(hconsole, GTERM_COLORS[c]);	\
			sprintf (buf, __VA_ARGS__);						\
			ptr = strtok (buf, "\n");							\
			do { 																								\
				coord.X = x; coord.Y = y + hoff;								\
				SetConsoleCursorPosition(hconsole, coord);				\
				printf ("%-*.*s", w, w, ptr);									\
				hoff++;																						\
			}	while ((ptr = strtok (NULL, "\n")) && hoff < h);	\
			for (; hoff < h; hoff++) {						\
				coord.X = x; coord.Y = y + hoff;								\
				SetConsoleCursorPosition(hconsole, coord);				\
				printf ("%*c", w, ' ');									\
			}																			\
			SetConsoleTextAttribute(hconsole, GTERM_COLORS[COLOR_BLACK]);	\
		}																				\
	}
#endif

#endif
