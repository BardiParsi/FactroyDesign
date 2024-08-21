#pragma once

#include "BaseProduct.h"

import LOGGER;

class ProductWithID : public BaseProduct {
private:
	int id;
public:
	explicit ProductWithID(int id) : id(id) {}
	int getID() const {
		return id;
	}
};