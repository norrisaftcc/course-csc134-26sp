# Project 4: AI-Assisted Development

**CSC 134 — Weeks 13–15 | Due: End of Week 15**

You've spent twelve weeks learning to think like a programmer. Now you'll learn to think like a *lead developer* — someone who directs the work, makes design calls, and uses every tool available to ship something real.

This project is built with AI. Not by AI. You drive.

---

## Pick Your Track

All three tracks earn the same grade. Choose based on what you want to build, not what seems easiest.

**Track A — C++ Program**
Build a terminal application in C++. Use everything you've learned: functions, arrays/vectors, file I/O, classes. This is the most direct continuation of the course.

**Track B — C++ to Visual**
Start in C++, then port your core logic into an HTML/JS application. Your C++ version serves as the prototype; the visual version is the deliverable. Good for students who want to see their work come alive in a browser.

**Track C — Direct to Visual (HTML/JS)**
Design and plan in structured English and pseudocode, then build directly in HTML/JS with AI assistance. The planning documents carry the same weight as code — you must demonstrate the same structured thinking a C++ solution would require.

> **Why allow non-C++ tracks?** The hardest part of programming isn't syntax. It's decomposing a problem, managing state, and making design decisions. A student who produces a clear design document, iterates thoughtfully with AI, and ships a working product has demonstrated those skills — regardless of language.

---

## What to Build

Your project must be an interactive program with meaningful state. That means the program tracks, modifies, and responds to data as the user interacts with it.

**Scope guidance:** Think "one feature done well" over "five features done halfway." A polished inventory tracker beats a sprawling RPG that crashes.

### Idea Starters

These are seeds, not prescriptions. Combine them. Twist them. Bring your own.

- Dungeon crawler with room/item state
- Budget tracker with categories and file persistence
- Quiz engine that loads questions from a file and tracks scores
- Narrative game with branching paths and an inventory system
- Fitness log with history, averages, and goals
- Recipe manager with search, scaling, and favorites

---

## Grade Tiers

### C Tier (70%) — It Works

- Interactive: takes input, produces output based on state
- Minimum 3 functions (Track A) or 3 distinct components/sections (Tracks B/C)
- Basic input validation — doesn't crash on bad input
- State tracking: at least 2 variables that change during use
- Design document completed before coding began
- AI interaction log submitted

### B Tier (85%) — It's Solid

Everything in C, plus:

- 5+ functions or components
- File I/O (Track A) or localStorage/equivalent persistence (Tracks B/C)
- Menu or navigation system
- Comprehensive input validation
- At least one data structure used meaningfully (array, vector, object)
- Evidence of iteration: log shows you revised AI output, not just accepted it

### A Tier (95%) — It's Polished

Everything in B, plus:

- Clean separation of concerns (display logic vs. data logic vs. file logic)
- Meaningful use of classes/objects (Track A) or modular code organization (Tracks B/C)
- Edge cases handled — difficult to break
- Visual polish: consistent formatting, clear interface, good UX
- Design document shows evolution from initial plan to final product
- AI log demonstrates at least one instance where you rejected AI output and explains why

### Badge Track (Additional)

All of A tier, plus the capstone deliverables defined in the badge requirements: requirements analysis, OO design documentation, test plan, and portfolio-ready reflection.

---

## Track-Specific Notes

### Track A: C++

- Compile with `g++ -std=c++17 -Wall -Wextra` — clean build, no warnings
- Follow course conventions: prototypes at top, main in middle, definitions at bottom
- Use `const` by default. Prefer STL algorithms over raw loops where they fit.
- Vectors are available (Week 13+). Use them instead of raw arrays for dynamic data.
- If you use ncurses or terminal graphics, document your build command.

### Track B: C++ → Visual

- Your C++ prototype doesn't need to be pretty. It proves your logic works.
- The port doesn't need to replicate every feature — focus on the core interaction.
- Document what changed in the port and why. This is valuable learning.
- Your design doc should note which parts of C++ translated cleanly and which didn't.

### Track C: Direct to Visual

- Your design document carries extra weight. It must show the same rigor a C++ student puts into code structure: function decomposition, state management plan, data flow.
- HTML/JS projects should be single-file or minimal-file. No frameworks beyond what you can explain.
- If you use a library (p5.js, Chart.js, etc.), you must explain in your log why you chose it and what it does.

---

## Rubric

| Component | Weight | What We're Looking For |
|---|---|---|
| **Design & Planning** | 25% | Did you think before you typed? Does the design doc show structure, not just a wishlist? |
| **Working Product** | 30% | Does it run? Does it do what you said it would? Is the core interaction solid? |
| **Code Quality** | 20% | Readable, organized, follows conventions. Comments explain *why*, not *what*. |
| **AI Collaboration** | 15% | Log shows a real working relationship: directing, iterating, questioning, learning. |
| **Testing & Polish** | 10% | Validated inputs, handled edge cases, consistent interface. |

---

## Submission Checklist

Submit all files to your GitHub repository by the Week 15 deadline.

```
project4/
├── design_doc.md          ← Completed BEFORE coding (we can see git timestamps)
├── src/                   ← Your source code (organized however fits your track)
├── ai_log.md              ← AI interaction log (use the provided template)
├── testing_log.md         ← Test cases, results, bugs found and fixed
└── README.md              ← What you built, which track, how to run it
```

**README.md must include:**
- Project title and one-sentence description
- Which track (A, B, or C)
- How to compile/run (exact commands)
- One paragraph: what you're most proud of, and what you'd improve with more time

**Late policy:** Same as all projects. On time = full credit available. Each day late caps 10% lower.

---

## Timeline

| Week | Milestone | What's Due |
|---|---|---|
| 13 | **Design week.** Complete your design document. Get instructor approval on scope. | `design_doc.md` draft pushed to repo |
| 14 | **Build week.** Iterate with AI. Test as you go. | Progress check: working prototype |
| 15 | **Polish week.** Fix bugs, improve UX, complete documentation. | Everything in the checklist above |

---

## One Last Thing

The earlier projects taught you to write code. This one teaches you to *direct* code. That's a different and harder skill. You'll need to:

- Explain what you want clearly enough for an AI to help
- Recognize when AI output is wrong, wasteful, or off-track
- Make decisions the AI can't make for you: scope, priorities, tradeoffs

The design document is where that thinking lives. Start there.
