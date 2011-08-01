#pragma once

namespace ns_base
{
	class Console
	{
	public:
		enum Color
		{
			Black       = 0,
			White       = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,//
			Grey        = FOREGROUND_INTENSITY,
			LightGrey   = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE,
			Blue        = FOREGROUND_BLUE,
			Green       = FOREGROUND_GREEN,
			Cyan        = FOREGROUND_GREEN | FOREGROUND_BLUE,
			Red         = FOREGROUND_RED,
			Purple      = FOREGROUND_RED   | FOREGROUND_BLUE,
			LightBlue   = FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
			LightGreen  = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
			LightCyan   = FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
			LightRed    = FOREGROUND_RED   | FOREGROUND_INTENSITY,
			LightPurple = FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
			Orange      = FOREGROUND_RED   | FOREGROUND_GREEN,
			Yellow      = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		};

	public:
		static bool Alloc();
		static bool Free();
		static bool SetTitle (LPCSTR sTitle);
		static bool SetSize (int columns, int lines);
		static bool GetSize (int * pcolumns, int * plines);
		static bool SetCursorPos (int x, int y);
		static bool GetCursorPos (int * px, int * py);
		static bool SetCursorSize (DWORD dwPercentShown, bool bVisible = false);
		static bool SetTextColor (Color FgColor, Color BgColor = Black);
		static bool Clear();

	protected:
		static bool RedirectIoToConsole ();
	};

}