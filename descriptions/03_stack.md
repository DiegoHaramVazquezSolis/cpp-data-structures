# #3 — Stack (LIFO)

## What it is, in words
A stack is a container with a single rule: **Last In, First Out**. You can only add
("push") and remove ("pop") at **one end**, called the *top*. The most recently pushed
element is the only one you can see or remove. Think of a stack of plates: you add to
the top and take from the top; you never pull from the middle or bottom.

A stack is an **adapter** — it's not really a new memory layout, it's a *restricted
interface* over something else. You can back it with a dynamic array (push/pop at the
end) or a singly linked list (push/pop at the front). Either gives O(1) operations.
The whole point is the discipline of the interface, not the storage.

Stacks are everywhere: function call stacks, undo/redo, expression evaluation,
backtracking, depth-first search.

## Cost summary
- `push` / `pop` / `top`: **O(1)**
- search: not a stack operation (you only ever touch the top)

## Contract — `stack.h`
```cpp
template <typename T>
class Stack {
public:
    Stack();
    ~Stack();

    void push(const T& value);   // add on top
    void pop();                  // remove the top element

    T&       top();              // the most recently pushed element
    const T& top() const;

    std::size_t size() const;
    bool        empty() const;
    void        clear();
};
```

Notes the tests assume:
- LIFO order: pushing `a, b, c` then popping yields `c, b, a`.
- `top()` / `pop()` assume the stack is non-empty.
- You choose the backing storage (array-style or list-style); the tests only check
  behavior, not how you store it.
