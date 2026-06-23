// Tests for DoublyLinkedList<T>  (round #5)
//
// Build & run:
//   g++ -std=c++20 -Wall -Wextra test_doubly_linked_list.cpp -o test_dll && ./test_dll
//
// Implement everything in doubly_linked_list.h. You should NOT need to edit this file.

#include <iostream>
#include <stdexcept>
#include <string>

#include "doubly_linked_list.h"

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

int main() {
    SECTION("empty list");
    {
        DoublyLinkedList<int> l;
        CHECK(l.size() == 0);
        CHECK(l.empty());
    }

    SECTION("push_back / push_front build correct order");
    {
        DoublyLinkedList<int> l;
        l.push_back(1);    // [1]
        l.push_front(0);   // [0,1]
        l.push_back(2);    // [0,1,2]
        l.push_front(-1);  // [-1,0,1,2]
        CHECK(l.size() == 4);
        CHECK(l.at(0) == -1);
        CHECK(l.at(1) == 0);
        CHECK(l.at(2) == 1);
        CHECK(l.at(3) == 2);
        CHECK(l.front() == -1);
        CHECK(l.back() == 2);
    }

    SECTION("pop_back is O(1) and updates tail");
    {
        DoublyLinkedList<int> l;
        for (int i = 0; i < 4; ++i) l.push_back(i);  // 0 1 2 3
        l.pop_back();                                // 0 1 2
        CHECK(l.size() == 3);
        CHECK(l.back() == 2);
        l.pop_back();                                // 0 1
        CHECK(l.back() == 1);
        CHECK(l.front() == 0);
    }

    SECTION("pop_front updates head");
    {
        DoublyLinkedList<int> l;
        for (int i = 0; i < 4; ++i) l.push_back(i);  // 0 1 2 3
        l.pop_front();                               // 1 2 3
        CHECK(l.size() == 3);
        CHECK(l.front() == 1);
        CHECK(l.back() == 3);
    }

    SECTION("drain from both ends then reuse");
    {
        DoublyLinkedList<int> l;
        l.push_back(1);
        l.push_back(2);
        l.pop_back();      // [1]
        l.pop_front();     // []  -- last node removed
        CHECK(l.empty());
        l.push_front(5);   // both head_ and tail_ must have reset to null
        CHECK(l.size() == 1);
        CHECK(l.front() == 5);
        CHECK(l.back() == 5);
    }

    SECTION("single element: front == back, remove from either end");
    {
        DoublyLinkedList<int> l;
        l.push_back(7);
        CHECK(l.front() == 7);
        CHECK(l.back() == 7);
        l.pop_back();
        CHECK(l.empty());

        l.push_front(8);
        l.pop_front();
        CHECK(l.empty());
    }

    SECTION("at() bounds checking (const and non-const)");
    {
        DoublyLinkedList<int> l;
        l.push_back(100);
        l.push_back(200);
        CHECK(l.at(1) == 200);

        bool threw = false;
        try { (void)l.at(2); } catch (const std::out_of_range&) { threw = true; }
        CHECK(threw);

        const DoublyLinkedList<int>& cl = l;
        CHECK(cl.at(0) == 100);
        bool threw_const = false;
        try { (void)cl.at(9); } catch (const std::out_of_range&) { threw_const = true; }
        CHECK(threw_const);
    }

    SECTION("clear then reuse");
    {
        DoublyLinkedList<int> l;
        for (int i = 0; i < 6; ++i) l.push_back(i);
        l.clear();
        CHECK(l.empty());
        l.push_back(1);
        l.push_front(0);
        CHECK(l.size() == 2);
        CHECK(l.front() == 0);
        CHECK(l.back() == 1);
    }

    SECTION("works with std::string");
    {
        DoublyLinkedList<std::string> l;
        l.push_back("b");
        l.push_front("a");
        l.push_back("c");   // a b c
        CHECK(l.front() == "a");
        CHECK(l.back() == "c");
        CHECK(l.at(1) == "b");
    }

    std::cout << "\n" << (g_checks - g_failures) << "/" << g_checks
              << " checks passed.\n";
    if (g_failures == 0) { std::cout << "ALL GREEN \xE2\x9C\x93\n"; return 0; }
    std::cout << g_failures << " FAILED.\n";
    return 1;
}
