# Sparse Graph Library (Adjacency Map) & Breadth-First Search

## Data Structure Design
To represent large **sparse graphs** ($E \ll V^2$) with generic node types and edge labels, three representations were evaluated:
1. **Adjacency Matrix:** Discarded due to $\Theta(V^2)$ space complexity, which is prohibitive for sparse networks.
2. **Standard Adjacency Lists:** Offers $O(V + E)$ space efficiency, but edge existence queries (`contains_edge`, `get_label`) require $O(\deg(u))$ linear scans.
3. **Adjacency Map (Selected Architecture):** Implemented as a **Nested Hash Table** structure—a primary Hash Table mapping each vertex $u$ to a secondary Hash Table of its incident edges $(v \to \text{label})$.

### Asymptotic Complexity Guarantees
By leveraging the $O(1)$ amortized complexity of the underlying Hash Table:
* **Space Complexity:** $O(V + E)$, strictly proportional to active vertices and edges.
* **Vertex Operations:** `graph_add_node`, `graph_contains_node`, and `graph_num_neighbours` execute in **$O(1)$** amortized time; `graph_remove_node` executes in **$O(V + E)$** (or $O(V)$ under sparsity assumptions).
* **Edge Operations:** `graph_add_edge`, `graph_remove_edge`, `graph_contains_edge`, and `graph_get_label` all achieve **$O(1)$** amortized complexity.
* **Undirected Graph Abstraction:** Built cleanly atop the directed engine by symmetrically maintaining edges $(u, v)$ and $(v, u)$ while adjusting edge counts and iteration accordingly.

## Breadth-First Search (BFS) on Road Networks
The library includes a generic `breadth_first_visit` implementation tested against the Italian road distance dataset:
* **Linear Time Traversal:** Combines a FIFO **Queue** for frontier exploration with a **Hash Set** for $O(1)$ visited-node tracking, guaranteeing optimal **$O(V + E)$** traversal time.

### Future Optimization
* **Small-Buffer Optimization (SBO) for Low-Degree Vertices:** In real-world road networks, most vertices have a very low degree ($\deg(v) \le 4$). Using an inline static array for vertices below a degree threshold (e.g., $\deg(v) < 8$) and dynamically promoting to a Hash Table only for high-degree hubs would significantly reduce memory fragmentation and pointer chasing.