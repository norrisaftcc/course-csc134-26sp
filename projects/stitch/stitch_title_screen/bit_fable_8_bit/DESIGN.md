```markdown
# Design System Strategy: The Analog Interface

## 1. Overview & Creative North Star
**Creative North Star: "The High-Fidelity Retro-Future"**

This design system is not a mere exercise in nostalgia; it is a premium reconstruction of 1980s 8-bit constraints translated for modern high-resolution displays. We are moving beyond "pixel art" as a novelty and treating it as a high-end editorial choice. The system breaks the standard fluid-web "template" look by using intentional asymmetry, rigid block-based layouts, and a "mechanical" UI feel that mimics the physical limitations of an NES hardware sprite-buffer.

We reject modern "softness." There are no rounded corners (0px radius) and no subtle blurs. Instead, we lean into **Tonal Layering** and **High-Contrast Brutalism**. The layout should feel like a curated digital artifact—a luxury visual novel experience that balances the raw energy of an 80s arcade with the sophisticated spacing of a modern editorial magazine.

---

## 2. Colors: The Neon-Cathode Palette
The color strategy uses a limited, punchy gamut to simulate the NES hardware palette.

*   **Primary (#b7c4ff / #0050ff):** Use these for "Active Data." The primary container provides the "glow" of a high-end cathode tube.
*   **Secondary (#ffabf1 / #be05ba):** Reserved for "Heroine/Character" UI elements or vital narrative choices. It provides a sharp, synthetic contrast to the deep backgrounds.
*   **Tertiary (#71d6d6 / #007171):** Used for "System/Inventory" functions to provide a cool, technical feel.

### The "No-Line" Rule
Standard 1px hairline borders are strictly prohibited. They are too "clean" for an 8-bit aesthetic. Instead, define sections through:
1.  **Background Color Shifts:** Use `surface-container-lowest` (#0e0e0e) for the main dialogue box sitting atop a `surface` (#131313) background.
2.  **The "Block Border":** If a boundary is needed, it must be a minimum of 2px–4px using the `outline` or `primary` token to simulate hardware-rendered boxes.

### Surface Hierarchy & Nesting
Think of the UI as physical cartridges stacked on a console. 
*   **Base Layer:** `surface` (#131313)
*   **Dialog/Narrative Layer:** `surface-container-low` (#1b1b1b)
*   **Active Selection/Pop-up:** `surface-container-highest` (#353535)
This "step-up" in brightness creates depth without needing modern shadows.

### Signature Textures: The CRT Scanline
Apply a global CSS overlay of linear-gradients to create a 25% opacity scanline effect. For CTAs, use a hard-stop gradient from `primary` (#b7c4ff) to `primary-container` (#0050ff) to simulate a "glowing" hardware button.

---

## 3. Typography: Monospaced Authority
We use **Space Grotesk** as a high-end, monospaced-adjacent alternative to standard pixel fonts to ensure readability in long-form narrative.

*   **Display (3.5rem):** Used for Chapter Titles and "Game Over" screens. High-tracking (letter-spacing) is required to give an editorial feel.
*   **Headline (2rem):** Used for Character Names and major location changes.
*   **Body (1rem):** The core narrative text. Must be set with a generous line-height (1.5) to balance the "blockiness" of the aesthetic.
*   **Label (0.75rem):** For metadata like "Save Slot" or "Inventory Weight." Always uppercase.

The hierarchy conveys authority: Narrative text is the focus, while "System UI" is kept small, rigid, and strictly labeled.

---

## 4. Elevation & Depth: Tonal Stacking
In this system, "Elevation" is a lie told by color. 

*   **The Layering Principle:** Depth is achieved by placing a `surface-container-high` (#2a2a2a) element over a `surface-dim` (#131313) background. This creates a "hard-cut" depth characteristic of 8-bit sprite layering.
*   **Ambient Shadows (The 8-Bit Drop):** We do not use blurs. "Shadows" are 100% opaque offset blocks. For a floating card, use a 4px offset shadow using `surface-container-lowest` (#0e0e0e) or a deep `on-surface` tint.
*   **The "Ghost Border":** For inactive elements, use `outline-variant` (#434656) at 20% opacity. This suggests a container exists without cluttering the high-contrast environment.

---

## 5. Components

### Buttons (The "Input Keys")
*   **Primary:** Solid `primary-container` (#0050ff) background, `on-primary` text. No rounded corners. A 4px "bottom-heavy" shadow in `on-primary-fixed-variant` gives it a mechanical feel.
*   **Secondary:** `outline` 2px border, transparent background. Text in `secondary`.
*   **States:** On hover, the background and text color should invert instantly (no transition duration) to mimic 80s hardware response times.

### Dialogue Boxes (The "Text Engine")
*   **Layout:** Forbid dividers. Use `surface-container-lowest` for the background.
*   **Header:** The character name should sit in a "tab" that overlaps the top-left edge of the box, using a `secondary-container` (#be05ba) fill.

### Input Fields
*   **Styling:** A thick 2px `outline` border. Use `surface-container-highest` for the input well.
*   **Focus State:** The border color must change to `tertiary` (#71d6d6) with a slight "flicker" animation on entry.

### Additional Component: The "CRT Overlay"
A full-screen fixed `div` with a repeating linear gradient (black 50%, transparent 50%) at 2px height, set to `pointer-events: none` and 5% opacity. This binds the entire UI into a cohesive "screen."

---

## 6. Do's and Don'ts

### Do:
*   **Embrace Asymmetry:** Place the dialogue box slightly off-center to create a dynamic, cinematic feel.
*   **Use Intentional Overlap:** Let character sprites or UI labels "break" the borders of their containers.
*   **Snap Everything to 4px:** All spacing (`0.5`, `1`, `2` in the scale) should feel like it aligns to a physical pixel grid.

### Don't:
*   **No Rounded Corners:** `0px` is the only value allowed. Even a 2px radius destroys the 8-bit illusion.
*   **No Smooth Transitions:** Avoid `ease-in-out` 300ms. Use `steps()` or 0ms durations for state changes to mimic retro hardware.
*   **No Divider Lines:** Separate list items using a background shift from `surface-container-low` to `surface-container-high`. Lines are "noise" in an already high-contrast system.

### Accessibility Note:
While the palette is high-contrast, ensure that `on-background` text (#e2e2e2) always sits on `surface` (#131313) or darker containers to maintain a minimum 7:1 contrast ratio, ensuring the narrative remains legible for all players.```