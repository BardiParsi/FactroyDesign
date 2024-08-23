#include "BaseProduct.h"
#include "ProductWithID.h"
#include "ConcreteProductA.h"
#include "ConcreteProductB.h"
#include "TempProduct.h"
#include "ProductTypes.h" 
#include "ThreadPool.h"
#include "Factory.h"
#include <vector>
#include <tuple>
#include <memory>
#include <string>
#include <atomic>
#include <iostream>
#include <variant>
#include <span>
#include <future>
#include <stop_token>

import LOGGER;

using std::cout;
using std::endl;
// Determine the number of threads based on the hardware capabilities
const unsigned int numThreads = std::thread::hardware_concurrency();
// Function to extract IDs from a span of ProductVariant
std::vector<int> extractID(std::span<const ProductVariant> products) {
    std::vector<int> vecID;
    for (const auto& p : products) {
        std::visit([&vecID](const auto& product) {
            using T = std::decay_t<decltype(product)>;
            if constexpr (std::is_base_of_v<ProductWithID, T>) {
                vecID.push_back(product.getID());
            }
        }, p); 
    }
    return vecID;
}
// Function to process all products using the provided thread pool
void processProducts(ThreadPool& pool, const std::vector<ProductVariant>& products) {
    std::vector<std::future<void>> futures;

    for (const auto& product : products) {
        futures.push_back(pool.enqueue([product]() {
            std::visit([](const auto& p) {
                p.process();
                }, product);
            }));
    }
    // Wait for all process tasks to complete
    for (auto& future : futures) {
        future.get(); // Ensure all tasks have finished
    }
}
// Function to extract IDs from products using the provided thread pool
void extractProductIDs(ThreadPool& pool, const std::vector<ProductVariant>& products, std::vector<int>& allIds) {
    const size_t numChunks = 2; // Adjust as needed -- Number of chunks to divide the product list into
    std::vector<std::future<std::vector<int>>> futures;
    size_t chunkSize = products.size() / numChunks;
    // Split products into chunks and submit tasks to extract IDs
    for (size_t i = 0; i < numChunks; ++i) {
        size_t start = i * chunkSize;
        size_t end = (i == numChunks - 1) ? products.size() : start + chunkSize;

        // Create a span for the current chunk of products
        std::span<const ProductVariant> productSpan(products.data() + start, end - start);

        // Submit the extraction task to the thread pool
        futures.push_back(pool.enqueue([productSpan]() {
            return extractID(productSpan);
            }));
    }
    // Collect results from all extraction tasks
    for (auto& future : futures) {
        std::vector<int> ids = future.get();
        allIds.insert(allIds.end(), ids.begin(), ids.end());
    }
}

int main() {
    ThreadPool poolProcess(numThreads); // Create a thread pool for processing products
    ThreadPool poolExtraction(numThreads); // Create a thread pool for extracting IDs
    // Prepare a list of products
    // Prepare a list of products using the factory
    Factory<int, std::string> factoryA;
    Factory<int, int> factoryB;
    Factory<> factoryTemp;

    std::vector<ProductVariant> products;

    // Create products using the factory
    auto [productA1, index1, name1] = factoryA.creatProduct(1, 0, "ProductA1");
    auto [productB1, id1, other1] = factoryB.creatProduct(2, 42);
    auto [tempProduct] = factoryTemp.creatProduct();

    // Add products to the vector
    products.push_back(std::move(productA1));
    products.push_back(std::move(productB1));
    products.push_back(std::move(tempProduct));

    // Add more products if needed
    auto [productA2, index2, name2] = factoryA.creatProduct(3, 1, "ProductA2");
    auto [productB2, id2, other2] = factoryB.creatProduct(4, 84);

    products.push_back(std::move(productA2));
    products.push_back(std::move(productB2));

    // Process products
    processProducts(poolProcess, products);

    // Extract IDs from all products
    std::vector<int> allIds;
    extractProductIDs(poolExtraction, products, allIds);

    // Print all extracted IDs
    INFO("ID Extracted: ");
    for (int id : allIds) {
        cout << id << endl; // Output each ID to the console
    }

    return 0;
}
