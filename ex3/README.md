# Ternary Heap Priority Queue & CPU Task Scheduler

## Architecture & Complexity
This module implements a generic **Priority Queue** backed by a dynamic **Ternary Heap** ($d=3$), where each parent node dominates up to three children. 

### 1. Ternary vs. Binary Heap Trade-offs
A 3-ary heap reduces tree height to $\lfloor \log_3 N \rfloor$, resulting in shallower upward percolation (`push`) at the cost of at most one additional comparison per level during downward percolation (`pop`). Contiguous array storage ensures strong CPU cache locality.

### 2. $O(1)$ Lookup & $O(\log_3 N)$ Arbitrary Removal via Auxiliary Hash Table
In a standard heap, `contains` and `remove` require an $O(N)$ linear scan. By coupling the heap array with our generic **Hash Table** (from Module 2) mapping `element_pointer -> heap_index`, every index swap during heapify operations is synchronized in $O(1)$ amortized time:
* **`priority_queue_contains`:** **$O(1)$** amortized time complexity.
* **`priority_queue_remove`:** **$O(\log_3 N)$** total time complexity ($O(1)$ index lookup + $O(\log_3 N)$ sift-up/sift-down restoration).

## Non-Preemptive CPU Scheduler Simulation
The priority queue powers a discrete-event simulation of a single-core, non-preemptive priority task scheduler (`main_ex3`):
* **High Throughput:** Processes **1,000,000 tasks** in **under 1 second**, empirically validating the $O(N \log_3 N)$ overall scheduling complexity.
* **Execution Model:** Accurately handles CPU idle jumps ($t \to \text{next arrival}$) and priority arbitration among all arrived tasks ($\text{Start} \le t$).

### Future Optimization
* **Capacity Pre-allocation:** Adding a `priority_queue_reserve(size_t capacity)` API to pre-allocate the internal `void **heap` buffer when input size is known ahead of time, eliminating dynamic `realloc` overhead.