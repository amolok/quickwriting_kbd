# QuickWriting Keyboard for Flipper Zero

A text entry application for Flipper Zero using the **Quikwriting** method — a single-stroke gesture keyboard operated entirely with the D-Pad.

Based on the original research by **Ken Perlin**:

- [Quikwriting: Continuous Stylus-Based Text Entry](https://mrl.cs.nyu.edu/projects/quikwriting/)
- [Ken Perlin — NYU Media Research Lab](https://mrl.cs.nyu.edu/~perlin/)

## How it works

The 128×64 screen is divided into a **3×3 zone grid**. To enter a character:

1. Press a D-Pad direction (or diagonal) to highlight a zone → release to **enter** it.
2. Once inside a zone, you see a **3×3 mini-grid** of characters or actions.
3. Press a direction to highlight a slot → release to **select** it.
4. **OK** button works as a fallback confirm in cell / menu / digit views.

No stylus, no touchscreen — just the D-Pad and diagonals.

## Input modes

| Mode | Entry |
|------|-------|
| **Letters** (default) | a–z, Space, Enter, Backspace, Shift, Caps Lock |
| **Symbols** | `? { } ` ` / \ ^ ! * % , ; _ " : & \| ~ [ @ # $ + .` |
| **Digits** | 0–9, +, -, ., /, =, <, >, [, ], {, }, `, %, *, # |

Switch modes via:
- Rectangle icon (ZoneU) — toggle Letters ↗ Symbols
- Circle icon (ZoneD) — toggle Letters ↗ Digits
- Triangle-up (ZoneU, slot 3) — Letters
- Triangle-down (ZoneD, slot 7) — back to Letters

## Menu (long Back)

Long-press **Back** opens a 3×3 action menu:
- SYM / DEL / LET — mode switches
- `,` / `.` — punctuation
- EXT — exit app
- ENT / SPC / DGT — Enter, Space, Digits mode

Short **Back** returns one level (cell→grid, menu→grid).

## Icon glossary

| Icon | Shape | Meaning |
|------|-------|---------|
| Rectangle | ▭ | SYM — toggle Symbols mode |
| Triangle up | ▲ | CAP — Caps Lock |
| Triangle down | ▼ | UN — Uncap (clear Caps) |
| Triangle left | ◄ | DEL — Backspace |
| Triangle right | ► | SPC — Space |
| Circle | ○ | DGT — toggle Digits mode |

When Caps Lock is active, a small ▲P indicator appears in the text input area.

## Building

```shell
cd quickwriting_keyboard
ufbt build
```

Requires [ufbt](https://github.com/flipperdevices/flipperzero-ufbt) and Flipper Zero SDK (target 7, API 87.1).

## File structure

```
quickwriting_keyboard/
├── application.fam       # app manifest
├── quickwriting_kbd.c    # entry point
├── app.h                 # types, enums, macros, zone declarations
├── app.c                 # zone data and action functions
├── draw.h / draw.c       # all rendering (grid, cell, menu, icons)
├── input.h / input.c     # D-Pad input handling
└── README.md
```

## License

MIT