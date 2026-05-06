# AI Interaction Log — Project 4

**Name:**  
**Project Title:**  
**AI Tool(s) Used:**  

---

## How to Use This Log

Record each meaningful AI interaction as you work. You don't need to log every typo fix — focus on interactions where AI helped you build, debug, or understand something. Aim for 8–15 entries across the project.

Copy the entry template below for each interaction.

---

## Entry Template

### Entry [number] — [date]

**What I was trying to do:**  
One sentence. What function, feature, or problem were you working on?

**What I prompted:**  
Paste your prompt or summarize it. If you gave AI context from your design doc, note which section.

**What AI gave me:**  
Summarize the output in 1–2 sentences. Don't paste entire code blocks — describe what it did.

**What I did with it:**  
Pick one:
- [ ] Used it as-is (explain why it was correct)
- [ ] Modified it (explain what you changed and why)
- [ ] Rejected it (explain what was wrong)
- [ ] Used the explanation but wrote my own code

**What I learned:**  
One sentence. What do you understand now that you didn't before?

---

## Sample Entry

### Entry 1 — Week 13, Tuesday

**What I was trying to do:**  
Write the `loadInventory()` function that reads items from a pipe-delimited file.

**What I prompted:**  
"I need a C++ function that reads lines from `inventory.txt` where each line looks like `sword|25|3`. It should split each line on `|` and store the values in three parallel arrays. Here's my state inventory from my design doc: [pasted section 2]."

**What AI gave me:**  
A function using `getline` with a while loop and `find()`/`substr()` to parse each line. It also added error checking for the file not opening.

**What I did with it:**  
Modified it. AI used a `vector<string>` but I'm using parallel arrays per my design. I rewrote the storage part to use my arrays and added a bounds check so it stops reading at `MAX_ITEMS`.

**What I learned:**  
The `find()` + `substr()` pattern for splitting strings — I can move the start position after each delimiter to grab the next field. Also learned that `stoi()` converts the string pieces to integers.

---

## End-of-Project Reflection

Complete this section before submitting.

**Total AI interactions logged:** ___

**Most useful interaction and why:**  


**An interaction where AI got it wrong:**  
What happened? How did you catch it? What did you do instead?


**What would you do differently next time?**  
Think about your prompting, your planning, your workflow — not just the code.


**Honest self-assessment:**  
Who drove this project — you or the AI? What's your evidence?

