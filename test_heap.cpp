// Tests for MinHeap<T>  (round #8 — binary min-heap)
//
// Build & run:
//   g++ -std=c++20 -Wall -Wextra test_heap.cpp -o test_heap && ./test_heap
//
// Implement everything in heap.h. You should NOT need to edit this file.

#include <iostream>
#include <vector>

#include "heap.h"

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
    SECTION("empty heap");
    {
        MinHeap<int> h;
        CHECK(h.size() == 0);
        CHECK(h.empty());
    }

    SECTION("top is the minimum, updates as smaller items arrive");
    {
        MinHeap<int> h;
        h.push(50);
        CHECK(h.top() == 50);
        h.push(30);
        CHECK(h.top() == 30);
        h.push(70);
        CHECK(h.top() == 30);   // 70 is larger, min unchanged
        h.push(10);
        CHECK(h.top() == 10);   // new global min bubbles to the top
        CHECK(h.size() == 4);
    }

    SECTION("pop removes the minimum, next min surfaces");
    {
        MinHeap<int> h;
        for (int v : {5, 1, 4, 2, 3}) h.push(v);
        CHECK(h.top() == 1);
        h.pop();
        CHECK(h.top() == 2);
        h.pop();
        CHECK(h.top() == 3);
        CHECK(h.size() == 3);
    }

    SECTION("repeated pop yields ascending order (heapsort)");
    {
        MinHeap<int> h;
        int input[] = {9, 3, 7, 1, 8, 2, 6, 0, 5, 4};
        for (int v : input) h.push(v);
        CHECK(h.size() == 10);

        int prev = -1;
        bool ascending = true;
        std::size_t count = 0;
        while (!h.empty()) {
            int cur = h.top();
            if (cur < prev) ascending = false;
            prev = cur;
            h.pop();
            ++count;
        }
        CHECK(ascending);
        CHECK(count == 10);
        CHECK(h.empty());
    }

    SECTION("handles duplicate values");
    {
        MinHeap<int> h;
        for (int v : {4, 4, 1, 1, 4, 1}) h.push(v);
        CHECK(h.top() == 1);
        int prev = -1;
        bool ascending = true;
        while (!h.empty()) {
            int cur = h.top();
            if (cur < prev) ascending = false;
            prev = cur;
            h.pop();
        }
        CHECK(ascending);
    }

    SECTION("interleaved push and pop keep the heap valid");
    {
        MinHeap<int> h;
        h.push(10);
        h.push(4);
        CHECK(h.top() == 4);
        h.pop();             // removes 4
        CHECK(h.top() == 10);
        h.push(7);
        h.push(2);
        CHECK(h.top() == 2);
        h.pop();             // removes 2
        CHECK(h.top() == 7);
    }

    std::cout << "\n" << (g_checks - g_failures) << "/" << g_checks
              << " checks passed.\n";
    if (g_failures == 0) { std::cout << "ALL GREEN \xE2\x9C\x93\n"; return 0; }
    std::cout << g_failures << " FAILED.\n";
    return 1;
}
