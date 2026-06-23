# #6 — Hash Table (separate chaining)

## What it is, in words
A hash table stores **key → value** pairs and gives you **average O(1)** insert, lookup,
and delete — no ordering, just "do I have this key, and what's mapped to it?"

The idea: keep an array of **buckets**. To find where a key goes, run the key through a
**hash function** that produces a big integer, then take it **modulo the bucket count**
to get an index. Ideally each key lands in its own bucket. But different keys can hash to
the same index — a **collision**. The **separate chaining** strategy handles collisions by
making each bucket a small **linked list** (a "chain") of all entries that landed there.
To look up a key: hash it to a bucket, then walk that bucket's short chain comparing keys.

Two numbers govern performance:
- **bucket count** — the size of the array.
- **load factor** = number of entries / bucket count. As it grows, chains get longer and
  lookups slow down. When the load factor crosses a threshold (commonly ~0.75), you
  **rehash**: allocate a larger bucket array and redistribute every entry. This keeps the
  average chain length near constant, which is what preserves O(1).

A good hash function spreads keys uniformly; a bad one piles everything into one chain and
degrades the table to O(n). For this exercise you may use `std::hash<K>`.

## Cost summary
- `insert` / `at` / `contains` / `erase`: **O(1) average**, O(n) worst case (all keys
  collide into one chain)
- the table is **unordered** — there is no "first" or "sorted" key

## Contract — `hash_table.h`
```cpp
template <typename K, typename V>
class HashMap {
public:
    HashMap();
    ~HashMap();

    void insert(const K& key, const V& value);  // insert new, or overwrite existing
    bool erase(const K& key);                    // true if a key was removed, else false
    bool contains(const K& key) const;

    V&       at(const K& key);                   // throws std::out_of_range if absent
    const V& at(const K& key) const;

    V&       operator[](const K& key);           // returns existing, or inserts a
                                                 // value-initialized V() and returns it

    std::size_t size() const;                    // number of key/value pairs
    bool        empty() const;
};
```

Notes the tests assume:
- `insert` with an existing key **overwrites** the value and does **not** increase `size()`.
- `operator[]` on a missing key **creates** an entry with a default-constructed value
  (`V()` — e.g. `0` for `int`), increasing `size()`, then returns a reference to it.
- `at` on a missing key throws `std::out_of_range`.
- The table must keep working correctly across a rehash (the tests insert enough distinct
  keys to force chains and/or a resize).
- You may use `std::hash<K>` for hashing. Buckets via separate chaining (a chain per
  bucket); you may use your own linked nodes or any list you like.
