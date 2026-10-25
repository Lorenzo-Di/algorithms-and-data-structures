# Generic Chained Hash Table & Lexical Analyzer

## Architecture & Complexity
This module provides a type-generic **Hash Table with Separate Chaining** (`HashTable`), supporting arbitrary key and value types via `void*` pointers, custom hash functions, and key comparators.

* **Dynamic Resizing:** Automatically expands bucket capacity when the load factor $\alpha = N / M$ exceeds the threshold, preserving **$O(1)$ amortized time complexity** for `put`, `get`, `contains_key`, and `remove`.
* **Ownership Semantics:** The container manages internal node allocations and bucket arrays while leaving key/value lifecycle management to the caller, preventing double-free vulnerabilities in generic contexts.
* **Application Benchmark:** Used in `main_ex2` to parse Homer's *Iliad* and compute the highest-frequency words matching a minimum length constraint in linear time with respect to text size.

---

## Methodology Case Study: Auditing LLM-Generated C Code
As part of an experimental software engineering requirement, initial scaffolding for this module was generated iteratively using a Large Language Model (LLM) under strict architectural constraints (Doxygen documentation, modular functions $< 30$ lines, strict compiler flags `-Wall -Wextra -Werror`, and Unity unit testing).

### Critical Engineering Interventions & Refactoring
Direct evaluation of the LLM output revealed several classic pitfalls in automated C code generation that required manual architectural correction:

1. **Asymptotic Complexity Enforcement (Dynamic Resizing):** The initial generated implementation omitted load-factor monitoring in `hash_table_put`, which would have degraded lookups from $O(1)$ to $O(N)$ on large datasets. A dedicated rehashing helper was engineered to maintain constant amortized complexity.
2. **Polymorphism & Type Erasure Violations:** During the implementation of `hash_table_remove`, the model regressed from generic `void*` pointers and user-supplied comparator callbacks to hardcoded `char*` casts and `strcmp` calls. This was refactored to strictly enforce type erasure.
3. **Memory Ownership & Safety:** In `hash_table_free`, the generated draft attempted to call `free()` directly on user-provided `const void*` keys and values, violating both the API contract and `const`-correctness (and risking segmentation faults on stack-allocated keys).
4. **API Contract Consistency:** Resolved signature drifts between header declarations and source definitions (e.g., return type mismatches between `int` and `bool` in `hash_table_contains_key` and error sentinel values).