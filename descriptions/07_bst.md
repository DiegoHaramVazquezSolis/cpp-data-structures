# #7 — Binary Search Tree

## What it is, in words
A binary search tree (BST) keeps elements in **sorted shape** using a tree of nodes. Each
node has a value and up to two children: a **left** child and a **right** child. The
defining invariant — the **BST property** — is that for every node:

- everything in its **left** subtree is **less** than the node's value, and
- everything in its **right** subtree is **greater**.

This invariant is what makes search fast. To look for a value you start at the **root** and
at each step compare: if the target is smaller, go left; if larger, go right; if equal,
you found it. Each comparison throws away half the remaining tree — that's the same
divide-and-conquer as binary search, hence the name. Insertion follows the same path down
until it falls off the tree, then hangs the new node there.

An **in-order traversal** (left subtree → node → right subtree) visits the values in
**sorted ascending order** — a neat property that falls straight out of the invariant, and
the easiest way to verify your tree is built correctly.

The catch: performance depends on the tree's **height**. A balanced tree has height
~log(n), giving O(log n) operations. But if you insert already-sorted data, the tree
degenerates into a glorified linked list of height n, and everything becomes O(n).
Self-balancing variants (AVL, red-black) fix this; we're building the plain version first.

## Cost summary
- `insert` / `contains` / `erase`: **O(h)** where `h` is height — **O(log n)** if balanced,
  **O(n)** worst case (degenerate / sorted-input tree)
- `in_order` traversal: **O(n)**, yields **sorted** order

## Contract — `bst.h`
```cpp
template <typename T>
class BST {
public:
    BST();
    ~BST();

    void insert(const T& value);     // duplicates are ignored (no-op, size unchanged)
    bool contains(const T& value) const;
    bool erase(const T& value);      // true if a node was removed, else false

    T min() const;                   // smallest value  (assumes non-empty)
    T max() const;                   // largest value   (assumes non-empty)

    std::vector<T> in_order() const; // all values, ascending sorted order

    std::size_t size() const;
    bool        empty() const;
};
```

Notes the tests assume:
- `Node` is a private nested struct: `struct Node { T value; Node* left; Node* right; };`.
- Comparisons use `<` / `>` (or `<` only) on `T`.
- **Duplicates are ignored**: inserting a value already present is a no-op and does not
  change `size()`.
- `erase` must handle all three classic cases: removing a **leaf**, a node with **one
  child**, and a node with **two children** (replace with its in-order successor or
  predecessor). It returns `false` if the value isn't in the tree.
- `min()` / `max()` assume the tree is non-empty.
- `in_order()` returns a `std::vector<T>` in ascending order (include `<vector>`).
