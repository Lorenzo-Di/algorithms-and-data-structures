# Ternary Heap Library, Priority Queue and cpu task scheduler

## Complexity and Performance

The **Ternary Heap** maintains the same time complexity as a standard Binary Heap for basic operations $O(\log N)$, but with specific advantages due to some implementation choices.

### 2. Hash Table Optimization
The standard implementation of `contains` and `remove` on a heap would strictly be $O(N)$ due to linear scanning.
By utilizing an **Auxiliary Hash Table** that maps `element_pointer -> heap_index`, we achieve:
* **Contains:** $O(1)$ amortized complexity.
* **Remove:** $O(\log N)$ total complexity ($O(1)$ to find the index + $O(\log N)$ to restore the heap property).

This makes the structure significantly faster for scenarios involving frequent updates or checks on specific tasks, which is critical for the scheduler simulation, at the cost of more complex code logic, requiring to update the hash table everytime the heap updates.

## Task Scheduler Simulation

The simulation on `tasks.csv` finishes in under 1 second with 1 million records, confirming the correctness of the $O(N \log N)$ total sorting logic.
* **Non-preemptive Logic:** Validated that tasks run to completion once started.
* **Idle Management:** The scheduler correctly handles time gaps when no tasks are available.
* **Priority:** Verified that among available tasks, the one with the highest priority is always chosen.

### Possible improvement
**Memory Pre-allocation:** Currently, `realloc` is used when capacity is reached. Since we know the line count of the CSV beforehand, we could allocate the exact memory needed for the internal array `void **heap` immediately to avoid resizing overhead.