// Tests for DynamicArray<T>  (round #1)
//
// Build & run:
//   g++ -std=c++20 -Wall -Wextra test_dynamic_array.cpp -o test_da && ./test_da
//
// You should NOT need to edit this file. Implement everything in dynamic_array.h.

#include <iostream>
#include <stdexcept>
#include <string>

#include "dynamic_array.h"

// ----- tiny test harness -------------------------------------------------
static int g_checks = 0;
static int g_failures = 0;

#define CHECK(cond)                                                        \
    do {                                                                   \
        ++g_checks;                                                        \
        if (!(cond)) {                                                     \
            ++g_failures;                                                  \
            std::cout << "  [FAIL] line " << __LINE__ << ": " #cond "\n";  \
        }                                                                  \
    } while (0)

#define SECTION(name) std::cout << "== " name " ==\n"
// -------------------------------------------------------------------------

int main() {
    SECTION("empty array");
    {
        DynamicArray<int> a;
        CHECK(a.size() == 0);
        CHECK(a.empty());
    }

    SECTION("push_back grows size and stores values");
    {
        DynamicArray<int> a;
        for (int i = 0; i < 10; ++i) a.push_back(i * 10);
        CHECK(a.size() == 10);
        CHECK(!a.empty());
        for (int i = 0; i < 10; ++i) CHECK(a[i] == i * 10);
        CHECK(a.front() == 0);
        CHECK(a.back() == 90);
    }

    SECTION("capacity is enough and grows");
    {
        DynamicArray<int> a;
        std::size_t cap_before = a.capacity();
        for (int i = 0; i < 1000; ++i) a.push_back(i);
        CHECK(a.size() == 1000);
        CHECK(a.capacity() >= a.size());   // must hold everything
        CHECK(a.capacity() > cap_before);  // must have grown
    }

    SECTION("operator[] writes through");
    {
        DynamicArray<int> a;
        a.push_back(1);
        a.push_back(2);
        a[0] = 42;
        CHECK(a[0] == 42);
        CHECK(a[1] == 2);
    }

    SECTION("pop_back shrinks size, keeps remaining");
    {
        DynamicArray<int> a;
        for (int i = 0; i < 5; ++i) a.push_back(i);
        a.pop_back();
        a.pop_back();
        CHECK(a.size() == 3);
        CHECK(a.back() == 2);
    }

    SECTION("at() bounds checking");
    {
        DynamicArray<int> a;
        a.push_back(7);
        CHECK(a.at(0) == 7);

        bool threw = false;
        try {
            (void)a.at(1);          // out of range
        } catch (const std::out_of_range&) {
            threw = true;
        }
        CHECK(threw);

        // same bounds rule must hold through a const reference
        const DynamicArray<int>& ca = a;
        CHECK(ca.at(0) == 7);
        bool threw_const = false;
        try {
            (void)ca.at(1);         // i == size(), must throw
        } catch (const std::out_of_range&) {
            threw_const = true;
        }
        CHECK(threw_const);
    }

    SECTION("clear empties the array");
    {
        DynamicArray<int> a;
        for (int i = 0; i < 4; ++i) a.push_back(i);
        a.clear();
        CHECK(a.size() == 0);
        CHECK(a.empty());
        a.push_back(99);            // must still be usable after clear
        CHECK(a.size() == 1);
        CHECK(a[0] == 99);
    }

    SECTION("works with a non-trivial type (std::string)");
    {
        DynamicArray<std::string> a;
        a.push_back("hello");
        a.push_back("world");
        CHECK(a.size() == 2);
        CHECK(a[0] == "hello");
        CHECK(a.back() == "world");
    }

    // ----- summary -------------------------------------------------------
    std::cout << "\n" << (g_checks - g_failures) << "/" << g_checks
              << " checks passed.\n";
    if (g_failures == 0) {
        std::cout << "ALL GREEN \xE2\x9C\x93\n";
        return 0;
    }
    std::cout << g_failures << " FAILED.\n";
    return 1;
}
