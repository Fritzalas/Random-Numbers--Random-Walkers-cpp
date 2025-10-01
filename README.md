# Random Number and Simulation Utilities in C++

This repository contains a collection of C++ programs for generating random numbers, Gaussian distributions, and simulating random walks. It also includes implementations using **MIXMAX** and standard C++ random engines. These programs are useful for physics simulations, Monte Carlo methods, and numerical experiments.

---

## Contents

1. **`urandom.cpp`** – Generates seeds using `/dev/urandom` or process ID & time.
2. **`drandom` / `gaussran`** – Produces uniformly distributed and Gaussian-distributed random numbers.
3. **`test_mixmax.cpp`** – Uses the MIXMAX random number generator for uniform distributions.
4. **`test_gaussran.cpp`** – Generates Gaussian-distributed random numbers using MIXMAX and outputs a histogram.
5. **`test_ranlux.cpp`** – Uses the Ranlux random engine for uniform random numbers with seeding and state saving.
6. **`random_walk.cpp`** – Simulates 2D random walks for multiple walkers and records final displacements.

---

## Features

* **Multiple seeding methods:**

  * `/dev/urandom` (more randomness)
  * Process ID and current time

* **Random number generation:**

  * Uniform numbers (`drandom`)
  * Gaussian numbers (`gaussran`)

* **Monte Carlo utilities:**

  * Random walk simulations
  * Histograms for Gaussian-distributed numbers

* **State management:**

  * Save and restore RNG states (MIXMAX and Ranlux)

* **C++11 compatible:**

  * Uses `<random>` library, `<thread>` for delays, and standard C++11 features.

---

## Compilation

* **Simple programs:**

```bash
g++ urandom.cpp -o urandom
./urandom
```

* **MIXMAX-based programs:**

```bash
g++ -std=c++11 test_mixmax.cpp MIXMAX/mixmax.cpp -o mxmx
./mxmx
```

* **Gaussian histogram example:**

```bash
g++ -std=c++11 test_gaussran.cpp MIXMAX/mixmax.cpp -o gaussran
./gaussran
```

* **Ranlux example:**

```bash
g++ -std=c++11 test_ranlux.cpp -o ranlux
./ranlux
```

* **Random walk simulation:**

```bash
g++ -std=c++11 random_walk.cpp MIXMAX/mixmax.cpp -o walk
./walk
```

---

## Usage

* **Generate random numbers:**

```bash
./urandom
```

* **Generate Gaussian numbers and histogram:**

```bash
./gaussran 1000000
```

* **Run 2D random walks:**

```bash
./walk
```

Output files:

* `dataR` → squared displacements of walkers

* `data` → step-by-step coordinates

* **Seeding and reproducibility:**

  * RNGs can be seeded manually or via `/dev/urandom`.
  * States can be saved to and loaded from files.

---

## Dependencies

* C++11 or higher
* Standard libraries (`<iostream>`, `<fstream>`, `<random>`, `<cmath>`, `<thread>`)
* Optional: `MIXMAX` engine (`MIXMAX/mixmax.hpp` and `mixmax.cpp`)

---

## Notes

* The Gaussian generator uses the Box-Muller transform.
* Random walks use a uniform choice among 4 directions.
* Histograms are printed in text format, with normalized comparison to the Gaussian distribution.
