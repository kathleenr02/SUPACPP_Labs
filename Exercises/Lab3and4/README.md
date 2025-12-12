# Assignment 2 – Finite Functions and Metropolis Sampling
Kathleen Ramage

## Overview

This code investigates a set of “mystery data” files and attempts to identify the probability distribution from which the data was sampled. Some candidate distributions are compared by plotting them alongside the data. Once a suitable distribution is identified, the Metropolis algorithm is used to generate new pseudo-data sampled from that distribution.

The final output includes plots comparing functions, mystery data, and sampled data, as well as a new mystery sampled data file written to data.

---

## Compiling the Code

Ensure you are in the directory containing the `Makefile`, then run:

```bash
make
./TestFiniteFunctions ../../Data/MysteryDataXXXXX.txt

```
## What the Program Does

- Reads mystery data from a text file  
- Plots candidate distributions including:
  - Default function  
  - Normal (Gaussian) distribution  
  - Cauchy–Lorentz distribution  
  - Crystal Ball distribution  
- Manually identifies the best-matching distribution  
- Uses the Metropolis algorithm to sample from the chosen distribution  
- Saves the sampled data to disk  

---

## Output

The sampled points are written to a new file in:

```text
./Outputs/data/
