# #4 — Queue (FIFO)

## What it is, in words
A queue is the mirror image of a stack: **First In, First Out**. You add at one end
(the *back*) and remove from the *other* end (the *front*). Think of a line of people:
the first to arrive is the first to be served. The element you can remove is always the
oldest one still in the container.

Like the stack, a queue is an **adapter** — a restricted interface over some storage.
The natural backing is a **singly linked list with a tail pointer**: enqueue at the
tail, dequeue at the head, both O(1). (Backing it with a plain dynamic array is awkward
because removing from the front is O(n) — the standard fix is a *circular buffer*, which
you can explore later.)

Queues are the backbone of breadth-first search, scheduling, buffering, and producer/
consumer pipelines.

## Cost summary
- `push` (enqueue at back) / `pop` (dequeue from front) / `front` / `back`: **O(1)**
- search: not a queue operation

## Contract — `queue.h`
```cpp
template <typename T>
class Queue {
public:
    Queue();
    ~Queue();

    void push(const T& value);   // enqueue at the back
    void pop();                  // dequeue from the front

    T&       front();            // oldest element (next to be removed)
    const T& front() const;
    T&       back();             // newest element (just pushed)
    const T& back() const;

    std::size_t size() const;
    bool        empty() const;
    void        clear();
};
```

Notes the tests assume:
- FIFO order: pushing `a, b, c` then popping yields `a, b, c`.
- `front()` / `back()` / `pop()` assume the queue is non-empty.
- After draining to empty, the queue must still be usable (front/back pointers reset).
