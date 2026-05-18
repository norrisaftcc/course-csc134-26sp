# Summer Remediation Outline — CSC 134 Incomplete

**Audience:** Asynchronous student finishing an incomplete over summer. Work fell
off around Module 4. Skipping all CYOA / game / roleplay framing — the goal is
a no-nonsense pass through the fundamentals using **Learn → Practice → Apply →
Assess (LPAA)** in every module.

**Time budget:** ~5% of a full-semester time commitment. Plan targets **~7–8
hours of student work**, plus instructor check-ins.

---

## What's in scope

| Module | Topic                  | Why it matters                                                 |
| ------ | ---------------------- | -------------------------------------------------------------- |
| M4     | Loops (`while`, `for`, nested) | The pivot point where the student stalled. Rebuild here.       |
| M5     | Functions (prototypes, params, return values, headers) | Decomposition — every later topic depends on this. |
| M6     | Arrays & `vector<>`    | First taste of collections; needed for any real program.       |
| M7     | Classes (data + methods, constructors) | Minimum OO viable. Enough to read and write a small class. |

**Explicitly out of scope** (cut to stay inside the time budget):

- Module 8 capstone project (replaced by a single short synthesis lab — see M7).
- CYOA / dungeon / game-jam framing from the original M3 and M5 labs.
- AI-collaboration / interaction-log assignments from the M8 brief.
- PPM image generation from M6 (cute, but not a fundamental).

**Prerequisite assumed (M1–M3 already done):** `cin`/`cout`, variables, types,
arithmetic, `if`/`else`, `switch`. If the M3 test was passed, no review is
needed. If not, a 30-minute diagnostic precedes M4 (see Implementation Notes).

---

## The LPAA shape (every module looks like this)

1. **Learn** — one short reading + one annotated worked example (≤ 20 min read).
2. **Practice** — 2–3 small drills with answer keys. Low stakes. Goal: muscle
   memory on the syntax.
3. **Apply** — one lab combining the concepts into a useful program (≤ 60 lines).
4. **Assess** — a short timed test (1 problem, ~30 min) + a 5-minute
   instructor check-in (video call or recorded walkthrough of the lab).

No roleplay, no narrative wrappers, no optional bonuses. If a piece doesn't
fit LPAA, it's cut.

---

## Per-module time budget

| Module | Learn | Practice | Apply | Assess | Total |
| ------ | ----- | -------- | ----- | ------ | ----- |
| M4 Loops    | 20 min | 30 min | 45 min | 30 min | **~2.0 h** |
| M5 Functions | 20 min | 30 min | 45 min | 30 min | **~2.0 h** |
| M6 Arrays/vector | 20 min | 20 min | 30 min | 20 min | **~1.5 h** |
| M7 Classes  | 25 min | 20 min | 30 min | 20 min | **~1.5 h** |
| Final synthesis (replaces M8) | — | — | 45 min | 15 min | **~1.0 h** |

**Total student time: ~8.0 hours.** Instructor time: ~1 hour total for
check-ins (15 min per module + final).

---

## Deliverables the student turns in

For each module, exactly four files in a `m{N}/` folder, named after them:

```
m4/m4_practice_lastname.cpp
m4/m4_lab_lastname.cpp
m4/m4_test_lastname.cpp
m4/m4_reflection_lastname.txt   # 3–5 sentences: what was hard, what clicked
```

Plus one synthesis program at the end: `final/final_lastname.cpp`.

---

## Pass criteria (what "complete" means)

To clear the incomplete, the student must:

1. Submit all four files for **each of M4, M5, M6, M7**.
2. Score ≥ 70% on each module test (re-attempt allowed once, with a different
   problem from the bank).
3. Submit a working final synthesis program that uses at least one feature from
   each of M4–M7 (loop, function, vector, class).
4. Complete the four instructor check-ins (one per module). A check-in is
   ~5 minutes: the student reads their own code aloud and answers two
   "why did you do it this way?" questions. This is the cheating-prevention
   mechanism and the only synchronous touchpoint.

Grade conversion follows the original syllabus (the incomplete becomes a
letter grade based on the average of the four module tests and the final).

---

## Suggested calendar (4 weeks, async)

| Week | Student does | Instructor does |
| ---- | ------------ | --------------- |
| 1 | M4 Loops (learn → assess) | M4 check-in, return grade |
| 2 | M5 Functions | M5 check-in, return grade |
| 3 | M6 Arrays + M7 Classes (lighter modules paired) | M6 + M7 check-ins |
| 4 | Final synthesis | Final check-in, post grade |

The student can compress this to 2 weeks if they want — the calendar is the
ceiling, not the floor.

---

## Three-part deliverable for this remediation package

1. **This outline** — `00-outline.md` (you are here).
2. **One fully-built sample module** — `01-module4-sample.md` (M4 Loops, every
   piece written out: reading, drills with keys, lab spec, test, rubric).
3. **Implementation notes for the rest** — `02-implementation-notes.md`
   (specifies what M5, M6, M7, and the final need, so they can be built in the
   same shape without re-deciding pedagogy each time).
