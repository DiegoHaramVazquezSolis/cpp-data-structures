# Data Structures from Scratch (C++20)

A hands-on training ground where I re-implement the classic data structures **from
scratch** in modern C++ — no `std::vector`, no `std::list`, no `std::unordered_map`.
The goal is to rebuild the muscle memory behind these containers (raw pointers, manual
memory management, complexity trade-offs) and to be sharp for technical interviews.

Every structure is a single self-contained header, paired with a description that
explains *what it is and why it exists*, and a standalone test suite that proves it
works — including under the AddressSanitizer.

## Why this repo exists

Most day-to-day C++ leans on the standard library, which hides the interesting parts:
how a vector grows, how a hash table resolves collisions, why removing the tail of a
singly linked list is O(n). Rebuilding each container by hand surfaces all of that —
pointer rewiring, capacity growth, unsigned underflow, the rule of three/five — which
is exactly the material that comes up in interviews.

This is **deliberately a learning project**, so the workflow is unusual: an AI assistant
acts as coach and test-writer (see [AGENTS.md](AGENTS.md)) and writes the descriptions
and tests, while **all implementation code is mine**. The assistant never touches the
data-structure headers; it reviews them, runs the tests, and points out bugs and
interview-flavored gotchas.

## How the workflow goes

Each structure is one self-contained round:

1. **Read the spec** — `descriptions/NN_name.md` gives a words-only explanation plus a
   precise **contract**: the exact class name, file name, and method signatures the
   implementation must match.
2. **Implement it** — I write the header named in the contract (e.g. `stack.h`), with no
   implementation hints handed to me on purpose.
3. **Test it** — compile and run the matching `test_*.cpp`. Every test header carries its
   exact build command.
4. **Review** — once it's green, the header gets read for real bugs, portability issues,
   and edge cases (empty container, single element, last-node removal, complexity).

Nothing is called "done" until it passes the **sanitizer build**, not just a plain run —
leaks and dangling pointers hide behind a passing plain build:

```bash
# the build that counts
g++ -std=c++20 -Wall -Wextra -fsanitize=address,undefined -g test_NAME.cpp -o test_NAME && ./test_NAME

# plain build
g++ -std=c++20 -Wall -Wextra test_NAME.cpp -o test_NAME && ./test_NAME
```

The tests use a tiny built-in `CHECK` / `SECTION` harness — no external framework, no
dependencies beyond a C++20 compiler.

## Roadmap (easiest → hardest)

| #  | Structure                     | Header                   | Status |
|----|-------------------------------|--------------------------|--------|
| 1  | Dynamic Array                 | `dynamic_array.h`        | ✅ done |
| 2  | Singly Linked List            | `linked_list.h`          | ✅ done |
| 3  | Stack (LIFO)                  | `stack.h`                | ✅ done |
| 4  | Queue (FIFO)                  | `queue.h`                | ✅ done |
| 5  | Doubly Linked List            | `doubly_linked_list.h`   | ⬜ next |
| 6  | Hash Table (separate chaining)| `hash_table.h`           | ⬜ todo |
| 7  | Binary Search Tree            | `bst.h`                  | ⬜ todo |
| 8  | Binary Min-Heap               | `heap.h`                 | ⬜ todo |
| 9  | Graph (adjacency list)        | `graph.h`                | ⬜ todo |

**Planned follow-up rounds** (after the nine are done):
- **Rule of three/five** — copy and move semantics on the owning containers (until then
  these containers must *not* be copied by value — raw owning pointers mean double-free).
- Possibly iterators, a circular-buffer queue, and a self-balancing tree.

## Conventions

- Each header is **self-contained** — it includes everything it uses.
- `at()` and key-checked accessors throw `std::out_of_range`; `front()`, `back()`,
  `top()`, `min()`, `max()` may assume the container is non-empty.
- Descriptions live under `descriptions/`, tests at the repo root, both named after the
  structure.

## Layout

```
descriptions/   words-only spec + contract for each structure
*.h             my implementations (one self-contained header each)
test_*.cpp      standalone test suite per structure
AGENTS.md       the coaching/test-writing rules the AI assistant follows
CMakeLists.txt  CLion project file (tests also build standalone via g++)
```

## Building

The tests are standalone — you don't need CMake, just a C++20 compiler:

```bash
g++ -std=c++20 -Wall -Wextra test_stack.cpp -o test_stack && ./test_stack
```

CLion users can also open the project directly; `CMakeLists.txt` wires up every test
target.
