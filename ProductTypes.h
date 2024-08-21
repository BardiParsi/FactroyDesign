#pragma once

#include <variant>
#include "ConcreteProductA.h"
#include "ConcreteProductB.h"
#include "TempProduct.h"

// Define a variant type that can hold any of the concrete product types
// This allows for a single type to represent multiple different product types

using ProductVariant = std::variant<ConcreteProductA, ConcreteProductB, TempProduct>;