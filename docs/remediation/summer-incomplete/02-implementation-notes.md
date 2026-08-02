# Implementation Notes — M5, M6, M7, Final

How to build the remaining modules in the same LPAA shape as M4. Each section
lists the learning targets, the four pieces (Learn / Practice / Apply /
Assess), and the rubric weights. Authoring time per module: ~1–2 hours for the
instructor, since M4 is the template.

---

## Module 5 — Functions (~2 h student work)

**Why it's here:** functions are the single most-used tool in the course past
M3. Without them, M6 and M7 don't make sense.

### Learning targets

1. Write a function prototype, definition, and call.
2. Pass parameters by value and use a return value.
3. Decompose a 30-line `main()` into 3–4 named functions.

### Learn

- Reading: prototype vs. definition vs. call; parameters as named slots; what
  `return` actually does (hands the value back to the caller). Half a page,
  no more.
- Worked example: take `m5hw_sample.cpp` already in the repo and walk through
  how `question1()` / `question2()` are *prototyped at the top, called from
  `main`, defined at the bottom*. That three-part shape is the whole topic.
- Cut the "split your code into a separate `.h` file" content from the
  original M5. It's worth doing eventually but not in the time budget.
  Header-file separation belongs in a follow-up course.

### Practice (drills with answer keys)

1. `int square(int x)` — returns `x * x`. Call it from `main` for 1..5 and
   print the results in a loop.
2. `void greet(string name)` — prints `Hello, <name>!`. Call it three times
   with three different names.
3. `bool isEven(int n)` — returns `true` if `n` is even. Use it inside a
   loop to count how many of the integers 1..20 are even.

### Apply — Lab

**Temperature converter library.** Write three functions:

- `double cToF(double c)` — Celsius to Fahrenheit
- `double fToC(double f)` — Fahrenheit to Celsius
- `void printConversionTable(double start, double end, double step)` — uses
  the two functions above and a `for` loop to print a side-by-side table.

`main()` should be ≤ 10 lines: prompt for `start`, `end`, `step`, then call
`printConversionTable`. The lab is a check that they can build a tiny
function-based design, not just call one-offs.

### Assess — Test

Write `double average(int a, int b, int c)` and use it from `main()` to
average three numbers the user enters. Plus reflection.

### Rubric weights (out of 10)

- Prototypes declared correctly: 2
- Each function compiles and returns the right type: 3
- `main()` is short and delegates: 2
- Code compiles, no warnings, readable names: 2
- Reflection: 1

### Check-in question

"Why did we declare the prototype at the top of the file? What breaks if you
remove it?" (Answer should mention: the compiler reads top-to-bottom and
needs to know the function exists before it sees the call.)

---

## Module 6 — Arrays & `vector<>` (~1.5 h student work)

**Why it's here:** every real program holds collections of values. We do
both `array` and `vector` briefly, then **lean on `vector`** for everything
after, because it's safer (knows its own size, grows) and matches what M7
will need.

### Learning targets

1. Declare and initialize a fixed-size array and a `vector<int>`.
2. Read/write elements by index, including the off-by-one risk.
3. Loop over a `vector` to compute a sum, average, or max.

### Learn

- Reading: arrays vs. vectors in one paragraph each. The pitch for vectors:
  `.push_back()`, `.size()`, no separate length variable to keep in sync.
- Skip: PPM / image generation from the original M6. Cool but not a
  fundamental. Cut.
- Skip: multi-dimensional arrays. Mentioned only — "this exists, you'd use it
  for grids; we did the same thing with nested loops in M4."

### Practice

1. Declare `vector<int> nums = {4, 8, 15, 16, 23, 42};` Print each with a
   `for` loop indexed by `i < nums.size()`.
2. Ask the user for 5 ints, store them in a `vector` using `push_back`, then
   print them in reverse order.
3. Given a vector of 10 ints, find and print the largest.

### Apply — Lab

**Grade book.** Read scores from the user until they enter `-1`. Store each
in a `vector<double>`. Then print:

- the count of scores entered,
- the average,
- the highest and lowest.

This is the canonical "loop + collection + a couple of accumulators" exercise.

### Assess — Test

Read 5 integers into a `vector<int>`. Print only the ones that are above the
average. Plus reflection.

### Rubric weights (out of 10)

- Vector declared and populated correctly: 2
- Loop iterates over the whole vector without crashing on size: 3
- Required computation correct (average, filter, etc.): 3
- Compiles, readable: 1
- Reflection: 1

### Check-in question

"If your vector has 6 elements and you write a `for` loop with `i <= nums.size()`,
what happens?" (Out-of-bounds read on the last iteration; undefined behavior.)

---

## Module 7 — Classes (~1.5 h student work)

**Why it's here:** the student should be able to read and write a small class
before leaving the course. We don't go past constructors + getters/setters +
one method. That's enough.

### Learning targets

1. Declare a class with private data and public methods.
2. Write a constructor and use it to create an object.
3. Call methods on an object.

### Learn

- Reading: "a class bundles data and the operations on that data." Concrete
  example, no philosophy.
- Worked example: `m7t1.cpp` in the repo (the `Restaurant` class) is already
  the right size. Strip out the emoji-star display and use a plain
  `cout << name << ": " << rating << "/5"` version so the student isn't
  distracted by string formatting. Keep `getName`, `getRating`, `display`.
- Skip: inheritance, friend functions, operator overloading, `static`,
  destructors. All out of scope for the time budget.

### Practice

1. Given a `Restaurant` class (instructor provides the `.h`/source), create
   two `Restaurant` objects in `main()` and call `display()` on each.
2. Add a `setRating(double r)` method that refuses to accept values outside
   0.0–5.0 (prints a warning and leaves the rating unchanged).
3. Add a `int reviewCount` field with a getter, setter, and an
   `addReview(double newRating)` method that updates the running average.

### Apply — Lab

**Book class.** Write a `Book` class with:

- private: `string title`, `string author`, `int pages`,
- a constructor that takes all three,
- getters for each field,
- a `void describe()` method that prints `"<title> by <author> (<pages> pages)"`.

In `main()`, create three `Book` objects in a `vector<Book>` and loop over
them, calling `describe()` on each. (This is the pay-off: M6 + M7 together.)

### Assess — Test

Write a `Rectangle` class with `width` and `height` (private doubles), a
constructor, getters, and a method `double area()`. Create one from user
input and print its area. Plus reflection.

### Rubric weights (out of 10)

- `private` fields declared correctly: 2
- Constructor sets fields: 2
- At least one method works correctly: 3
- Object created and used from `main()`: 2
- Compiles, readable, reflection: 1

### Check-in question

"Why are the fields `private`? What goes wrong if you make them `public`?"
(Anything outside the class can change them to anything, bypassing the
class's invariants — like the rating-range check in the practice.)

---

## Final Synthesis (~1 h student work, replaces M8 project)

A single small program that exercises one feature from each module. Far
smaller than the original Project 4 — the goal is "prove you can combine
these four ideas," not "ship a product."

### Spec

Build a **score tracker** for any activity the student picks (game scores,
workout reps, quiz grades, whatever — the topic doesn't matter).

Required pieces, one per module:

- **M4 (loops):** the program loops in `main()`, repeatedly asking the user
  what they want to do (add a score, show all, show stats, quit). Use a
  `while` loop that exits when they pick "quit."
- **M5 (functions):** at least three named functions besides `main`, e.g.
  `addScore`, `showAll`, `showStats`.
- **M6 (vector):** scores stored in a `vector<double>` (or `vector<Score>`
  if they want to combine with M7).
- **M7 (class):** one small class. Either `Score { double value; string label; }`
  or a `Tracker` class that wraps the vector. One is enough.

### Rubric (out of 20)

- Uses `while` loop as the menu driver: 3
- Has ≥ 3 functions besides `main`: 4
- Uses `vector<>` to hold the data: 4
- Defines and uses one class with at least one method: 4
- Compiles, no warnings, no crashes on bad input: 3
- Reflection (`final_reflection_lastname.txt`, 1 paragraph: which module
  was hardest, which felt most useful): 2

**Passing = 14/20.** No retake — the four module tests are the safety net.

### Final check-in (~15 min)

The student runs the program in front of the instructor and walks through
the code. Two open questions:

1. "If I wanted to save these scores between runs of the program, what would
   need to change?" (Looking for: file I/O — they haven't learned it, but
   should be able to articulate that the vector is in memory and disappears.)
2. "Which of these four modules do you think you'd reach for first in a real
   project, and why?" (No wrong answer; this is checking that they have an
   intuitive grasp.)

---

## Cross-cutting implementation notes

### File naming

Every submitted file: `m{N}_{kind}_lastname.cpp`. Keeping the same shape
across modules removes the mental tax of "where does this go."

### Compiler / environment

Stick with whatever the original course used (looks like g++ via the
`.vscode/tasks.json`). Don't introduce CMake or a new IDE during
remediation — it's pure friction. If the student is on Windows and stuck,
the `projects/terminal_codespaces_win.md` file in the repo is the fallback.

### How to handle the M1–M3 diagnostic (if needed)

If there's doubt the student retained M1–M3, give a single 30-min diagnostic
**before M4 starts**:

- Prompt the user for two ints, print their sum, difference, product, and
  integer quotient.
- Then ask which is larger, using `if`/`else`.

If they can do this in 30 minutes unaided, M1–M3 is fine. If not, spend an
extra hour walking through `m3t1_lastname.c++` and the simple `if`/`else`
examples in `m3` before starting M4.

### What to do if the student stalls mid-summer

The original incomplete happened because work fell off. If it happens again:

- Drop M7 entirely. M4 + M5 + M6 + a smaller final is a defensible minimum
  for the credit.
- Don't drop M5. Functions are the load-bearing concept.
- Convert the final to a takehome M6 lab extension (`gradebook` with a few
  more features) rather than the full synthesis program.

### What this plan deliberately doesn't include

- No game-jam, no CYOA story, no AI-collaboration write-ups.
- No design documents or pseudocode-only tracks. C++ only.
- No peer interaction (it's an async incomplete; everyone else has moved on).
- No "stretch goals" or bonus points. Either the work is done or it isn't.

The principle throughout: **every minute the student spends should be on
learning, practicing, applying, or being assessed on a fundamental.** If a
piece of content doesn't fit one of those four, it's cut.
