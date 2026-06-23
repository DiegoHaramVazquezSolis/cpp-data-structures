# #8 — Binary Min-Heap

## What it is, in words
A heap is a tree-shaped structure tuned for one question: **"what's the smallest (or
largest) element right now?"** A **min-heap** answers "smallest" in O(1) and lets you
remove it in O(log n). It does **not** keep everything fully sorted — it maintains just
enough order to know the minimum.

The rule is the **heap property**: every node's value is **≤** the values of its children.
So the global minimum is always at the **root**. Nothing is promised about left-vs-right
ordering between siblings — only the parent-below-children relationship — which is why a
heap is cheaper to maintain than a fully sorted structure.

The clever part is the storage: a heap is a **complete binary tree** (every level full,
last level filled left-to-right), and a complete tree maps perfectly onto a **plain
array** with no pointers at all. For a node at index `i`:
- its left child is at `2*i + 1`,
- its right child is at `2*i + 2`,
- its parent is at `(i - 1) / 2`.

Two repair operations keep the property intact:
- **sift up** (a.k.a. bubble up): after inserting at the end of the array, swap the new
  element upward with its parent until it's no longer smaller than its parent.
- **sift down** (a.k.a. bubble down / heapify): after removing the root, move the last
  element to the root and swap it downward with its smaller child until the property holds.

Heaps power priority queues, scheduling, Dijkstra's algorithm, and heapsort.

## Cost summary
- `top` (peek minimum): **O(1)**
- `push` (sift up) / `pop` (sift down): **O(log n)**
- a heap is **not** sorted; only the minimum is directly accessible

## Contract — `heap.h`
```cpp
template <typename T>
class MinHeap {
public:
    MinHeap();
    ~MinHeap();

    void push(const T& value);   // insert, then sift up
    void pop();                  // remove the minimum (root), then sift down

    const T& top() const;        // the current minimum (assumes non-empty)

    std::size_t size() const;
    bool        empty() const;
};
```

Notes the tests assume:
- It's a **min**-heap: `top()` is the **smallest** element, and repeated `pop()` yields
  values in **ascending** order.
- Comparisons use `<` on `T`.
- `top()` / `pop()` assume the heap is non-empty.
- You may store the elements in any array-like backing (your own buffer, or reuse your
  `DynamicArray`, or `std::vector` — your choice; the tests only check behavior).
