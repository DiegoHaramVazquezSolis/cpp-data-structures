// Tests for Stack<T>  (round #3 — LIFO)
//
// Build & run:
//   g++ -std=c++20 -Wall -Wextra test_stack.cpp -o test_stack && ./test_stack
//
// Implement everything in stack.h. You should NOT need to edit this file.

#include <iostream>
#include <string>

#include "stack.h"

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
    SECTION("empty stack");
    {
        Stack<int> s;
        CHECK(s.size() == 0);
        CHECK(s.empty());
    }

    SECTION("push then top sees most recent");
    {
        Stack<int> s;
        s.push(10);
        CHECK(s.top() == 10);
        s.push(20);
        CHECK(s.top() == 20);
        CHECK(s.size() == 2);
        CHECK(!s.empty());
    }

    SECTION("LIFO order on pop");
    {
        Stack<int> s;
        for (int i = 1; i <= 5; ++i) s.push(i);   // pushed 1..5
        for (int i = 5; i >= 1; --i) {            // must come back 5..1
            CHECK(s.top() == i);
            s.pop();
        }
        CHECK(s.empty());
    }

    SECTION("top() is a writable reference");
    {
        Stack<int> s;
        s.push(1);
        s.top() = 42;
        CHECK(s.top() == 42);
    }

    SECTION("size tracks pushes and pops");
    {
        Stack<int> s;
        s.push(1); s.push(2); s.push(3);
        CHECK(s.size() == 3);
        s.pop();
        CHECK(s.size() == 2);
        s.pop(); s.pop();
        CHECK(s.size() == 0);
    }

    SECTION("clear then reuse");
    {
        Stack<int> s;
        for (int i = 0; i < 4; ++i) s.push(i);
        s.clear();
        CHECK(s.empty());
        s.push(99);
        CHECK(s.size() == 1);
        CHECK(s.top() == 99);
    }

    SECTION("works with std::string");
    {
        Stack<std::string> s;
        s.push("a");
        s.push("b");
        CHECK(s.top() == "b");
        s.pop();
        CHECK(s.top() == "a");
    }

    std::cout << "\n" << (g_checks - g_failures) << "/" << g_checks
              << " checks passed.\n";
    if (g_failures == 0) { std::cout << "ALL GREEN \xE2\x9C\x93\n"; return 0; }
    std::cout << g_failures << " FAILED.\n";
    return 1;
}
