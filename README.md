
# The Tenerife Sea 🌊 

A comprehensive repository for competitive programming, algorithmic implementations, and data structure practices in C++. 

This repository serves as a personal codebase and documentation hub, with a **heavy emphasis on Mathematics and Number Theory** applied in competitive programming (e.g., CSES Problem Set).

## 📐 Highlight: Mathematics & Number Theory
A significant portion of this repository is dedicated to exploring and optimizing mathematical algorithms. Moving beyond basic implementations, the math module includes mathematical proofs, time/space complexity analysis, and competitive programming templates.

*   **Prime Algorithms:** Sieve of Eratosthenes ($O(N \log \log N)$), $O(\sqrt{N})$ trial division, prime gap theories, and next-prime calculations.
*   **Combinatorics & Set Theory:** In-depth application of the **Inclusion-Exclusion Principle** (e.g., Prime Multiples problem), bitwise state enumeration, and permutation sequencing/generation.
*   **Arbitrary-Precision Arithmetic (BigInt):** Custom implementations of large number addition, subtraction, multiplication, and division, including vector-based storage, carry processing, and leading-zero optimizations.
*   **Modular Arithmetic:** Euler's totient function, fast exponentiation, and modular multiplicative inverses.

## 📚 Repository Structure

*   `Algo_cpp_ex/` - Core C++ algorithm implementations and problem-solving.
    *   `01_basics/` - BigInt arithmetic, prefix sums, difference arrays, binary search.
    *   `02_data_structure/` - Linked lists, monotonic stacks/queues, Union-Find (Disjoint Set), Trie, Heaps.
    *   `03_search_graph/` - DFS/BFS, Shortest Path algorithms, Topological Sorting.
    *   `CSES/Mathematics/` - **Advanced math problems and proofs** from the CSES platform.
    *   `debug/` - Comprehensive guides on VSCode compiler configuration, GDB/LLDB debugging, and C++ macros (`define.cpp`).
*   `pta/` - Solutions for the PAT (Programming Ability Test) platform.
    *   `chapter3_Stack_Queue/` - Practical applications like parenthesis matching and expression evaluation.

## 🛠️ Core Topics

### Data Structures
*   **Linear:** Singly/Doubly linked lists, Monotonic Stacks & Queues.
*   **Advanced:** Union-Find (Connectivity maintenance), Trie (Prefix queries), Priority Queues.
*   **Trees:** Binary Search Trees, Tree Traversals, Segment Trees (WIP).

### Graph Theory & Search
*   **Search:** Depth-First Search (DFS) with backtracking, Breadth-First Search (BFS).
*   **Shortest Path:** Dijkstra, Bellman-Ford (negative weights), Floyd-Warshall (multi-source).
*   **Graph Processing:** Topological sorting, Connected components, Minimum Spanning Trees (Kruskal/Prim).

### Algorithmic Paradigms
*   Greedy Algorithms & Dynamic Programming (DP)
*   Divide & Conquer
*   Bitwise Operations & Wheel Factorization

## 💎 Code Quality & Documentation

To ensure long-term readability and reusability, the code in this repository adheres to strict documentation standards:
*   **Bilingual Comments:** Detailed line-by-line explanations in both English and Chinese.
*   **Mathematical Proofs:** Pre-requisite formulas and proofs are documented before implementation.
*   **Complexity Analysis:** Explicit $O(N)$ time and space complexity annotations.
*   **ASCII Visualizations:** Text-based diagrams illustrating data structure states (e.g., step-by-step BFS queue snapshots).
*   **Out-of-the-box Templates:** Highly optimized, reusable code snippets for competitive programming.

## 🚀 Quick Start

**Requirements:** GCC 9+ or Clang 10+ with C++17 support.

```bash
# Clone the repository
git clone https://github.com/Tenerife-Q/the-Tenerife-sea.git
cd the-Tenerife-sea

# Compile with C++17 standards
g++ -std=c++17 -O2 -o output filename.cpp

# Execute
./output
```

## 📊 Roadmap & Progress

| Module | Status | Key Topics |
| :--- | :--- | :--- |
| **Basics** | Completed | BigInt, Prefix Sums, Binary Search |
| **Data Structures** | Completed | Stacks, Queues, Union-Find, Trie |
| **Graph & Search** | Completed | DFS/BFS, Dijkstra, Bellman-Ford |
| **CSES Mathematics**| Active | Primes, Inclusion-Exclusion, Permutations |
| **Advanced Data Structs**| Planned | Segment Trees, Suffix Arrays |

## 📚 Resources & References
*   [CSES Problem Set](https://cses.fi/) - Main source for mathematical challenges.
*   [AcWing](https://www.acwing.com/) - Foundational algorithm courses.
*   *Introduction to Algorithms* (CLRS)

## 📄 License
Released under the[MIT License](LICENSE). 

---
*Maintainer: [Tenerife-Q](https://github.com/Tenerife-Q) | Last Updated: March 2026*
