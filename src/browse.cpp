/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <iostream>

#include "UI/Browser.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Please pass the URL to open as the first argument" << std::endl;
		return 1;
	}
	auto browser = UI::Browser::create(argv[1]);
	return browser->run();
}
