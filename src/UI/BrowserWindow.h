/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <gtkmm/window.h>
#include <string>

#include "DocumentView.h"
#include "../HTTP/Method.h"
#include "../HTTP/Request.h"
#include "../HTTP/Response.h"
#include "../HTTP/URL.h"

#define KEY_SCROLL_AMOUNT 60

namespace UI {

class BrowserWindow : public Gtk::Window {
private:
	DocumentView m_document_view{};

public:
	BrowserWindow();
	void visit(std::string_view url_string);

private:
	HTTP::Request create_request(HTTP::Method method, HTTP::URL url);
	HTTP::Response fetch_url(std::string_view url_string);
	void on_key_released(guint key_value, guint key_code, Gdk::ModifierType state);

};

}
