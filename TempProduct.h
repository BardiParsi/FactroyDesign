#pragma once

#include "BaseProduct.h"
#include <chrono>
#include <thread>

import LOGGER;

class TempProduct : public BaseProduct {
public:
	TempProduct() = default; 
	void process() const override {
		INFO("TEMP PRODUCT is going to be processed. ");
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		INFO("the process for TEMP PRODUCT is done. ");
	}
};