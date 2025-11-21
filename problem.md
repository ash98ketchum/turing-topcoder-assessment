# The Resonant Triad

**Time Limit:** 2.0 seconds
**Memory Limit:** 256 MB

## Description
You are the chief engineer of a starship equipped with $N$ antimatter containment cells. The $i$-th cell currently holds $a_i$ units of antimatter.

To safely initiate a hyperspace jump, the ship's computer requires a stable configuration where **exactly 2** cells are active (contain non-zero antimatter). All other $N-2$ cells must be completely empty (contain 0 units).

You can perform a **Resonant Transfer** operation between two distinct cells: a **Target** cell ($T$) and a **Source** cell ($S$). The laws of antimatter physics dictate the transfer rules:
1.  The **Target** cell must absorb an amount of antimatter exactly equal to what it currently holds. (If cell $T$ has $x$ units, it takes $x$ units from $S$ and becomes $2x$).
2.  The **Source** cell loses that amount. (If cell $S$ has $y$ units, it becomes $y-x$).
3.  This operation is valid only if the Source has sufficient antimatter ($y \ge x$).

Your task is to construct a sequence of operations that results in exactly 2 cells containing non-zero antimatter. If it is impossible, output `-1`.

You do not need to minimize the number of operations, but the total number of operations **for each test case** must not exceed 20,000.

## Input Format
- The first line contains an integer $t$ ($1 \le t \le 1000$) — the number of test cases.
- The description of each test case follows:
    - The first line of each test case contains an integer $N$ ($3 \le N \le 1000$).
    - The second line contains $N$ integers $a_1, a_2, \dots, a_N$ ($1 \le a_i \le 10^9$), the initial antimatter amounts.
- It is guaranteed that the sum of $N$ over all test cases does not exceed 5000.

## Output Format
For each test case:
- If a solution exists, print an integer $K$ ($0 \le K \le 20000$), the number of operations.
- Then print $K$ lines. Each line should contain two integers `target_idx` and `source_idx` (1-based indices), representing a transfer into `target` from `source`.
- If no solution exists (e.g., fewer than 2 non-zero cells initially), print `-1`.


## Examples

**Input**
```text
5
4
4 4 1 2
4
2 5 4 1
5
5 4 4 1 2
4
5 2 5 1
4
1 1 1 1
```

**Output**
```text
6
3 1
3 4
1 2
2 1
2 1
2 3
6
4 3
4 1
3 4
4 2
4 3
4 2
9
4 2
4 5
2 3
3 2
3 2
3 4
2 1
1 2
1 2
3
4 1
4 2
1 4
2
1 2
3 4
```