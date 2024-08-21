module LOGGER;

import <iostream>;
import <sstream>;
import <string>;

using std::cout;
using std::endl;

// LOGGER.cpp
// This file provides the implementation for the logging functions declared in LOGGER.ixx.

void INFO(const std::string& message) {
	std::stringstream ss;
	ss << message;
	cout << ss.str() << endl;
}