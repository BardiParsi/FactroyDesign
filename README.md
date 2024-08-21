# Factory Design Pattern with Advanced C++20 Features
## Overview
This project is a demonstration of the Factory Software Pattern implemented using modern C++ features. It showcases the use of C++17 and C++20 functionalities to create a dynamic and generic product factory system. The project is specifically designed for C++20, using the Microsoft Visual Studio compiler.

## Features
C++20 Modules: Utilizes modular programming with the LOGGER.ixx and LOGGER.cpp files to manage logging functionality.
C++17 Variadic Templates: Implements factory classes using variadic templates and specialization to handle different product types and parameters.
Advanced Metaprogramming: Demonstrates advanced metaprogramming techniques to make product creation dynamic and generic.
# Structure
## Core Components
1. 'ProductWithID.h': Base class for products that have an ID.
2. 'ConcreteProductA.h': Derived class implementing a concrete product A with ID handling.
3. 'ConcreteProductB.h': Derived class implementing a concrete product B with ID handling.
4. 'TempProduct.h': A placeholder product used in the factory.
5. 'ProductTypes.h': Defines ProductVariant using std::variant to handle different product types.
6. 'Factory.h': Template and specialization for the Factory class that creates products based on input parameters.
7. 'ThreadPool.h': Implements a thread pool to manage concurrent task execution using modern C++ concurrency features.
8. 'LOGGER.ixx': Module interface for logging utility.
9. 'LOGGER.cpp': Implementation of logging functionality.
## Key Files
1. 'main.cpp': The entry point of the application demonstrating how to use the factory to create products, process them using a thread pool, and extract product IDs.
2. 'ThreadPool.cpp': Implements the thread pool functionality to manage and execute tasks concurrently.
# Getting Started
## Prerequisites
Compiler: Microsoft Visual Studio with support for C++20.
C++ Standard: C++20 with C++17 features.
## Building the Project
Open Visual Studio: Create a new C++ project.
Add Source Files: Include all .cpp and .h files in your project.
Set Compiler Flags: Ensure that the project is configured to use C++20 standards.
## Running the Application
Build the Project: Use the build command in Visual Studio.
Execute: Run the compiled binary to see the factory in action.
## Usage
The project demonstrates how to use the Factory class to create instances of different product types and process them concurrently using the ThreadPool class. The LOGGER module is used to print messages and trace execution.

## Example
In main.cpp, the following operations are performed:

Create Products: Use the Factory class to create various products.
Process Products: Use the ThreadPool to process the products concurrently.
Extract IDs: Collect and print IDs from the processed products.
cpp
Copy code
// Example snippet from main.cpp
std::vector<ProductVariant> products;
products.push_back(ConcreteProductA(1));
products.push_back(ConcreteProductB(2));
// ... more products

// Process products
processProducts(poolProcess, products);

// Extract and print IDs
std::vector<int> allIds;
extractProductIDs(poolExtraction, products, allIds);
Contributing
Contributions are welcome. Please open an issue or submit a pull request for any enhancements or bug fixes.

# License
This project is licensed under the GNU General Public License (GPL).

# Contact
Author: Masoud Farsi (Bardi)
For further information, please reach out to the project maintainer at farsi.masoud@gmail.com.
