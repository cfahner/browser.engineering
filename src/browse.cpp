/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */

#include <iostream>
#include <string>

#include "Browser.h"

int main(void) {
	Browser browser{};
	std::cout << "Type URL: ";
	std::string url_string{""};
	std::getline(std::cin, url_string);
	browser.visit(url_string);
	return 0;
}
