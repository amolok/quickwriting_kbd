#pragma once
#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>
#include <storage/storage.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TEXT_BUF_SIZE 64
#define SETTINGS_DIR  "/ext/apps_data/quickwriting_kbd"
#define SETTINGS_PATH "/ext/apps_data/quickwriting_kbd/settings.txt"
#define SETTINGS_PAGE_COUNT 2

typedef enum { ZoneUL,ZoneU,ZoneUR,ZoneL,ZoneC,ZoneR,ZoneDL,ZoneD,ZoneDR,ZoneNone } GridZone;
typedef enum { StateGrid, StateCell, StateMenu, StateSettings } AppState;
typedef enum { ModeLetters, ModeCaps, ModeSymbols, ModeDigits } InputMode;

typedef enum {
    ActChar, ActSpace, ActBackspace, ActShift,
    ActCapsLock, ActUncaps, ActEnter,
    ActModeLetters, ActModeCaps, ActModeSymbols, ActModeDigits,
    ActQuickDigits, ActSettings, ActExit,
} SlotType;

typedef enum { GlyphNone, GlyphRect, GlyphTriUp, GlyphTriDown, GlyphTriLeft, GlyphTriRight, GlyphCircle, GlyphDiamond } SlotGlyph;
typedef enum { GridGlyphText, GridGlyphRect, GridGlyphTriUp, GridGlyphTriDown, GridGlyphCircle, GridGlyphDiamond } GridGlyph;

typedef struct { SlotType type; char ch; const char* label; SlotGlyph glyph; } CellSlot;
typedef struct { const char* grid_label; GridGlyph grid_glyph; CellSlot slots[9]; } ZoneDef;

typedef struct {
    int8_t grid_ox, grid_oy, grid_cw, grid_ch;
    int8_t cell_ox, cell_oy, cell_cw, cell_ch, cell_gap;
} SettingsData;
#define SETTINGS_DEFAULT {10,2,36,18, 13,4,30,14,3}

typedef struct {
    FuriMutex* mutex;
    AppState state;
    InputMode mode;
    GridZone sel_zone;
    GridZone cursor;
    int cell_cursor;
    char text[TEXT_BUF_SIZE];
    uint8_t text_len;
    bool shift, caps_lock;
    bool dpad[4];
    uint32_t press_tick[4];
    bool running, back_short;
    SettingsData settings;
    int8_t settings_page, settings_selector;
} App;

#define S(ch,l)     {ActChar,(ch),(l),GlyphNone}
#define S_NONE      {ActChar,0,"",GlyphNone}
#define S_SPC       {ActSpace,0,"SPC",GlyphTriRight}
#define S_DEL       {ActBackspace,0,"DEL",GlyphTriLeft}
#define S_ENT       {ActEnter,0,"ENT",GlyphNone}
#define S_CAP       {ActCapsLock,0,"CAP",GlyphTriUp}
#define S_UN        {ActUncaps,0,"UN",GlyphTriDown}
#define S_SYM       {ActModeSymbols,0,"SYM",GlyphRect}
#define S_LET       {ActModeLetters,0,"LET",GlyphDiamond}
#define S_CPS       {ActModeCaps,0,"CPS",GlyphTriUp}
#define S_DGT       {ActModeDigits,0,"DGT",GlyphCircle}
#define S_QDG       {ActQuickDigits,0,"1-9",GlyphNone}
#define S_SET       {ActSettings,0,"CFG",GlyphNone}
#define S_EXT       {ActExit,0,"EXT",GlyphNone}

extern const ZoneDef zones_letters[9], zones_caps[9], zones_symbols[9], zones_digits[9];
extern const CellSlot menu_slots[9];

GridZone zone_from_dpad(bool u,bool d,bool l,bool r);
bool all_dpad_released(App* a);
char to_upper_ascii(char c);
void append_char(App* a, char c);
void backspace(App* a);
const ZoneDef* current_zones(App* a);
void return_to_grid(App* a);
void do_action(App* a, SlotType t, char ch);
void settings_load(App* a);
void settings_save(App* a);