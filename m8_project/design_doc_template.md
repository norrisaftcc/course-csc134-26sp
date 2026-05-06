# Design Document Template — Project 4

**Name:**  
**Track:** A / B / C  
**Project Title:**  
**One-sentence pitch:** What does your program do, in plain language?

---

## 1. The Problem

What does your program solve or provide? Who would use it? Write 2–3 sentences. No jargon.

> *Example: "A text-based inventory tracker for tabletop RPG players. The user adds, removes, and searches items by category. It saves the inventory to a file so it persists between sessions."*

---

## 2. State Inventory

List every piece of data your program tracks. For each, note its type and what changes it.

| Data | Type | What Changes It |
|---|---|---|
| *Example: player health* | *int* | *Taking damage, using potions, resting* |
| *Example: inventory items* | *array of strings* | *Picking up items, dropping, using* |
| | | |
| | | |
| | | |

> **Track C note:** Use plain-language types (number, text, list, true/false). The thinking matters more than the syntax.

---

## 3. Function / Component Map

Break your program into pieces. Each piece does one job.

| Function or Component | What It Does | Inputs | Outputs |
|---|---|---|---|
| *Example: displayMenu()* | *Shows main menu, gets user choice* | *none* | *int (menu choice)* |
| *Example: loadInventory()* | *Reads items from save file* | *filename* | *populated array* |
| | | | |
| | | | |
| | | | |

> Aim for at least 5 entries at B tier, 7+ at A tier. If a function does two unrelated things, split it.

---

## 4. User Flow

Describe what happens from the moment the user runs the program to when they quit. Use numbered steps or a simple flowchart. Focus on the *main path* first, then note branches.

**Main path:**

1. 
2. 
3. 
4. 
5. 

**Key branches:**

- If the user does X → ...
- If the file doesn't exist → ...
- If input is invalid → ...

---

## 5. What Could Go Wrong

List at least 3 things that could break or confuse the user. For each, state your plan.

| Risk | Plan |
|---|---|
| *Example: User enters text when a number is expected* | *Input validation loop with clear error message* |
| *Example: Save file is missing on first run* | *Check if file exists; if not, start with empty state* |
| | |
| | |
| | |

---

## 6. What I'll Ask AI to Help With

Be specific. "Help me code it" is not a plan. Good entries name the *task* and the *reason*.

| Task | Why AI Help Makes Sense |
|---|---|
| *Example: Write the file-parsing function* | *I understand the logic but string splitting syntax is fiddly* |
| *Example: Suggest a cleaner way to organize my menu* | *My current version has too many nested ifs* |
| | |
| | |

---

## 7. What I'll Do Myself (No AI)

Name at least 2 parts you'll write or solve without AI assistance. These should be things where the struggle is the learning.

1. 
2. 

---

## 8. Scope Check

Answer honestly:

- Can I build the C-tier version in one focused work session? **yes / no / unsure**
- Does every feature in my plan connect to the core interaction? **yes / no**
- Have I cut anything that's "nice to have" but not essential? **yes / no**

> If you answered "no" or "unsure" to the first question, your scope is too large. Cut features until the answer is yes, then add B/A tier features as stretch goals.

---

## Instructor Approval

*To be filled out during Week 13 check-in:*

- [ ] Scope is appropriate
- [ ] State inventory is complete
- [ ] Function map shows clear decomposition
- [ ] Student knows what they'll ask AI for and what they'll do themselves

**Notes:**

