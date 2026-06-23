// Tests for LinkedList<T>  (round #2 — singly linked list)
//
// Build & run:
//   g++ -std=c++20 -Wall -Wextra test_linked_list.cpp -o test_ll && ./test_ll
//
// Implement everything in linked_list.h. You should NOT need to edit this file.

#include <iostream>
#include <stdexcept>
#include <string>

#include "linked_list.h"

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
    SECTION("empty list");
    {
        LinkedList<int> l;
        CHECK(l.size() == 0);
        CHECK(l.empty());
    }

    SECTION("push_back appends in order");
    {
        LinkedList<int> l;
        for (int i = 0; i < 5; ++i) l.push_back(i);   // 0 1 2 3 4
        CHECK(l.size() == 5);
        CHECK(!l.empty());
        CHECK(l.front() == 0);
        CHECK(l.back() == 4);
        for (std::size_t i = 0; i < 5; ++i) CHECK(l.at(i) == static_cast<int>(i));
    }

    SECTION("push_front prepends (reverses insertion order)");
    {
        LinkedList<int> l;
        for (int i = 0; i < 5; ++i) l.push_front(i);  // 4 3 2 1 0
        CHECK(l.size() == 5);
        CHECK(l.front() == 4);
        CHECK(l.back() == 0);
        CHECK(l.at(0) == 4);
        CHECK(l.at(4) == 0);
    }

    SECTION("mixing push_front and push_back");
    {
        LinkedList<int> l;
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

    SECTION("pop_front");
    {
        LinkedList<int> l;
        for (int i = 0; i < 3; ++i) l.push_back(i);   // 0 1 2
        l.pop_front();                                // 1 2
        CHECK(l.size() == 2);
        CHECK(l.front() == 1);
        CHECK(l.back() == 2);
    }

    SECTION("pop_back");
    {
        LinkedList<int> l;
        for (int i = 0; i < 3; ++i) l.push_back(i);   // 0 1 2
        l.pop_back();                                 // 0 1
        CHECK(l.size() == 2);
        CHECK(l.front() == 0);
        CHECK(l.back() == 1);                         // tail must be updated
    }

    SECTION("drain to empty then reuse (head/tail reset correctly)");
    {
        LinkedList<int> l;
        l.push_back(10);
        l.push_back(20);
        l.pop_front();          // [20]
        l.pop_front();          // []  -- last node removed
        CHECK(l.size() == 0);
        CHECK(l.empty());

        // After draining, tail_ must have been reset to null so push works again.
        l.push_back(99);        // [99]
        CHECK(l.size() == 1);
        CHECK(l.front() == 99);
        CHECK(l.back() == 99);  // head == tail on a single-element list
    }

    SECTION("single element: front == back");
    {
        LinkedList<int> l;
        l.push_front(7);
        CHECK(l.size() == 1);
        CHECK(l.front() == 7);
        CHECK(l.back() == 7);
        l.pop_back();
        CHECK(l.empty());
    }

    SECTION("at() bounds checking (both const and non-const)");
    {
        LinkedList<int> l;
        l.push_back(100);
        l.push_back(200);
        CHECK(l.at(1) == 200);

        bool threw = false;
        try { (void)l.at(2); } catch (const std::out_of_range&) { threw = true; }
        CHECK(threw);

        const LinkedList<int>& cl = l;
        CHECK(cl.at(0) == 100);
        bool threw_const = false;
        try { (void)cl.at(5); } catch (const std::out_of_range&) { threw_const = true; }
        CHECK(threw_const);
    }

    SECTION("clear empties and stays usable");
    {
        LinkedList<int> l;
        for (int i = 0; i < 6; ++i) l.push_back(i);
        l.clear();
        CHECK(l.size() == 0);
        CHECK(l.empty());
        l.push_back(1);
        l.push_back(2);
        CHECK(l.size() == 2);
        CHECK(l.front() == 1);
        CHECK(l.back() == 2);
    }

    SECTION("works with std::string");
    {
        LinkedList<std::string> l;
        l.push_back("b");
        l.push_front("a");
        l.push_back("c");           // a b c
        CHECK(l.size() == 3);
        CHECK(l.front() == "a");
        CHECK(l.back() == "c");
        CHECK(l.at(1) == "b");
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
