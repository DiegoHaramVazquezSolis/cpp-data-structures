// Tests for Queue<T>  (round #4 — FIFO)
//
// Build & run:
//   g++ -std=c++20 -Wall -Wextra test_queue.cpp -o test_queue && ./test_queue
//
// Implement everything in queue.h. You should NOT need to edit this file.

#include <iostream>
#include <string>

#include "queue.h"

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
    SECTION("empty queue");
    {
        Queue<int> q;
        CHECK(q.size() == 0);
        CHECK(q.empty());
    }

    SECTION("front/back after pushes");
    {
        Queue<int> q;
        q.push(10);
        CHECK(q.front() == 10);
        CHECK(q.back() == 10);   // single element: front == back
        q.push(20);
        q.push(30);
        CHECK(q.front() == 10);  // oldest
        CHECK(q.back() == 30);   // newest
        CHECK(q.size() == 3);
    }

    SECTION("FIFO order on pop");
    {
        Queue<int> q;
        for (int i = 1; i <= 5; ++i) q.push(i);  // 1 2 3 4 5
        for (int i = 1; i <= 5; ++i) {           // must come back 1..5
            CHECK(q.front() == i);
            q.pop();
        }
        CHECK(q.empty());
    }

    SECTION("front() is a writable reference");
    {
        Queue<int> q;
        q.push(1);
        q.push(2);
        q.front() = 99;
        CHECK(q.front() == 99);
    }

    SECTION("interleaved push and pop");
    {
        Queue<int> q;
        q.push(1);
        q.push(2);
        q.pop();          // remove 1 -> front now 2
        q.push(3);        // 2 3
        CHECK(q.front() == 2);
        CHECK(q.back() == 3);
        CHECK(q.size() == 2);
    }

    SECTION("drain to empty then reuse");
    {
        Queue<int> q;
        q.push(1);
        q.push(2);
        q.pop();
        q.pop();          // empty
        CHECK(q.empty());
        q.push(7);        // pointers must have reset
        CHECK(q.size() == 1);
        CHECK(q.front() == 7);
        CHECK(q.back() == 7);
    }

    SECTION("clear then reuse");
    {
        Queue<int> q;
        for (int i = 0; i < 4; ++i) q.push(i);
        q.clear();
        CHECK(q.empty());
        q.push(5);
        q.push(6);
        CHECK(q.front() == 5);
        CHECK(q.back() == 6);
    }

    SECTION("works with std::string");
    {
        Queue<std::string> q;
        q.push("first");
        q.push("second");
        CHECK(q.front() == "first");
        CHECK(q.back() == "second");
        q.pop();
        CHECK(q.front() == "second");
    }

    std::cout << "\n" << (g_checks - g_failures) << "/" << g_checks
              << " checks passed.\n";
    if (g_failures == 0) { std::cout << "ALL GREEN \xE2\x9C\x93\n"; return 0; }
    std::cout << g_failures << " FAILED.\n";
    return 1;
}
