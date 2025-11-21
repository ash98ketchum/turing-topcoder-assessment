# Problem Idea: The Resonant Triad

## Initial Concept
I started with the idea of "Constructive Algorithms" involving state transformations. My initial thought was a simple flow problem: "Move items from box A to box B until box A is empty."

**Rejection:** This was too easy. Standard Greedy or Max-Flow algorithms would solve it instantly.

## The Twist: "Doubling" Interaction
I decided to restrict the movement rule to make it non-linear. Instead of moving any amount $X$, the receiver must absorb exactly its current amount ($V \to 2V$).

This creates a fascinating mathematical structure. If we have two numbers $A$ and $B$, can we empty one?
- If we perform the operation $A \to 2A$ using $B$ as the source, $B$ becomes $B - A$.
- This looks like the Euclidean GCD algorithm ($B \% A$), but we are limited to powers of 2.

## The "AI Trap"
The core difficulty is that to reduce $B$ modulo $A$ using binary subtraction, you sometimes need to double $A$ *without* subtracting from $B$ (when the current bit of the quotient is 0).
This requires a **Third Helper Node** ($C$).

AI models (like Qwen) usually try to solve this with:
1.  **BFS:** Fails because the numbers grow exponentially ($2^k$), exploding the state space.
2.  **Greedy:** Fails because locally optimal moves (always subtracting from the largest) don't work for specific binary patterns.
3.  **Two-pointer:** Fails because they ignore the necessity of the 3rd helper node.

## Final Formulation
- **Input:** $N$ integers.
- **Goal:** Reduce $N-2$ of them to exactly 0.
- **Invariant:** We need 3 numbers to guarantee a reduction step. If we have 3 non-zero numbers $A, B, C$, we can always make one of them smaller.
- **Difficulty:** Div2 C / Div1 A level.