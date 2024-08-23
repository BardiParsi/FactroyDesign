#pragma once

#include "BaseProduct.h"
#include "ProductWithID.h"
#include "ConcreteProductA.h"
#include "ConcreteProductB.h"
#include "TempProduct.h"
#include "ProductTypes.h"
#include <tuple>
#include <memory>
#include <string>
#include <atomic>
#include <variant>

import LOGGER;

// General Factory template
// This template handles creation of products with default parameters
// This class will act as the base class for multiple argument calls
template<typename... Args>
class Factory {
public:
    // General method to create a product; for cases with no specific type parameters
    std::tuple<ProductVariant, Args...> creatProduct(Args... args) const {
        static std::atomic<int> NoIDcounter{ 0 };
        INFO("Creating NO ID TEMP PRODUCT\n");
        NoIDcounter.fetch_add(1, std::memory_order_relaxed);
        ProductVariant product = TempProduct();
        return std::make_tuple(std::move(product), args...);
    }
};
// Specialization for cases with int and std::string
// This specialization is used when creating ConcreteProductA
// This class will act as the recursive empty class when there is no argument left
template<>
class Factory<int, std::string> {
public:
    std::tuple<ProductVariant, int, std::string> creatProduct(int id, int index, const std::string& name) const {
        static std::atomic<int> Acounter{ 0 };
        INFO("Creating PRODUCT A\n");
        Acounter.fetch_add(1, std::memory_order_relaxed);
        ProductVariant product = ConcreteProductA(id);
        return std::make_tuple(std::move(product), index, name);
    }
};
// Specialization for cases with int and other types (T)
// This specialization is used when creating ConcreteProductB
template<typename T>
class Factory<int, T> {
public:
    std::tuple<ProductVariant, int, T> creatProduct(int id, T other) const {
        static std::atomic<int> Bcounter{ 0 };
        INFO("Creating PRODUCT B: \n");
        Bcounter.fetch_add(1, std::memory_order_relaxed);
        ProductVariant product = ConcreteProductB(id);
        return std::make_tuple(std::move(product), id, other);
    }
};

