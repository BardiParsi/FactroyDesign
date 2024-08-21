export module ExtractID;
#include "BaseProduct.h"
#include "ProductWithID.h"
#include "ConcreteProductA.h"
#include "ConcreteProductB.h"
#include "TempProduct.h"
import <vector>;
import <tuple>;
import <memory>;
import <string>;
import <atomic>;
import <iostream>; 

class BaseProduct;
class ProductWithID;
class ConcreteProductA;
class ConcreteProductB;


export std::vector<int> extractID(const std::vector<std::unique_ptr<BaseProduct>>& products) {
	std::vector<int> vecID;
	for (const auto& p : products) {
		const ProductWithID* productID = dynamic_cast<const ProductWithID*>(p.get());
		if (productID) {
			vecID.push_back(productID->getID());
		}
	}
	return vecID;
}

