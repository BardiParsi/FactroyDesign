#pragma once

#include "ProductWithID.h"
#include <chrono>
#include <thread>

import LOGGER;

class ConcreteProductB : public ProductWithID {
public:
	explicit ConcreteProductB(int id) : ProductWithID(id) {}
	void process() const override {
		INFO("PRODUCT B is going to be processed. ");
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		INFO("the process for PRODUCT B is done. ");
	}
};