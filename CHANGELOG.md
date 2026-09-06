# CHANGELOG

### 2026-08-24 Caps mode + new menu + layout shrink

- Added `ModeCaps` — separate uppercase screen (CAP activates, ZoneU has LET to return)
- Removed UN (triangle-down) from letters/caps ZoneD; caps handled via mode switch
- Added mode indicator glyph in grid center: diamond (LET), tri-up (CAPS), rect (SYM), circle (DGT)
- New menu layout: U=DGT (circle), L=EXT, R=CFG, D=ENT
- Shrunk grid to 36×18 (ox=10, centered + pushed up); cell 30×14 (ox=13, gap=3)
- Quick digits reuses same grid layout (no separate big-digit screen)
- Auto-select only fires in cell (fixes missing characters)