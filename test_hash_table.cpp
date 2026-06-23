// Tests for HashMap<K, V>  (round #6 — hash table, separate chaining)
//
// Build & run:
//   g++ -std=c++20 -Wall -Wextra test_hash_table.cpp -o test_hm && ./test_hm
//
// Implement everything in hash_table.h. You should NOT need to edit this file.

#include <iostream>
#include <stdexcept>
#include <string>

#include "hash_table.h"

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
    SECTION("empty map");
    {
        HashMap<int, int> m;
        CHECK(m.size() == 0);
        CHECK(m.empty());
        CHECK(!m.contains(123));
    }

    SECTION("insert and look up");
    {
        HashMap<int, int> m;
        m.insert(1, 100);
        m.insert(2, 200);
        m.insert(3, 300);
        CHECK(m.size() == 3);
        CHECK(m.contains(2));
        CHECK(m.at(1) == 100);
        CHECK(m.at(2) == 200);
        CHECK(m.at(3) == 300);
    }

    SECTION("insert on existing key overwrites, size unchanged");
    {
        HashMap<int, int> m;
        m.insert(5, 1);
        m.insert(5, 2);
        m.insert(5, 999);
        CHECK(m.size() == 1);
        CHECK(m.at(5) == 999);
    }

    SECTION("at() throws on missing key (const and non-const)");
    {
        HashMap<int, int> m;
        m.insert(1, 10);

        bool threw = false;
        try { (void)m.at(42); } catch (const std::out_of_range&) { threw = true; }
        CHECK(threw);

        const HashMap<int, int>& cm = m;
        CHECK(cm.at(1) == 10);
        bool threw_const = false;
        try { (void)cm.at(42); } catch (const std::out_of_range&) { threw_const = true; }
        CHECK(threw_const);
    }

    SECTION("at() returns a writable reference");
    {
        HashMap<int, int> m;
        m.insert(1, 10);
        m.at(1) = 55;
        CHECK(m.at(1) == 55);
    }

    SECTION("operator[] inserts default then is assignable");
    {
        HashMap<int, int> m;
        CHECK(m[7] == 0);          // missing key -> value-initialized int(0), inserted
        CHECK(m.contains(7));
        CHECK(m.size() == 1);
        m[7] = 70;                 // now assign through it
        CHECK(m.at(7) == 70);
        CHECK(m.size() == 1);      // assigning an existing key doesn't grow

        m[8] += 5;                 // default 0, then += 5
        CHECK(m.at(8) == 5);
        CHECK(m.size() == 2);
    }

    SECTION("erase");
    {
        HashMap<int, int> m;
        m.insert(1, 1);
        m.insert(2, 2);
        CHECK(m.erase(1));          // present -> true
        CHECK(!m.contains(1));
        CHECK(m.size() == 1);
        CHECK(!m.erase(1));         // already gone -> false
        CHECK(!m.erase(999));       // never existed -> false
        CHECK(m.at(2) == 2);        // untouched key survives
    }

    SECTION("many keys force chaining / rehash, all survive");
    {
        HashMap<int, int> m;
        const int N = 1000;
        for (int i = 0; i < N; ++i) m.insert(i, i * 7);
        CHECK(m.size() == static_cast<std::size_t>(N));
        bool all_ok = true;
        for (int i = 0; i < N; ++i) if (m.at(i) != i * 7) all_ok = false;
        CHECK(all_ok);
        CHECK(m.contains(0));
        CHECK(m.contains(N - 1));
        CHECK(!m.contains(N));      // one past the end was never inserted
    }

    SECTION("string keys");
    {
        HashMap<std::string, int> m;
        m.insert("alpha", 1);
        m.insert("beta", 2);
        m.insert("alpha", 11);      // overwrite
        CHECK(m.size() == 2);
        CHECK(m.at("alpha") == 11);
        CHECK(m.at("beta") == 2);
        CHECK(m.contains("beta"));
        CHECK(!m.contains("gamma"));
        CHECK(m.erase("beta"));
        CHECK(!m.contains("beta"));
    }

    std::cout << "\n" << (g_checks - g_failures) << "/" << g_checks
              << " checks passed.\n";
    if (g_failures == 0) { std::cout << "ALL GREEN \xE2\x9C\x93\n"; return 0; }
    std::cout << g_failures << " FAILED.\n";
    return 1;
}
