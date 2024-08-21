export module LOGGER;

import <string>;
import <iostream>;
import <sstream>;
// LOGGER.ixx
// This module provides logging functionality for the application.
// Export the INFO function from the LOGGER module
// This function outputs informational messages to the console
export void INFO(const std::string& message);