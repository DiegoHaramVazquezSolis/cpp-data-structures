# #9 — Graph (adjacency list)

## What it is, in words
A graph is the most general structure here: a set of **vertices** (nodes) connected by
**edges** (links). Unlike a tree, there's no root and no hierarchy — any vertex can connect
to any other, cycles are allowed, and a vertex can have any number of neighbors. Graphs
model roads, social networks, dependencies, the web — anything that's "things and the
connections between them."

The central design choice is **how to store the edges**:
- **Adjacency matrix:** an n×n grid of booleans; `M[u][v] = true` means an edge exists.
  O(1) edge lookup, but O(n²) memory even when there are few edges.
- **Adjacency list:** for each vertex, keep a list of the vertices it connects to. Memory
  is O(vertices + edges) — far better for **sparse** graphs (most real graphs) — at the
  cost of O(degree) edge lookups. This is the version you'll build.

For this exercise the graph is **undirected** (an edge `u–v` connects both ways) and
vertices are integers `0 .. n-1`.

The two foundational traversals — which every graph algorithm builds on:
- **Breadth-First Search (BFS):** explore in expanding rings from a start vertex using a
  **queue**. Because it visits vertices in order of hop-distance, BFS finds the
  **shortest path** (fewest edges) in an unweighted graph.
- **Depth-First Search (DFS):** plunge as deep as possible along one path before
  backtracking, using a **stack** (or recursion). Good for connectivity, cycle detection,
  and topological ordering.

You've already built the queue and stack that power these — this is where they pay off.

## Cost summary
- `add_edge` / `has_edge`: O(1) to O(degree) depending on storage
- BFS / DFS: **O(V + E)** (visit every vertex and every edge once)
- `shortest_path` (unweighted, via BFS): **O(V + E)**

## Contract — `graph.h`
```cpp
class Graph {
public:
    explicit Graph(int n);                      // n vertices, labeled 0 .. n-1, no edges

    void add_edge(int u, int v);                // undirected: connects u<->v
    bool has_edge(int u, int v) const;

    std::vector<int> neighbors(int u) const;    // vertices adjacent to u (any order)
    int  num_vertices() const;

    int  shortest_path(int u, int v) const;     // fewest edges from u to v via BFS;
                                                // 0 if u == v; -1 if v is unreachable
};
```

Notes the tests assume:
- The graph is **undirected**: after `add_edge(u, v)`, both `has_edge(u, v)` and
  `has_edge(v, u)` are true, and `v` appears in `neighbors(u)` and vice versa.
- `neighbors(u)` may return the vertices in **any order** (the tests sort before comparing).
- `shortest_path(u, v)` returns the number of **edges** on the shortest route: `0` when
  `u == v`, the hop count when reachable, and `-1` when there is no path.
- This is a non-templated class (vertices are plain `int`s). Include `<vector>`.
- You may reuse your own `Queue` for the BFS, or use `std::queue` — your choice.
