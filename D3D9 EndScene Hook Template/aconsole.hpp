#pragma once
#include <Windows.h>
#include <memory>
#include "agui.hpp"
#include "ainput.hpp"


namespace aconsole
{
	constexpr int MAX_LENGTH   = 150;
	constexpr int MAX_ELEMENTS =  11;
	constexpr int MAX_WATCHLIST = 7;

	// THIS ARE YOUR SETTINGS
	struct settings_console {

		bool wnd_b;
		int wnd_i;

		int  lastElement = 0;
		char console_str[MAX_ELEMENTS][MAX_LENGTH];
		char watch_str[MAX_ELEMENTS][MAX_LENGTH];
	};

	class gui_console
	{
		bool m_initSettings;
		bool m_initConsole;
		bool m_cleanedUp;

		char* arr[MAX_ELEMENTS];
		int	  currentPos;

		agui::guiFunc* guiFuncConsole;
		std::vector<agui::guiObj*> container;

	public:
		gui_console();
		~gui_console();

		// THIS MUST BE CALLED
		void initSettings();
		void initConsole();
		void drawConsole();
		void cleanUpConsole();

		void printToConsole(const char* str);
		void printToWatchList(int pos, const char* str);
	};

	extern std::unique_ptr<settings_console> sConsole;
	extern std::unique_ptr<gui_console> gConsole;
}