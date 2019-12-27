#include "stdafx.h"
#include "aconsole.hpp"

namespace aconsole
{
	using namespace agui;

	std::unique_ptr<settings_console> sConsole = std::make_unique<settings_console>();
	std::unique_ptr<gui_console> gConsole = std::make_unique<gui_console>();
	
	gui_console::gui_console()
		: m_initSettings(false), m_initConsole(false), m_cleanedUp(false),
		guiFuncConsole(nullptr)
	{
	}

	gui_console::~gui_console()
	{
	}

	void gui_console::initSettings()
	{
		if (m_initSettings == true)
			return;

		sConsole->wnd_b = true;
		sConsole->wnd_i = VK_INSERT;
		currentPos = 0;

		for (int i = 0; i < MAX_ELEMENTS; i++)
		{
			sConsole->console_str[i][0] = '\0';
			sConsole->watch_str[i][0]   = '\0';
		}

		m_initSettings = true;
	}

	void gui_console::initConsole()
	{
		if (m_initConsole == true)
			return;

		for (int i = 0; i < MAX_ELEMENTS; i++)
		{
			arr[i] = sConsole->console_str[i];
		}

		guiFuncConsole = new guiFunc;
		setGuiFunc(guiFuncConsole);
		guiFuncConsole->init();

		container.push_back(new  window("WindowName", &sConsole->wnd_b, &sConsole->wnd_i, 100, 100, 490, 290));
		container.push_back(new  titlebar("Console - Press [INSERT]"));
		container.push_back(new  ribbon("ribbonbar"));
		container.push_back(new  tab("Console"));
		container.push_back(new  frame(""));
		container.push_back(new  consoleLabel("", &arr[0]));
		container.push_back(new  consoleLabel("", &arr[1]));
		container.push_back(new  consoleLabel("", &arr[2]));
		container.push_back(new  consoleLabel("", &arr[3]));
		container.push_back(new  consoleLabel("", &arr[4]));
		container.push_back(new  consoleLabel("", &arr[5]));
		container.push_back(new  consoleLabel("", &arr[6]));
		container.push_back(new  consoleLabel("", &arr[7]));
		container.push_back(new  consoleLabel("", &arr[8]));
		container.push_back(new  consoleLabel("", &arr[9]));
		container.push_back(new  consoleLabel("", &arr[10]));


		container.push_back(new  tab("Watch"));
		container.push_back(new  frame(""));

		//[ Position ] [ File, Line ] [ Function ] >> Output");
		container.push_back(new  label(sConsole->watch_str[0]));
		container.push_back(new  label(sConsole->watch_str[1]));
		container.push_back(new  label(sConsole->watch_str[2]));
		container.push_back(new  label(sConsole->watch_str[3]));
		container.push_back(new  label(sConsole->watch_str[4]));
		container.push_back(new  label(sConsole->watch_str[5]));
		container.push_back(new  label(sConsole->watch_str[6]));
		container.push_back(new  label(sConsole->watch_str[7]));

		m_initConsole = true;
	}

	void gui_console::cleanUpConsole()
	{
		if (m_cleanedUp == true)
			return;

		m_cleanedUp = true;

		for (auto o : container)
			free(o);
	}


	void gui_console::drawConsole() 
	{
		if (m_initSettings == false)
			return;

		if (m_initConsole == false)
			return;

		if (m_cleanedUp == true)
			return;

		// Resort Array
		int j = sConsole->lastElement;
		for (int i = 0; i < MAX_ELEMENTS; i)
		{
			if (++j == MAX_ELEMENTS)
				j = 0;

			arr[i] = sConsole->console_str[j];
		}

		setGuiFunc(guiFuncConsole);
		guiFuncConsole->drawAll();
	}

	void gui_console::printToConsole(const char* str)
	{
		if (m_initSettings == false)
			return;

		if (++sConsole->lastElement == MAX_ELEMENTS)
			sConsole->lastElement = 0;

		sprintf_s(sConsole->console_str[sConsole->lastElement], MAX_LENGTH, str);
	}

	void gui_console::printToWatchList(int pos, const char* str)
	{
		if (m_initSettings == false)
			return;

		if (pos > MAX_WATCHLIST)
			pos = MAX_WATCHLIST - 1;

		sprintf_s(sConsole->watch_str[pos], MAX_LENGTH, str);
	}

}