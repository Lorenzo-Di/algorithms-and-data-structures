# Graph Library and Breadth-First Search

## Implementation Choices

### 1. Data Structure Design
Two possible representations were analyzed and discarded in favor of a nested Hash Table approach:
* **Adjacency Matrix:** Rejected due to $O(N^2)$ memory usage, which is inefficient for sparse graphs.
* **Adjacency Lists:** Better in memory for sparse graphs but with $O(Degree)$ lookup time for edge existence checks.

For this library, the choice was to implement a variation of Adjacency Lists using an **Adjacency Map**, to combine the memory efficiency for sparse graphs with the fast lookup time of hash maps.

The chosen **Adjacency Map** (a Main Hash Table mapping Nodes to Nested Hash Tables of neighbors) ensures that memory usage remains proportional to the number of edges $O(E)$, satisfying the sparsity requirement while providing superior access times.

### 2. Time Complexity
By utilizing the amortized constant time of Hash Table operations, the library achieves:
* **Edge Operations:** `add_edge`, `remove_edge`, and `contains_edge` achieve **$O(1)$ amortized complexity**.
* **Node Operations:** `add_node` and `contains_node` are $O(1)$. `remove_node` remains $O(N)$ as it necessitates scanning the adjacency structures of other nodes to remove incident edges (in the directed case).
* **Undirected Graphs:** Implemented as a simplified abstraction over the directed logic; adding an undirected edge $(u, v)$ automatically also adds $(v, u)$, trading a slight memory increase for code reuse and simplicity.

## BFS Simulation

The simulation on `italian_dist_graph.csv` validates the correctness of the search.
* **Algorithm:** Implemented using a FIFO **Queue** for the nodes that need to be visited and a **Hash Set** to track already visited nodes in $O(1)$, ensuring linear total complexity $O(N + E)$.

### Possible improvement
**Hybrid Storage for Low-Degree Nodes:** Currently, every node allocates a full Hash Table structure for its neighbors. For nodes with very low degree (e.g., $< 5$, common in road networks), the memory overhead of the Hash Table struct is significant compared to a simple dynamic array. A hybrid approach switching between array and hash table based on degree threshold would optimize memory usage without compromising performance.