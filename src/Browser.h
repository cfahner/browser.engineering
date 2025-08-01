/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <string>
#include <gtkmm/window.h>

#include "DocumentDisplay.h"
#include "HTTP/Request.h"
#include "HTTP/Method.h"
#include "HTTP/URL.h"

class Browser : public Gtk::Window {
private:
	DocumentDisplay m_document_display;

public:
	Browser();
	void visit(std::string_view url_string);

private:
	HTTP::Request create_request(HTTP::Method method, HTTP::URL url);
	HTTP::Response fetch_url(std::string_view url_string);

};
