// Tests for BST<T>  (round #7 — binary search tree)
//
// Build & run:
//   g++ -std=c++20 -Wall -Wextra test_bst.cpp -o test_bst && ./test_bst
//
// Implement everything in bst.h. You should NOT need to edit this file.

#include <iostream>
#include <vector>

#include "bst.h"

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

static bool is_sorted_vec(const std::vector<int>& v) {
    for (std::size_t i = 1; i < v.size(); ++i)
        if (v[i - 1] >= v[i]) return false;   // strictly increasing (no duplicates)
    return true;
}

int main() {
    SECTION("empty tree");
    {
        BST<int> t;
        CHECK(t.size() == 0);
        CHECK(t.empty());
        CHECK(!t.contains(5));
        CHECK(t.in_order().empty());
    }

    SECTION("insert + in_order is sorted");
    {
        BST<int> t;
        int vals[] = {50, 30, 70, 20, 40, 60, 80, 10};
        for (int v : vals) t.insert(v);
        CHECK(t.size() == 8);
        std::vector<int> order = t.in_order();
        CHECK(order.size() == 8);
        CHECK(is_sorted_vec(order));
        CHECK(order.front() == 10);
        CHECK(order.back() == 80);
    }

    SECTION("contains true and false");
    {
        BST<int> t;
        for (int v : {5, 3, 8, 1, 4}) t.insert(v);
        CHECK(t.contains(5));
        CHECK(t.contains(1));
        CHECK(t.contains(4));
        CHECK(!t.contains(2));
        CHECK(!t.contains(100));
    }

    SECTION("duplicates are ignored");
    {
        BST<int> t;
        t.insert(10);
        t.insert(10);
        t.insert(10);
        CHECK(t.size() == 1);
        CHECK(t.in_order().size() == 1);
    }

    SECTION("min and max");
    {
        BST<int> t;
        for (int v : {50, 30, 70, 20, 40, 60, 80, 10}) t.insert(v);
        CHECK(t.min() == 10);
        CHECK(t.max() == 80);
    }

    SECTION("erase a leaf");
    {
        BST<int> t;
        for (int v : {50, 30, 70, 20, 40}) t.insert(v);
        CHECK(t.erase(20));            // 20 is a leaf
        CHECK(!t.contains(20));
        CHECK(t.size() == 4);
        CHECK(is_sorted_vec(t.in_order()));
    }

    SECTION("erase a node with one child");
    {
        BST<int> t;
        for (int v : {50, 30, 70, 60}) t.insert(v);  // 70 has only a left child (60)
        CHECK(t.erase(70));
        CHECK(!t.contains(70));
        CHECK(t.contains(60));        // child must be reconnected
        CHECK(t.size() == 3);
        CHECK(is_sorted_vec(t.in_order()));
    }

    SECTION("erase a node with two children");
    {
        BST<int> t;
        for (int v : {50, 30, 70, 20, 40, 60, 80}) t.insert(v);
        CHECK(t.erase(30));           // 30 has two children (20 and 40)
        CHECK(!t.contains(30));
        CHECK(t.contains(20));
        CHECK(t.contains(40));
        CHECK(t.size() == 6);
        std::vector<int> order = t.in_order();
        CHECK(is_sorted_vec(order));  // invariant must still hold
    }

    SECTION("erase the root repeatedly");
    {
        BST<int> t;
        for (int v : {50, 30, 70, 20, 40, 60, 80}) t.insert(v);
        CHECK(t.erase(50));           // remove root (two children)
        CHECK(!t.contains(50));
        CHECK(is_sorted_vec(t.in_order()));
        CHECK(t.size() == 6);
    }

    SECTION("erase returns false for missing value");
    {
        BST<int> t;
        for (int v : {5, 3, 8}) t.insert(v);
        CHECK(!t.erase(99));
        CHECK(t.size() == 3);
    }

    SECTION("drain the whole tree");
    {
        BST<int> t;
        int vals[] = {50, 30, 70, 20, 40, 60, 80, 10};
        for (int v : vals) t.insert(v);
        for (int v : vals) CHECK(t.erase(v));
        CHECK(t.empty());
        CHECK(t.in_order().empty());
    }

    std::cout << "\n" << (g_checks - g_failures) << "/" << g_checks
              << " checks passed.\n";
    if (g_failures == 0) { std::cout << "ALL GREEN \xE2\x9C\x93\n"; return 0; }
    std::cout << g_failures << " FAILED.\n";
    return 1;
}
