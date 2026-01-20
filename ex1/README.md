# Experimental Analysis

|k      |id    |field1|field2|field3|
|-------|------|------|------|------|
|0      |5.95s |3.88s |5.79s |4.81s |
|10     |5.68s |3.78s |5.61s |4.75s |
|50     |5.81s |3.84s |5.71s |4.79s |
|100    |6.01s |4.05s |5.86s |5.09s |
|500    |8.47s |5.46s |8.36s |8.09s |
|1000   |11.70s|7.57s |11.72s|11.93s|
|5000   |45.06s|27.42s|45.03s|50.16s|
|10000  |1m 32s|55.55s|1m 31s|1m 43s|
|1000000|fail  |fail  |fail  |fail  |

## Hybrid approach advantages

The results are as theorically expected: both with $k=10$ and $k=10$ the hybrid approach is faster than pure quicksort ($k=0$).
An optimal value of k is certainly between 0 and 50, but by tring even more values of k many times it can be seen that the sweet spot is about $k=15$ for this particular algorithm.
The value k could be even higher if another low overhead algorithm with better performance than selection sort was used, like insertion sort.
Even though selection sort has $O(n^2)$ complexity we still have a gain in performance over quicksort's $O(n \log n)$ complexity for small values of n because of the simpler implementation: selection sort has a way **smaller constant factor $c$**.
Thanks to this hybrid approach we're also limiting recursion, and so maximum stack depth and memory usage.

## Differences Between Field Types

Performance differnces can be seen depending on the data type:
* **Field 1 (float, 4 bytes)** is the fastest to sort because of **spatial locality**: 4-byte values fit twice as densely into CPU cache lines compared to 8-byte integers  like *id* and *field2*, resulting in fewer cache misses.
* **Field 3 (string, 16 bytes)** with low values of *k*, so when using quicksort, it's faster than *id* and *field2* probably thanks to this specific data's structure and the use of **3-way partitioning**, likely there are more equal values compared to the other fields, making it already partially ordered, and probably strcmp can recognize the bigger of the strings in the first few bytes. However, when *k* increases it starts becoming slower because it can no longer take advantage of the equal values with selection sort.
* **Id and Field 2(uint and int, 8 bytes)** are very similar since they have the same size and the cpu instruction to compare them is the same.

### Possible improvements
1. If we know we're going to be dealing with real world data we should check for *runs*: blocks of data already ordered that we don't need to shuffle around.
2. Use a more cache friendly pivoting strategy: the implemented quicksort uses a random pivot to avoid worst case scenario on crafted data, but this also drastically increases recursion on real unsorted data by making unbalanced partitions, where a median of three startegy or similar would work better.