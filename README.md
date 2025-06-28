---

## 📌 Features

- Represents city roads as a **general weighted graph**
- Computes **shortest paths using Dijkstra's algorithm**
- Precomputes shortest paths from all relevant pickup/dropoff points
- Applies **5 carpooling scenarios** with level-of-service filtering
- Outputs **pairwise shared cost** between all passenger combinations

---

## 🧠 Core Concepts

- **Graph Representation:** Weighted, undirected adjacency list
- **Passengers:** Each has a pickup and dropoff node
- **Distance Calculation:** Uses Dijkstra from relevant nodes only (optimized)
- **Level of Service:** A passenger will only be pooled if the extra travel is ≤25% over solo distance
- **Matching Logic:** Uses minimum shared distance across valid pooling scenarios

---

## ✅ How to Compile and Run

### Requirements

- C++17 or higher
- Standard C++ compiler (`g++`, `clang++`, etc.)

### Compilation

```bash
g++ main.cpp graph.cpp passenger.cpp -o carpooling
