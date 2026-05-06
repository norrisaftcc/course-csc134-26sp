# AI Collaboration Guide — Project 4

You've used AI as a tutor. Now you'll use it as a junior developer who works fast but needs direction. The quality of what you get depends on the quality of what you ask.

---

## The Short Version

1. Start with your design document, not with AI.
2. Give AI context before giving it tasks.
3. Ask for one thing at a time.
4. Read every line of output. If you can't explain it, don't use it.
5. When AI gives you something wrong, say what's wrong and why.

---

## Feeding AI Your Design Document

Your design doc is your most powerful prompt. Before asking AI to write code, paste in the relevant section. Compare these two approaches:

**Weak prompt:**
> "Write me a save function for my game."

**Strong prompt:**
> "Here's my state inventory: [paste section 2]. I need a function that writes these values to a pipe-delimited text file called `save.txt`. One line per record. The function should take the arrays as parameters and return true if the write succeeds. I'm using C++17 with fstream."

The second prompt works because AI now knows your data, your format, your constraints, and your language. It can't invent those — you have to supply them.

---

## Prompt Patterns That Work

### The Scaffold Ask
Ask AI to set up structure, then fill in the logic yourself.

> "Give me the function signatures and empty bodies for these five functions: [list from your function map]. Don't write the implementations — just the prototypes, the empty definitions with TODO comments, and a main() that calls them in order."

This gets you a compilable skeleton fast. You write the guts.

### The Explain-Then-Generate Ask
Make AI prove it understands before it writes.

> "I need to parse a pipe-delimited string like `sword|25|3` into separate variables. First, explain how `find()` and `substr()` work together to split on a delimiter. Then show me a function that does it."

If the explanation is wrong, the code will be too. Catch it early.

### The Refactor Ask
Hand AI your working-but-messy code and ask for a specific improvement.

> "This function works but it's 60 lines long and has three levels of nesting. Refactor it into smaller functions. Keep the same behavior — don't add features."

### The Debug Ask
Give AI the code, the expected behavior, the actual behavior, and the input that triggers the bug.

> "This function should return the index of the item with the highest value. When I pass in `{10, 25, 5, 30}` it returns 1 instead of 3. Here's the code: [paste]. What's wrong?"

Four pieces of information. AI can't debug with less.

### The Review Ask
Ask AI to criticize your code, not compliment it.

> "Review this function for problems. Focus on: edge cases I haven't handled, input validation I'm missing, and anything that violates the single-responsibility principle. Don't rewrite it — just list the issues."

---

## When AI Goes Wrong

It will. Expect these failure modes:

**Over-engineering.** You ask for a simple menu and get a class hierarchy with an abstract base. Fix: restate your scope. "I need a function with a do-while loop, not a class."

**Wrong assumptions.** AI guesses your data format, naming conventions, or project structure. Fix: paste the relevant part of your design doc.

**Plausible nonsense.** The code compiles and looks right but doesn't do what you need. Fix: test it with known inputs before trusting it.

**Ignoring constraints.** You said C++17 but AI used features from C++20. You said no vectors but AI used one. Fix: restate the constraint and ask it to rewrite.

**Drift.** After several back-and-forth messages, AI forgets your original requirements. Fix: re-paste the relevant design doc section. Start a new conversation if it's badly lost.

---

## Staying the Driver

Three questions to ask yourself after every AI interaction:

1. **Can I explain every line?** If not, ask AI to explain it. If the explanation doesn't make sense, don't use the code.
2. **Did I make the design decision, or did AI?** You choose the data structures, the function boundaries, the user flow. AI fills in syntax.
3. **Could I modify this without AI's help?** If you needed to change the delimiter from `|` to `,`, could you do it? If not, you don't understand the code well enough.

---

## What Counts as Good AI Use

| Good | Not Good |
|---|---|
| "Explain how fstream handles file-not-found" | "Write my project" |
| Pasting your design doc as context | Pasting only "make a game" |
| Asking AI to refactor your working code | Asking AI to write it from scratch with no plan |
| Rejecting AI output that doesn't fit | Accepting everything and hoping it works |
| Asking for one function at a time | Asking for the whole program at once |
| Testing AI output before moving on | Stacking untested AI code |

---

## A Workflow That Works

1. Open your design document alongside your code editor.
2. Pick the next function from your function map.
3. Try it yourself for 10–15 minutes.
4. If stuck, write a specific prompt with context from your design doc.
5. Read the AI output. Test it. Modify it if needed.
6. Log the interaction: what you asked, what you got, what you changed.
7. Move to the next function.

This loop — plan, attempt, prompt, test, log — is the core workflow. Each cycle should take 15–30 minutes. If a single function takes longer than an hour, your scope may be too large or your decomposition too coarse. Revisit your function map.
