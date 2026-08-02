# Module 4 — Loops (Full Sample Module)

This is the template every other module follows. It's deliberately complete so
M5–M7 can be built by copying the shape, not redesigning the pedagogy.

**Time budget:** ~2 hours of student work.
**Prereqs:** M1–M3 (variables, I/O, `if`/`else`).
**Learning targets — by the end the student can:**

1. Write a `while` loop with a correct termination condition.
2. Write a `for` loop with init / condition / update.
3. Choose between `while` and `for` based on whether the count is known ahead of time.
4. Write a nested loop and explain what the inner vs. outer loop controls.

---

## Part 1 — Learn (~20 min)

### Reading (one page, then move on)

A loop runs a block of code repeatedly. You stop when a condition becomes
false. There are two everyday loop shapes in C++:

**`while` — use when you don't know in advance how many times to loop.**

```cpp
int guess = 0;
while (guess != 7) {
    cout << "Pick a number: ";
    cin >> guess;
}
cout << "Got it." << endl;
```

The condition `guess != 7` is checked **before** each pass. As soon as it's
false, the loop exits.

**`for` — use when you do know how many times to loop (counted iteration).**

```cpp
for (int i = 0; i < 5; i++) {
    cout << i << " ";
}
// prints: 0 1 2 3 4
```

The three parts are: **init** (`int i = 0`), **condition** (`i < 5`), and
**update** (`i++`). They run in that order on the first pass; after that, it's
condition → body → update → condition → ...

**Nested loops — a loop inside a loop.** The inner loop runs to completion on
every single pass of the outer loop. This is how you produce rows-and-columns
output:

```cpp
for (int row = 0; row < 3; row++) {       // outer: 3 rows
    for (int col = 0; col < 4; col++) {   // inner: 4 cols
        cout << "* ";
    }
    cout << endl;
}
```

That prints a 3×4 grid of stars. The outer loop steps once per *row*; the
inner loop draws the four stars *within* that row.

### Worked example (read it, then type it yourself once)

The file `m4t1_example.c++` already in the repo is the canonical example.
Open it. Lines 11–14 are a `while` countdown; lines 17–19 are a `for` count-up;
lines 24–35 use a `while` to build a squares table. Read it line-by-line.
Then close it and re-type it from scratch. Don't copy-paste — typing it is the
practice.

### The three mistakes that cause 90% of loop bugs

1. **Off-by-one:** `i <= n` when you meant `i < n` (or vice versa). Decide
   "do I want to include `n` or stop just before it?" before you type the
   condition.
2. **Forgotten update:** writing `while (i < 10)` and never incrementing `i`
   inside the loop body. Result: infinite loop. If your program hangs, this is
   almost always why.
3. **Confusing inner and outer:** in a nested loop, the `endl` to start a new
   row belongs *outside* the inner loop, *inside* the outer one.

---

## Part 2 — Practice (~30 min)

Three drills. After each one, check against the answer key. If you got it
wrong, retype the correct version from scratch — don't just stare at it.

### Drill 1: Count down

Write a program that prints `10 9 8 7 6 5 4 3 2 1 blastoff!` on one line,
using a `while` loop.

**Answer key:**

```cpp
#include <iostream>
using namespace std;

int main() {
    int n = 10;
    while (n >= 1) {
        cout << n << " ";
        n--;
    }
    cout << "blastoff!" << endl;
    return 0;
}
```

### Drill 2: Sum 1 to N

Ask the user for a positive integer `N`. Use a `for` loop to compute
`1 + 2 + ... + N` and print the total.

**Answer key:**

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter N: ";
    cin >> n;

    int total = 0;
    for (int i = 1; i <= n; i++) {
        total += i;
    }
    cout << "Sum 1.." << n << " = " << total << endl;
    return 0;
}
```

**Self-check:** if the user enters 10, the answer is 55. If you got 45, your
loop is off-by-one — you're stopping at `i < n` instead of `i <= n`.

### Drill 3: Multiplication row

Ask the user for a number `x` between 1 and 12. Print its first 10 multiples
on one line, separated by tabs:
`x  2x  3x  ...  10x`.

**Answer key:**

```cpp
#include <iostream>
using namespace std;

int main() {
    int x;
    cout << "Enter x (1-12): ";
    cin >> x;

    for (int i = 1; i <= 10; i++) {
        cout << (x * i) << "\t";
    }
    cout << endl;
    return 0;
}
```

> Submit the three drills as a single file `m4_practice_lastname.cpp` with
> all three in `main()`, separated by a `cout` header for each
> (`"--- Drill 1 ---"`, etc.).

---

## Part 3 — Apply (~45 min)

### Lab: Multiplication table

Write **one program** that prints a multiplication table from 1 to `N`,
where the user picks `N` (cap at 12 so the output stays readable).

**Required output for `N = 5`:**

```
    1   2   3   4   5
1   1   2   3   4   5
2   2   4   6   8  10
3   3   6   9  12  15
4   4   8  12  16  20
5   5  10  15  20  25
```

Don't fuss over perfect column alignment — using `\t` between numbers is fine.

**You must use:**

- a `for` loop to print the header row,
- a nested `for` loop for the body of the table,
- one constant or variable for `N` so changing it changes the whole table.

**Submit as** `m4_lab_lastname.cpp`.

### Rubric (out of 10)

| Criterion | Pts |
| --------- | --- |
| Compiles cleanly with no warnings | 2 |
| Prompts for `N` and validates it's between 1 and 12 | 2 |
| Header row prints correctly via a `for` loop | 1 |
| Body printed via a nested loop, correct values | 3 |
| Code is readable: meaningful names, indented, no dead code | 2 |

---

## Part 4 — Assess (~30 min)

### Test problem (30 min, closed-book on syntax, open IDE)

Write a program that asks the user for two positive integers, `rows` and
`cols`. Print a rectangle of `#` characters with that many rows and columns,
using a nested loop. Then on the next line print the *area* (`rows * cols`).

**Example run:** for `rows = 3`, `cols = 5`:

```
#####
#####
#####
Area: 15
```

Submit as `m4_test_lastname.cpp`. Then write a 3–5 sentence reflection in
`m4_reflection_lastname.txt`:

- What was hardest in this module?
- What clicked?
- Which of the "three common loop mistakes" did you actually make at least once?

### Grading

| Element | Pts |
| ------- | --- |
| Reads `rows` and `cols` from input | 2 |
| Nested loop produces correct rectangle | 4 |
| Area printed correctly | 2 |
| Code compiles, no warnings | 1 |
| Reflection submitted, addresses all three prompts | 1 |

**Passing = 7/10.** One retake permitted with a different problem from the
bank (see Implementation Notes).

### Instructor check-in (5 min, after the test)

Schedule a brief video or recorded walkthrough. The student answers:

1. "Walk me through your nested loop — which loop draws a row, and which
   one draws the characters within it?"
2. "What would you change to print a hollow rectangle (`#` on the border,
   space in the middle)?" (They don't have to implement it, just describe it.)

This is the cheating-prevention checkpoint. If the student can't explain
their own code, the module isn't passed regardless of the test score.

---

## Bank of alternate test problems (for retakes)

Each of these is roughly the same difficulty as the rectangle problem.

1. **Triangle:** print a right triangle of `*` with height `h` (row `i` has
   `i` stars).
2. **Even sum:** ask for `N`, print the sum of even numbers from 2 to `N`.
3. **Reverse countdown table:** ask for `N`, print `N, N-1, ..., 1` then on
   the next line print each number's square in the same order.
4. **Checkerboard:** given `rows` and `cols`, print a board alternating
   `#` and `.` (nested loop + parity check).
