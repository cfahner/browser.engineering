/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <gdk/gdkkeysyms.h>
#include <gtkmm/eventcontrollerkey.h>
#include <memory>
#include <string>
#include <iostream>

#include "BrowserWindow.h"
#include "../HTML/Parser.h"
#include "../HTTP/Header.h"
#include "../HTTP/Method.h"
#include "../HTTP/NetworkException.h"
#include "../HTTP/Request.h"
#include "../HTTP/Response.h"
#include "../HTTP/URL.h"
#include "../HTTP/URLParseException.h"

namespace UI {

BrowserWindow::BrowserWindow() {
	maximize();
	set_child(m_document_view);

	std::shared_ptr<Gtk::EventControllerKey> controller = Gtk::EventControllerKey::create();
	controller->signal_key_released().connect(sigc::mem_fun(*this, &BrowserWindow::on_key_released), false);
	add_controller(controller);
}

void BrowserWindow::visit(std::string_view url_string) {
	try {
		HTTP::Response response{fetch_url(url_string)};
		m_document_view.display_html(response.body);
	} catch (HTTP::NetworkException& ne) {
		std::cerr << "Network error: " << ne.what() << std::endl;
	} catch (HTTP::URLParseException& upe) {
		std::cerr << "Could not parse URL: " << upe.what() << std::endl;
	}
}

HTTP::Response BrowserWindow::fetch_url(std::string_view url_string) {
	if (url_string.length() >= 5 && url_string.substr(0, 5) == "data:") {
		return HTTP::Response::from_data_uri(url_string);
	}
	HTTP::Request request = create_request(HTTP::Method::GET, HTTP::URL::parse_string(url_string));
	return request.send();
}

HTTP::Request BrowserWindow::create_request(HTTP::Method method, HTTP::URL url) {
	HTTP::Request request{method, url};
	request.headers.push_back(HTTP::Header{"user-agent", "CFahnerBrowser"});
	return request;
}

void BrowserWindow::on_key_released(guint key_value, guint, Gdk::ModifierType) {
	if (key_value == GDK_KEY_Down) {
		m_document_view.scroll(KEY_SCROLL_AMOUNT);
	} else if (key_value == GDK_KEY_Up) {
		m_document_view.scroll(-KEY_SCROLL_AMOUNT);
	}
}

}
