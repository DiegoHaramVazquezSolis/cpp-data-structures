# #2 — Singly Linked List

## What it is, in words
A linked list stores elements in separate **nodes** scattered anywhere in memory.
Each node holds two things: the **value**, and a **pointer to the next node**. The
list itself remembers a pointer to the **head** (first node). The last node's `next`
is `nullptr`, which is how you know you've reached the end.

This is the conceptual opposite of the dynamic array:

- **Array:** contiguous memory → O(1) random access by index, but inserting at the
  front means shifting everything (O(n)).
- **Linked list:** scattered memory → **no** random access (to reach index `k` you
  walk `k` hops from the head, O(n)), but inserting/removing at the **front is O(1)** —
  allocate a node and rewire two pointers. No shifting, ever.

The core skill is **pointer rewiring**: order of assignment matters, and every
off-by-one and null-pointer bug lives in the edge cases (empty list, single element,
removing the last node). Caching a **tail** pointer makes `push_back` O(1).

## Cost summary
- `push_front` / `pop_front`: **O(1)**
- `push_back`: **O(1)** with a tail pointer
- `pop_back`: **O(n)** (singly linked — you can't step backward; you walk from head)
- access / search by position: **O(n)**

## Contract — `linked_list.h`
```cpp
template <typename T>
class LinkedList {
public:
    LinkedList();
    ~LinkedList();                        // free every node

    void push_front(const T& value);      // O(1)
    void push_back(const T& value);       // O(1) with tail pointer
    void pop_front();                     // remove first node
    void pop_back();                      // remove last node (O(n) walk)

    T&       front();                     // first value
    T&       back();                      // last value

    T&       at(std::size_t i);           // walk i hops; throws std::out_of_range
    const T& at(std::size_t i) const;

    std::size_t size() const;
    bool        empty() const;
    void        clear();                  // free all nodes, size -> 0
};
```

Notes the tests assume:
- `Node` is a private nested struct: `struct Node { T value; Node* next; };`.
- Keep `head_`, `tail_`, `size_`. `push_back` must be O(1).
- `at(i)` throws `std::out_of_range` for `i >= size()`.
- `front()` / `back()` assume non-empty.
- Watch the empty-list and last-node-removal cases: `tail_` must be reset to
  `nullptr` when the list becomes empty.
