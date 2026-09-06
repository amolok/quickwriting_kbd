# QuickWriting Keyboard for Flipper Zero

A proof-of-concept text input application for Flipper Zero inspired by **Ken Perlin's Quikwriting** research.

This project serves as a tribute to continuous stylus-based text entry methods and explores their adaptation to constrained embedded devices with D-Pad-only interfaces.

![[https://mrl.cs.nyu.edu/~perlin/demos/template2_0_small.gif]]

---

## How it works

The screen is divided into a **3×3 zone grid**. A text line at the bottom displays your input — you can backspace or exit anytime. Navigation follows two levels:
- Move the joystick to enter a zone → release to navigate inside it
- Navigate the inner 3×3 mini-grid of characters or actions → release to select

This mirrors Quikwriting's continuous input model on a D-Pad interface.

![[screenshots/Screenshot-20260824-184222.png]]
![[screenshots/Screenshot-20260824-184310.png]]
![[screenshots/Screenshot-20260824-184450.png]]

For further reading, explore related predictive input methods like **Dasher**: https://dasher.tbrt.net/

---

## Input modes

| Mode | Description |
|------|-------------|
| **Letters** | a–z, Space, Enter, Backspace, Shift, Caps Lock |
| **Symbols** | `? { } \ ^ ! * % , ; _ " : & \| ~ [ @ # $ + .` |
| **Digits** | 0–9, +, -, ., /, =, <, >, [, ], {, }, `, %, *, # |

Mode toggles use geometric icons in the grid (rectangle, circle, triangles). Caps Lock mode has uppercase letters.

Note: The Quikwriting layout is kept as-is as a tribute to Perlin's original design. While not optimized for D-Pad input, this serves as proof-of-concept and homage to the Quikwriting method.

### Icon Glossary

| Icon | Shape | Meaning |
|------|-------|---------|
| Rectangle | ▭ | SYM — toggle Symbols mode |
| Triangle up | ▲ | CAP — Caps Lock |
| Triangle down | ▼ | UN — Uncap (clear Caps) |
| Triangle left | ◄ | DEL — Backspace |
| Triangle right | ► | SPC — Space |
| Circle | ○ | DGT — toggle Digits mode |

When Caps Lock is active, a small ▲P indicator appears in the text input area.

---

## Menu (long Back)

A 3×3 action menu accessible via long-pressing **Back**:
- Mode switches (SYM / DEL / LET)
- Special characters (`,` / `.`)
- Actions (ENT, SPC, DGT for navigation)
- Exit (EXT)

Short Back returns one level.

---

## Building

```shell
cd quickwriting_keyboard
ufbt build
```

Requires [ufbt](https://github.com/flipperdevices/flipperzero-ufbt) and Flipper Zero SDK (target 7, API 87.1).

---

## Files

```
quickwriting_keyboard/
├── application.fam       # app manifest
├── quickwriting_kbd.c    # entry point
├── app.h / app.c         # core logic and zone definitions
├── draw.h / draw.c       # rendering (grid, cell, menu)
├── input.h / input.c     # D-Pad input handling
└── README.md             # this file
```

---

## License

MIT — original Quikwriting by Ken Perlin (NYU Media Research Lab).

Original research: [Quikwriting](https://mrl.cs.nyu.edu/projects/quikwriting/).  

![[screenshots/Screenshot-20260824-185410.png]]

*(Note: punctuation marks have been added for readability where absent in the original.)*
