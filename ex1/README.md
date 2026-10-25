# Generic Hybrid Sorting Library (QuickSort + SelectionSort)

## Overview
This module implements a type-generic hybrid sorting algorithm (`hybridsort`) in C that combines **3-way QuickSort** for large partitions ($n \ge k$) with **SelectionSort** for small sub-arrays ($n < k$). 

Although SelectionSort has an asymptotic time complexity of $O(n^2)$ compared to QuickSort's $O(n \log n)$, it exhibits a significantly smaller constant factor $c$ and avoids recursive function call overhead on tiny partitions.

## Experimental Benchmark (20 Million Records)
The library was benchmarked on a binary dataset (`records.bin`) consisting of **20,000,000 packed 36-byte records**:
* `id`: 64-bit unsigned integer (8 bytes, little-endian)
* `field1`: 32-bit IEEE 754 float (4 bytes, little-endian)
* `field2`: 64-bit signed integer (8 bytes, little-endian)
* `field3`: 16-byte null-padded ASCII string

### Execution Times by Threshold ($k$)

| Threshold ($k$) | `id` (uint64) | `field1` (float32) | `field2` (int64) | `field3` (char[16]) |
| :--- | :--- | :--- | :--- | :--- |
| **0 (Pure QuickSort)** | 5.95s | 3.88s | 5.79s | 4.81s |
| **10** | **5.68s** | **3.78s** | **5.61s** | **4.75s** |
| **50** | 5.81s | 3.84s | 5.71s | 4.79s |
| **100** | 6.01s | 4.05s | 5.86s | 5.09s |
| **500** | 8.47s | 5.46s | 8.36s | 8.09s |
| **1,000** | 11.70s | 7.57s | 11.72s | 11.93s |
| **5,000** | 45.06s | 27.42s | 45.03s | 50.16s |
| **10,000** | 1m 32s | 55.55s | 1m 31s | 1m 43s |
| **1,000,000** | > 5m (Timeout) | > 5m (Timeout) | > 5m (Timeout) | > 5m (Timeout) |

## Performance & Hardware-Level Analysis

### 1. Optimal Cutoff Threshold ($k$)
Experimental results confirm the theoretical hypothesis: transitioning to SelectionSort at $k \in [10, 50]$ consistently outperforms pure QuickSort ($k=0$). Fine-grained profiling indicates an optimal sweet spot around **$k \approx 15$**, reducing recursion depth and stack frame overhead. Replacing SelectionSort with InsertionSort would allow an even higher cutoff threshold due to adaptive early termination on nearly-sorted partitions.

### 2. CPU Cache Locality & Data Type Impact
* **`field1` (32-bit float, 4 bytes):** Fastest across all thresholds due to **spatial locality** and memory bandwidth efficiency during comparison operations.
* **`field3` (16-byte string):** At low $k$ values, sorting strings is faster than sorting 64-bit integers (`id` and `field2`). Because the strings are extracted from natural language (Dante's *Divine Comedy*), the dataset contains a high frequency of duplicate keys. Our **3-way partitioning** groups duplicates in linear time, and `strcmp` typically resolves comparisons within the first few characters. As $k$ grows, SelectionSort cannot exploit duplicate keys, causing `field3` to become the slowest field.
* **`id` and `field2` (64-bit integers, 8 bytes):** Exhibit nearly identical performance profiles, as they occupy the same memory footprint and map to equivalent CPU comparison instructions.

### Future Optimizations
1. **Natural Run Detection:** Pre-scanning for pre-existing monotonic sequences (similar to Timsort) to avoid unnecessary partitioning on partially ordered real-world data.
2. **Median-of-Three / Ninther Pivot Selection:** Replacing random pivot selection with a cache-friendly median-of-three strategy to produce better-balanced partitions and reduce recursion depth.