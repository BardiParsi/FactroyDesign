#pragma once

#include "ProductWithID.h"
#include <chrono>
#include <thread>

import LOGGER;

class ConcreteProductA : public ProductWithID {
public:
	explicit ConcreteProductA(int id) : ProductWithID(id) {}
	void process() const override {
		INFO("PRODUCT A is going to be processed. "); 
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		INFO("the process for PRODUCT A is done. ");
	}
};