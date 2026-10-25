# High-Performance Generic Data Structures & Algorithms in C

[![C Build & Valgrind CI](https://github.com/lorenzo-di/algorithms-and-data-structures/actions/workflows/ci.yml/badge.svg)](https://github.com/lorenzo-di/algorithms-and-data-structures/actions/workflows/ci.yml)

A collection of generic, memory-safe data structures and algorithms implemented from scratch in standard C. Designed to handle large-scale datasets (up to **20 million binary records** and **1 million scheduled tasks**), focusing on asymptotic complexity, CPU cache locality, and strict memory management.

## Key Engineering Highlights

* **Type-Generic Programming in C:** Full polymorphism achieved via `void*` data handling and user-supplied comparator/hash function pointers (`int (*compare)(const void*, const void*)`, `unsigned long (*hash)(const void*)`).
* **Large-Scale Benchmarking:** Stress-tested against multi-million record binary streams, massive plain-text documents, synthetic CPU task queues, and real-world spatial road networks.
* **Automated Unit Testing:** Comprehensive test suites built with the **Unity** framework covering edge cases, boundary thresholds, and degenerate inputs.
* **Memory Safety & Documentation:** Zero memory leaks verified via **Valgrind**; APIs documented using **Doxygen**.

---

## Repository Architecture

| Module | Directory | Core Implementation | Real-World Benchmark / Application |
| :--- | :--- | :--- | :--- |
| **1. Hybrid Introspective Sort** | [`ex1/`](./ex1) | Generic **QuickSort** (3-way partitioning) + **SelectionSort** cutoff | Sorting **20,000,000** packed binary records (36 bytes each) across 4 data types |
| **2. Chained Hash Table** | [`ex2/`](./ex2) | Generic **Hash Map** with separate chaining & dynamic resizing | High-speed lexical frequency analysis (tested on Homer's *Iliad*) |
| **3. Ternary Heap & Scheduler** | [`ex3/`](./ex3) | **3-ary Priority Queue** coupled with an auxiliary Hash Map for O(1) lookup | Non-preemptive CPU task scheduler simulating **1,000,000** processes in `< 1s` |
| **4. Sparse Graph & BFS** | [`ex4/`](./ex4) | Directed/Undirected **Adjacency Map** (nested Hash Tables) + **BFS** | Breadth-First Search traversal on the Italian road distance network |

---

## Building and Running Unit Tests

All modules and automated unit test suites are self-contained. Running `make test` from the root directory will automatically compile all libraries, CLI executables, test runners, and immediately execute the **Unity** test suites across all four modules:

```bash
# Compile everything and run all automated unit tests
make test

# Alternatively, compile binaries only (without running tests)
make all

# Remove all build/ and bin/ directories
make clean
```

### CLI Executables Usage
Once compiled, each module also provides a standalone CLI executable in its `bin/` directory to process custom input files matching the module's format:

* **Module 1 (Binary Record Sorter):** `./ex1/bin/main_ex1 <input.bin> <output.bin> <field: 1..4> <k_cutoff>`
* **Module 2 (Lexical Analyzer):** `./ex2/bin/main_ex2 <text_file.txt> <min_word_length>`
* **Module 3 (CPU Task Scheduler):** `./ex3/bin/main_ex3 <tasks_input.csv> <schedule_output.csv>`
* **Module 4 (Graph BFS Traversal):** `./ex4/bin/main_ex4 <graph_edges.csv> <start_node> <bfs_output.txt>`