#pragma once

#include <curses.h>

#ifdef getch
#undef getch
#endif

#ifdef ungetch
#undef ungetch
#endif

#include "Size2.h"
#include "Rectangle.h"
#include "Rgb.h"

namespace re::core
{
	class CursesAdapter final
	{
	private:
		static bool default_terminal_enabled_;

	public:
		CursesAdapter() = delete;

		CursesAdapter(const CursesAdapter& other) = delete;

		CursesAdapter(CursesAdapter&& other) = delete;

		CursesAdapter& operator=(const CursesAdapter& other) = delete;

		CursesAdapter& operator=(CursesAdapter&& other) noexcept = delete;

		~CursesAdapter() = delete;

		static bool IsDefaultCursesTerminalEnabled()
		{
			return default_terminal_enabled_;
		}

		static WINDOW* GetDefaultWindow()
		{
			if (!IsDefaultCursesTerminalEnabled()) {
				EnterDefaultCursesTerminal();
			}

			return stdscr;
		}

		static void EnterDefaultCursesTerminal()
		{
			if (IsDefaultCursesTerminalEnabled()) {
				return;
			}

			default_terminal_enabled_ = true;
			initscr();
		}

		static void ExitCursesTerminal()
		{
			if (!IsDefaultCursesTerminalEnabled())
			{
				return;
			}

			default_terminal_enabled_ = false;
			endwin();
		}

		static void EnableSpecialKeyInput()
		{
			keypad(GetDefaultWindow(), true);
		}

		static void HideCursor()
		{
			curs_set(0);
		}

		static void SetCursorPosition(WINDOW* win, const utility::Size2& p)
		{
			if (GetCursorPosition(win) == p) {
				return;
			}

			wmove(win, p.GetY(), p.GetX());
		}

		static utility::Size2 GetCursorPosition(const WINDOW* win)
		{
			return utility::Size2{
				static_cast<uint16_t>(win->_curx),
					static_cast<uint16_t>(win->_cury)
			};
		}

		static WINDOW* CreateWindowInstance(const utility::Rectangle& rect)
		{
			return newwin(rect.GetHeight(),
				rect.GetWidth(),
				rect.GetTop(),
				rect.GetLeft());
		}

		static void DestroyWindowInstance(WINDOW* win)
		{
			ClearWindow(win);
			UpdateWindow(win);
			delwin(win);
		}

		static utility::Size2 GetWindowPosition(const WINDOW* win)
		{
			return utility::Size2{
				static_cast<uint16_t>(win->_begx),
					static_cast<uint16_t>(win->_begy)
			};
		}

		static void SetWindowPosition(WINDOW* win, const utility::Size2& p)
		{
			mvwin(win, p.GetY(), p.GetX());
		}

		static utility::Size2 GetWindowSize(const WINDOW* win)
		{
			return utility::Size2{
				static_cast<uint16_t>(win->_maxx),
					static_cast<uint16_t>(win->_maxy)
			};
		}

		static utility::Rectangle GetWindowRect(WINDOW* win)
		{
			return {
			GetWindowPosition(win),
			GetWindowPosition(win) + GetWindowSize(win)
			};
		}

		static void SetWindowSize(WINDOW* win, const utility::Size2& size)
		{
			wresize(win, size.GetY(), size.GetX());
		}

		static void UpdateWindow(WINDOW* win)
		{
			wrefresh(win);
		}

		static void FillWindowCell(WINDOW* win, const char ch, const uint32_t attr = 0)
		{
			waddch(win, ch | attr);
		}

		static void ClearWindowCell(WINDOW* win)
		{
			wdelch(win);
			waddch(win, ' ');
		}

		static void ClearWindow(WINDOW* win)
		{
			wclear(win);
		}

		static void ShowWindowBorder(WINDOW* win)
		{
			box(win,
				static_cast<unsigned char>('\xb3'),
				static_cast<unsigned char>('\xc4'));
		}

		static bool CanUseColors()
		{
			return has_colors();
		}

		static void UseDefaultColors()
		{
			start_color();
			use_default_colors();
		}

		static int32_t GetNColors()
		{
			return COLORS;
		}

		static int32_t GetNColorPairs()
		{
			return COLOR_PAIRS;
		}

		static void AddNewColor(const uint16_t index, const Rgb& value)
		{
			init_color(index, value.GetR(), value.GetG(), value.GetB());
			init_pair(index, index, -1);
		}

		static uint32_t GetColor(const uint16_t index)
		{
			return COLOR_PAIR(index);
		}

		static void OverlayWindow(const WINDOW* upper, WINDOW* lower)
		{
			overlay(upper, lower);
		}

		static void OverwriteWindow(const WINDOW* upper, WINDOW* lower)
		{
			overwrite(upper, lower);
		}
	};

	bool CursesAdapter::default_terminal_enabled_ = false;
}
