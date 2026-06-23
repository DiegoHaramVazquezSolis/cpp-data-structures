# #5 — Doubly Linked List

## What it is, in words
A doubly linked list is a singly linked list where every node stores **two** pointers:
one to the **next** node and one to the **previous** node. The list keeps both a **head**
and a **tail**. Because each node knows its predecessor, you can walk the list in either
direction, and — crucially — you can remove the **last** node in **O(1)**: you no longer
have to walk from the head to find the node before the tail, because the tail already
points back to it.

The trade-off versus a singly linked list: every node costs an extra pointer of memory,
and every insertion/removal must rewire **twice** as many links (both `next` and `prev`),
so there are more edge cases to get right. In exchange you get O(1) removal at both ends
and the ability to delete a known node in O(1).

This is the structure behind LRU caches, text editors' cursors, and `std::list`.

## Cost summary
- `push_front` / `push_back` / `pop_front` / `pop_back`: **O(1)** (this is the win —
  `pop_back` is now O(1), unlike the singly linked list)
- access / search by position: **O(n)**

## Contract — `doubly_linked_list.h`
```cpp
template <typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void push_front(const T& value);   // O(1)
    void push_back(const T& value);    // O(1)
    void pop_front();                  // O(1)
    void pop_back();                   // O(1)  <-- the reason this structure exists

    T&       front();
    T&       back();

    T&       at(std::size_t i);        // throws std::out_of_range
    const T& at(std::size_t i) const;

    std::size_t size() const;
    bool        empty() const;
    void        clear();
};
```

Notes the tests assume:
- `Node` is a private nested struct: `struct Node { T value; Node* prev; Node* next; };`.
- Keep `head_`, `tail_`, `size_`, and maintain **both** link directions on every op.
- Edge cases to nail: inserting into an empty list (head == tail, both end pointers of
  the lone node are null), and removing the last remaining node (head and tail both
  become `nullptr`).
- `at(i)` throws `std::out_of_range` for `i >= size()`.
