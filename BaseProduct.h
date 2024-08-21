#pragma once

class BaseProduct {
public: 
	virtual void process() const = 0;
	virtual ~BaseProduct() = default; 
};