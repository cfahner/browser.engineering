/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <gtkmm/application.h>
#include <string>

#include "Browser.h"
#include "BrowserWindow.h"

namespace UI {

Glib::RefPtr<Browser> Browser::create() {
	return Glib::make_refptr_for_instance<Browser>(new Browser());
}

Glib::RefPtr<Browser> Browser::create(std::string initial_url) {
	return Glib::make_refptr_for_instance<Browser>(new Browser(initial_url));
}

Browser::Browser()
	: Browser("")
{
}

Browser::Browser(std::string initial_url)
	: Gtk::Application("com.frisiapp.cf.browser-engineering")
	, m_initial_url(initial_url)
{
}

void Browser::on_activate() {
	auto browser_window = create_browser_window();
	browser_window->present();
	if (m_initial_url.length() > 0) {
		browser_window->visit(m_initial_url);
	}
}

BrowserWindow* Browser::create_browser_window() {
	auto browser_window = new BrowserWindow();
	add_window(*browser_window);
	browser_window->signal_hide().connect([browser_window]() { delete browser_window; });
	return browser_window;
}

}
