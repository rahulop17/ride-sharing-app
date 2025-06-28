---

## Features

- Represents city roads as a **general weighted graph**
- Computes **shortest paths using Dijkstra's algorithm**
- Precomputes shortest paths from all relevant pickup/dropoff points
- Applies **5 carpooling scenarios** with level-of-service filtering
- Outputs **pairwise shared cost** between all passenger combinations

---

## Core Concepts

- **Graph Representation:** Weighted, undirected adjacency list
- **Passengers:** Each has a pickup and dropoff node
- **Distance Calculation:** Uses Dijkstra from relevant nodes only (optimized)
- **Level of Service:** A passenger will only be pooled if the extra travel is ≤25% over solo distance
- **Matching Logic:** Uses minimum shared distance across valid pooling scenarios

---

## 🚦 Pooling Scenarios

For each pair of passengers **X** and **Y** (with pickup points `X1`, `Y1` and dropoff points `X2`, `Y2`), 5 possible ride-sharing paths are evaluated:

| Scenario | Route Description | Formula |
|----------|--------------------|---------|
| **1 (a)** | Pick up X → pick up Y → drop off X → drop off Y | `X1 → Y1 → X2 → Y2` |
| **2 (b)** | Pick up X → pick up Y → drop off Y → drop off X | `X1 → Y1 → Y2 → X2` |
| **3 (c)** | Pick up Y → pick up X → drop off X → drop off Y | `Y1 → X1 → X2 → Y2` |
| **4 (d)** | Pick up Y → pick up X → drop off Y → drop off X | `Y1 → X1 → Y2 → X2` |
| **5**     | Both passengers travel alone | `X1 → X2` + `Y1 → Y2` |

After calculating travel costs for all scenarios using **Dijkstra's algorithm**, the minimum cost is selected **only if the "level of service" condition is satisfied**.

---

## How to Compile and Run

### Requirements

- Standard C++ compiler (`g++`, `clang++`, etc.)

### Compilation

```bash
g++ main.cpp -o carpooling
