#include "stdafx.h"
#include "amenu.hpp"

namespace amenu
{
	using namespace agui;

	std::unique_ptr<settings_menu> sMenu = std::make_unique<settings_menu>();
	std::unique_ptr<gui_menu> gMenu = std::make_unique<gui_menu>();

	char* cmb1_sz[] = { "test", "test2", "test3" };
	char* cmb2_sz[]{ "Value 1", "Value 2", "Value 3", "Value 4" };

	gui_menu::gui_menu()
		: m_initSettings(false), m_initMenu(false), m_cleanedUp(false)
	{
	}

	gui_menu::~gui_menu()
	{
	}

	void gui_menu::initSettings()
	{
		if (m_initSettings == true)
			return;

		sMenu->wnd_b = true;
		sMenu->wnd_key = VK_HOME;
		sMenu->btn1_b = false;
		sMenu->btn2_b = false;
		sMenu->chb1_b = false;
		sMenu->chb2_b = true;
		sMenu->sli1_i = 20;
		sMenu->sli2_i = 120;
		sprintf_s(sMenu->txt1_str, ARRAYSIZE(sMenu->txt1_str), "text 1");
		sprintf_s(sMenu->txt2_str, ARRAYSIZE(sMenu->txt2_str), "");
		//char txt1_str[50];
		//char txt2_str[50];
		sMenu->hky1_i = VK_SPACE;
		sMenu->hky2_i = VK_LEFT;
		sprintf_s(sMenu->tb1_sz, ARRAYSIZE(sMenu->tb1_sz), "Textbox 1");
		sprintf_s(sMenu->tb2_sz, ARRAYSIZE(sMenu->tb2_sz), "Textbox 2");
		sMenu->cmb1_i = 1;
		sMenu->cmb2_i = 0;
		
		m_initSettings = true;
	}

	void gui_menu::initMenu()
	{
		if (m_initMenu == true)
			return;

		guiFuncMenu = new guiFunc;
		setGuiFunc(guiFuncMenu);
		guiFuncMenu->init();

		container.push_back(new  window("WindowName", &sMenu->wnd_b, &sMenu->wnd_key, 700, 100, 490, 290));
		container.push_back(new  titlebar("Titlebar - Press [HOME]"));
		container.push_back(new  ribbon("ribbonbar"));
		container.push_back(new  tab("Tab 1"));
		container.push_back(new  frame("frame 1"));
		container.push_back(new  button("button 1", &sMenu->btn1_b));
		container.push_back(new  button("button 2", &sMenu->btn2_b));
		container.push_back(new  label(sMenu->txt1_str));
		container.push_back(new  label(sMenu->txt2_str));
		container.push_back(new  checkbox("checkbox 1", &sMenu->chb1_b));
		container.push_back(new  checkbox("checkbox 2", &sMenu->chb2_b));
		container.push_back(new  slider("slider 1", &sMenu->sli1_i, 50));
		container.push_back(new  slider("slider 2", &sMenu->sli2_i, 255));
		container.push_back(new  hotkey("hotkey 1", &sMenu->hky1_i));
		container.push_back(new  hotkey("hotkey 2", &sMenu->hky2_i));

		container.push_back(new textbox(sMenu->tb1_sz));
		container.push_back(new textbox(sMenu->tb2_sz));
		container.push_back(new tab("Tab 2"));
		container.push_back(new frame("frame 2"));
		container.push_back(new combobox("combobox 1", &sMenu->cmb1_i, ARRAYSIZE(cmb1_sz), cmb1_sz));
		container.push_back(new combobox("combobox 2", &sMenu->cmb2_i, ARRAYSIZE(cmb2_sz), cmb2_sz));
		container.push_back(new tab("Tab 3"));
		container.push_back(new frame("frame 3"));
		container.push_back(new tab("Tab 4"));
		container.push_back(new frame("frame 4"));

		m_initMenu = true;
	}

	void gui_menu::cleanUpMenu()
	{
		if (m_cleanedUp == true)
			return;

		m_cleanedUp = true;

		for (auto o : container)
			free(o);
	}

	void gui_menu::drawMenu()
	{
		if (m_initSettings == false)
			return;

		if (m_initMenu == false)
			return;

		if (m_cleanedUp == true)
			return;

		if (sMenu->btn1_b) {
			sprintf_s(sMenu->txt1_str, ARRAYSIZE(sMenu->txt1_str), "button 1 is clicked");
			sMenu->btn1_b = false;
		}
		if (sMenu->btn2_b) {
			sprintf_s(sMenu->txt1_str, ARRAYSIZE(sMenu->txt1_str), "button 2 is clicked");
			sMenu->btn2_b = false;
		}

		POINT mouse = ainput::getMousePos();
		sprintf_s(sMenu->txt2_str, ARRAYSIZE(sMenu->txt2_str), "x: %i, y: %i", mouse.x, mouse.y);

		setGuiFunc(guiFuncMenu);
		guiFuncMenu->drawAll();
	}

}