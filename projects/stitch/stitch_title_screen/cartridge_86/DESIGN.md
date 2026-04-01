```markdown
# Design System Specification: 1986 Industrial Arcade

## 1. Overview & Creative North Star
**Creative North Star: "Tactile Command & Control"**

This design system rejects the soft, blurry aesthetics of modern "vaporwave" in favor of the rigid, high-contrast, and utilitarian digital world of 1986. We are not building a dream; we are building a machine. This system draws inspiration from the rugged internals of a Commodore 64 and the high-stakes friction of a dimly lit arcade cabinet.

To move beyond a "template" look, this system utilizes **Hard-Edge Asymmetry**. We break the standard grid by using heavy, blocky borders and intentional offsets that mimic the limitations of 8-bit hardware. Layouts should feel constructed rather than rendered, using layered rectangles and bold primary colors to create a hierarchy that demands attention.

---

## 2. Colors & Surface Logic

### The Palette
The color system is built on a foundation of deep charcoals (`#131313`) and high-impact "safety" primaries.
- **Primary (`#ffb4a8` / `#ff5540`):** Use for critical actions and "Warning" states.
- **Secondary (`#b6c4ff` / `#0356ff`):** Use for technical data and interactive navigation.
- **Tertiary (`#f1c100`):** The "Safety Yellow." Use for status indicators and specialized accents.

### The "No-Line" Rule (Alternative Interpretation)
In this system, we prohibit the standard "modern" 1px soft border. Instead, boundaries are defined by **Structural Insets**. Use `surface-container-lowest` (`#0e0e0e`) to "carve" into the page, or `surface-bright` (`#393939`) to create raised mechanical plates. 

### Surface Hierarchy & Nesting
Treat the UI as a physical motherboard. 
- **Base Level:** `surface` (`#131313`).
- **Sub-Panels:** Use `surface-container` (`#201f1f`) for the main content area.
- **Raised Modules:** Use `surface-container-high` (`#2a2a2a`) for interactive cards.
- **Nesting:** Never use a shadow to lift an element. If a card needs to stand out, change its background token to one tier higher or lower than its parent.

### The "Glass & Gradient" Rule (Arcade Edition)
Instead of soft Gaussian blurs, we use **Dithered Gradients**. For CTAs, transition from `primary` (`#ffb4a8`) to `primary-container` (`#ff5540`) to mimic the glow of a CRT monitor. "Glass" effects should be high-opacity with no blur—think smoked acrylic panels, not frosted glass.

---

## 3. Typography

The typography strategy pairs technical precision with aggressive display scales.

*   **Display & Headlines (Space Grotesk):** This is our "Technical Bold." It should be used in all-caps for headlines to mimic the blocky, geometric sans-serifs of early computing.
    *   *Headline-LG (`2rem`):* Used for section headers.
*   **Body & Titles (Work Sans):** Chosen for its high legibility at small scales. Work Sans provides a functional, "instruction manual" feel that balances the aggression of the headlines.
*   **Labels (Space Grotesk):** Used for micro-copy and data points. These should always be high-contrast (`on-surface`).

---

## 4. Elevation & Depth

### The Layering Principle
Forget Z-axis shadows. Depth in this system is **Mechanical**. Elements are either "Bolted On" (higher surface tier) or "Cut Out" (lower surface tier). 
- **The "Step" Effect:** To show hierarchy, shift the background color. A `surface-container-highest` button sitting on a `surface-container` panel creates a "tactile switch" feel without a single drop shadow.

### The "Ghost Border" & Pixel Perfection
Traditional 1px lines are forbidden. Instead, use **Pixel-Block Borders**. 
- Borders must be `2px` or `4px` (referencing the Spacing Scale `px` or `0.5`).
- Use the `outline` token (`#b18780`) only for active input states or critical focus.
- **Do not use opacity.** This system is binary; an element is either there or it isn't.

### Signature Textures
To add "soul," use a subtle scanline overlay (a repeating 2px linear gradient) on `surface-bright` containers to emulate a CRT screen.

---

## 5. Components

### Buttons
- **Primary:** Background: `primary-container` (`#ff5540`). Border: None. Shape: `0px` (Strictly Square). 
- **Secondary:** Background: `surface-container-highest`. Border: 2px `secondary`.
- **States:** On hover, the background and text color should invert instantly (no transition duration).

### Input Fields
- **Styling:** Background: `surface-container-lowest`. Border-bottom: 4px `tertiary` (`#f1c100`).
- **Interaction:** When focused, the border-bottom should "blink" to mimic a command line cursor.

### Cards & Lists
- **The No-Divider Rule:** Forbid the use of horizontal rules. Use vertical whitespace from the spacing scale (e.g., `spacing-4`) or toggle between `surface-container` and `surface-container-low` for alternating list items.

### Chips (Status Indicators)
- Square edges (`0px`). Use high-contrast pairings like `on-tertiary` text on a `tertiary` background for a "Warning" or "System" status.

### Custom Component: The "LED Header"
A thin strip (4px) of `primary` or `tertiary` color placed at the very top of a container to indicate it is "powered on."

---

## 6. Do’s and Don’ts

### Do:
- **Embrace the Square:** Every corner must be `0px`. Roundness is a failure of the hardware.
- **Use High Contrast:** If text is hard to read, don't use a shadow; change the background to `surface-container-lowest`.
- **Align to the Pixel:** Ensure all elements sit on the `0.2rem` (spacing-1) grid to maintain the "bit-mapped" look.

### Don’t:
- **No Soft Shadows:** Never use `box-shadow` with a blur radius greater than `0px`. If you need a shadow, use a hard-edged offset block of `surface-container-lowest`.
- **No Pastels:** If the color looks "friendly," it’s wrong. Stick to the rugged, industrial primaries.
- **No Transitions:** Avoid "ease-in-out." Digital states in 1986 were instantaneous. Use `transition: none;`.

### Accessibility Note:
While we aim for a "dim arcade" feel, ensure that `on-surface` text on `surface-container` maintains at least a 7:1 contrast ratio for readability. When in doubt, use the `tertiary` (Yellow) for critical instructions.