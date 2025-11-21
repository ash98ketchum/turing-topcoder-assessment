# Solution: The Resonant Triad

## Problem Analysis
We are given $N$ numbers. The goal is to perform operations until exactly 2 numbers are non-zero.
The operation is defined as:
* Select a Target $T$ and a Source $S$.
* Require $S \ge T$.
* $T \leftarrow 2 \cdot T$
* $S \leftarrow S - T$

This operation preserves the sum of the sequence but changes the distribution.

## The 3-Cell Strategy
The problem is trivial if we can find a way to reliably reduce one number to 0 using others.
Consider three non-zero numbers $A, B, C$ such that $0 < A \le B \le C$.
We can always reduce $B$ (the middle number) effectively modulo $A$ using a specific bitwise strategy.

Let $q = \lfloor B / A \rfloor$.
We can decompose $q$ into its binary representation:
$$q = \sum_{k=0}^{m} b_k 2^k$$

We iterate through the bits of $q$ from $k=0$ to $m$:
1.  **If the $k$-th bit is 1:** We use $B$ as the source.
    * $B$ loses $A \cdot 2^k$.
    * $A$ doubles to $A \cdot 2^{k+1}$.
2.  **If the $k$-th bit is 0:** We cannot use $B$ (as we don't want to subtract for this power of 2). However, $A$ must still double to prepare for the next bit. We use $C$ (the largest number) as the source.
    * $C$ loses $A \cdot 2^k$.
    * $A$ doubles to $A \cdot 2^{k+1}$.

Since $C \ge B \ge A$, $C$ will always have enough value to act as this "helper" buffer.
At the end of this process, $B$ is reduced to $B \pmod A$. Since this is strictly smaller than the original $B$ (and often 0), this is a valid Euclidean descent.

## Algorithm
1.  Collect all non-zero numbers.
2.  If count $\le 1$, output -1 (impossible to reach exactly 2).
3.  While count $> 2$:
    * Select the 3 smallest non-zero numbers.
    * Sort them so $A \le B \le C$.
    * Apply the bitwise reduction logic to reduce $B$ against $A$.
    * One number will eventually become 0. Remove it from the active set.
4.  Output the sequence of moves.

## Complexity
Each reduction step behaves like the Euclidean algorithm, which is logarithmic with respect to the values.
Given constraints $N \le 1000$ and values up to $10^9$, the total operations are well within the limit of 20,000.
Time Complexity: $O(N \cdot \log(\max A_i))$.
Space Complexity: $O(1)$ auxiliary space (excluding input storage).