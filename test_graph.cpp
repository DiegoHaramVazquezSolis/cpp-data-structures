// Tests for Graph  (round #9 — undirected, adjacency list)
//
// Build & run:
//   g++ -std=c++20 -Wall -Wextra test_graph.cpp -o test_graph && ./test_graph
//
// Implement everything in graph.h. You should NOT need to edit this file.

#include <algorithm>
#include <iostream>
#include <vector>

#include "graph.h"

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

// neighbors() may return any order; compare as a sorted set.
static std::vector<int> sorted(std::vector<int> v) {
    std::sort(v.begin(), v.end());
    return v;
}

int main() {
    SECTION("construction");
    {
        Graph g(5);
        CHECK(g.num_vertices() == 5);
        CHECK(g.neighbors(0).empty());      // no edges yet
        CHECK(!g.has_edge(0, 1));
    }

    SECTION("add_edge is undirected");
    {
        Graph g(4);
        g.add_edge(0, 1);
        g.add_edge(0, 2);
        CHECK(g.has_edge(0, 1));
        CHECK(g.has_edge(1, 0));            // symmetric
        CHECK(g.has_edge(0, 2));
        CHECK(g.has_edge(2, 0));
        CHECK(!g.has_edge(1, 2));
        CHECK(sorted(g.neighbors(0)) == (std::vector<int>{1, 2}));
        CHECK(sorted(g.neighbors(1)) == (std::vector<int>{0}));
        CHECK(g.neighbors(3).empty());
    }

    SECTION("shortest_path: self distance is 0");
    {
        Graph g(3);
        CHECK(g.shortest_path(2, 2) == 0);
    }

    SECTION("shortest_path: direct and multi-hop");
    {
        // path graph: 0 - 1 - 2 - 3 - 4
        Graph g(5);
        g.add_edge(0, 1);
        g.add_edge(1, 2);
        g.add_edge(2, 3);
        g.add_edge(3, 4);
        CHECK(g.shortest_path(0, 1) == 1);
        CHECK(g.shortest_path(0, 2) == 2);
        CHECK(g.shortest_path(0, 4) == 4);
        CHECK(g.shortest_path(4, 0) == 4);  // undirected: symmetric distance
    }

    SECTION("shortest_path: BFS picks the fewest-edges route");
    {
        // square with a chord:
        // 0-1, 1-2, 2-3, 3-0, and a long branch 0-4-5-2
        Graph g(6);
        g.add_edge(0, 1);
        g.add_edge(1, 2);
        g.add_edge(2, 3);
        g.add_edge(3, 0);
        g.add_edge(0, 4);
        g.add_edge(4, 5);
        g.add_edge(5, 2);
        CHECK(g.shortest_path(0, 2) == 2);  // 0-1-2 (2 hops), not 0-4-5-2 (3 hops)
    }

    SECTION("shortest_path: unreachable is -1");
    {
        // two disconnected components: {0,1} and {2,3}
        Graph g(4);
        g.add_edge(0, 1);
        g.add_edge(2, 3);
        CHECK(g.shortest_path(0, 1) == 1);
        CHECK(g.shortest_path(0, 2) == -1);
        CHECK(g.shortest_path(0, 3) == -1);
        CHECK(g.shortest_path(2, 3) == 1);
    }

    SECTION("larger graph reachability");
    {
        Graph g(7);
        g.add_edge(0, 1);
        g.add_edge(0, 2);
        g.add_edge(1, 3);
        g.add_edge(2, 3);
        g.add_edge(3, 4);
        g.add_edge(4, 5);
        // vertex 6 is isolated
        CHECK(g.shortest_path(0, 5) == 4);  // 0-1-3-4-5 or 0-2-3-4-5
        CHECK(g.shortest_path(0, 6) == -1);
        CHECK(g.shortest_path(6, 6) == 0);
    }

    std::cout << "\n" << (g_checks - g_failures) << "/" << g_checks
              << " checks passed.\n";
    if (g_failures == 0) { std::cout << "ALL GREEN \xE2\x9C\x93\n"; return 0; }
    std::cout << g_failures << " FAILED.\n";
    return 1;
}
