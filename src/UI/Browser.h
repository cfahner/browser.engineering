/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <gtkmm/application.h>
#include <string>

#include "BrowserWindow.h"

namespace UI {

// https://gnome.pages.gitlab.gnome.org/gtkmm-documentation/chapter-building-applications.html

class Browser : public Gtk::Application {
private:
	std::string m_initial_url;

public:
	static Glib::RefPtr<Browser> create();
	static Glib::RefPtr<Browser> create(std::string initial_url);

protected:
	Browser();
	Browser(std::string initial_url);
	void on_activate() override;

private:
	BrowserWindow* create_browser_window();

};

}
