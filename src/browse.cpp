/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */

#include <gtkmm/application.h>

#include "Browser.h"

int main(int argc, char* argv[]) {
	auto app = Gtk::Application::create("com.frisiapp.cf.browser-engineering");
	return app->make_window_and_run<Browser>(argc, argv);
}
