# Assignment 2 – Finite Functions and Metropolis Sampling

## Overview

This code investigates a set of “mystery data” files and attempts to identify the probability distribution from which the data was sampled. Some candidate distributions are compared by plotting them alongside the data. Once a suitable distribution is identified, the Metropolis algorithm is used to generate new pseudo-data sampled from that distribution.

The final output includes plots comparing functions, mystery data, and sampled data, as well as a new mystery-style data file written to disk.

---

## Compiling the Code

Ensure you are in the directory containing the `Makefile`, then run:

```bash
make
./TestFiniteFunctions ../../Data/MysteryDataXXXXX.txt