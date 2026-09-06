#include "input.h"
#include "app.h"

#define AUTO_SELECT_MS 400

// ── Helpers ──
static void do_grid_enter(App* a) {
    if(a->cursor == ZoneNone) return;
    a->sel_zone = a->cursor;
    a->cell_cursor = (int)ZoneC;
    a->state = StateCell;
}
static void do_cell_select(App* a) {
    const ZoneDef* zd = &current_zones(a)[a->sel_zone];
    const CellSlot* s = &zd->slots[a->cell_cursor];
    do_action(a, s->type, s->ch);
}
static void do_menu_select(App* a) {
    const CellSlot* s = &menu_slots[a->cell_cursor];
    do_action(a, s->type, s->ch);
}

// ── Settings ──
static const int8_t srows[2] = {4,4};
static void settings_change(App* a, int dir) {
    int8_t row = a->settings_selector;
    if(row < 0) { a->settings_page = (a->settings_page + 1) % 2; return; }
    if(row >= 4) return;
    int8_t* p = NULL;
    int8_t pg = a->settings_page;
    if(pg == 0) {
        if(row == 0) p = &a->settings.grid_ox;
        else if(row == 1) p = &a->settings.grid_oy;
        else if(row == 2) p = &a->settings.grid_cw;
        else if(row == 3) p = &a->settings.grid_ch;
    } else {
        if(row == 0) p = &a->settings.cell_ox;
        else if(row == 1) p = &a->settings.cell_oy;
        else if(row == 2) p = &a->settings.cell_cw;
        else if(row == 3) p = &a->settings.cell_ch;
    }
    if(!p) return;
    int8_t step = (pg==0 && row>=2) ? 4 : ((pg==1 && row>=2) ? 4 : 1);
    *p += dir * step;
    if(*p < 2) *p = 2;
    if(*p > 60) *p = 60;
    settings_save(a);
}

void input_callback(InputEvent* ev, void* ctx) {
    furi_assert(ctx);
    App* a = (App*)ctx;
    furi_mutex_acquire(a->mutex, FuriWaitForever);

    // Track dpad
    if(ev->key == InputKeyUp && ev->type != InputTypeRepeat) {
        if(ev->type == InputTypePress) { a->dpad[0] = 1; a->press_tick[0] = furi_get_tick(); }
        else if(ev->type == InputTypeRelease) a->dpad[0] = 0;
    }
    if(ev->key == InputKeyDown && ev->type != InputTypeRepeat) {
        if(ev->type == InputTypePress) { a->dpad[1] = 1; a->press_tick[1] = furi_get_tick(); }
        else if(ev->type == InputTypeRelease) a->dpad[1] = 0;
    }
    if(ev->key == InputKeyLeft && ev->type != InputTypeRepeat) {
        if(ev->type == InputTypePress) { a->dpad[2] = 1; a->press_tick[2] = furi_get_tick(); }
        else if(ev->type == InputTypeRelease) a->dpad[2] = 0;
    }
    if(ev->key == InputKeyRight && ev->type != InputTypeRepeat) {
        if(ev->type == InputTypePress) { a->dpad[3] = 1; a->press_tick[3] = furi_get_tick(); }
        else if(ev->type == InputTypeRelease) a->dpad[3] = 0;
    }

    GridZone z = zone_from_dpad(a->dpad[0],a->dpad[1],a->dpad[2],a->dpad[3]);
    bool free = all_dpad_released(a);

    // ── BACK ──
    if(ev->key == InputKeyBack) {
        if(ev->type == InputTypePress) a->back_short = true;
        else if(ev->type == InputTypeLong) {
            a->back_short = false;
            if(a->state == StateSettings) { settings_save(a); a->state = StateMenu; a->cell_cursor=(int)ZoneC; }
            else { a->state = StateMenu; a->cell_cursor=(int)ZoneC; }
        } else if(ev->type == InputTypeRelease && a->back_short) {
            a->back_short = false;
            if(a->state == StateSettings) { settings_save(a); a->state = StateGrid; }
            else if(a->state == StateMenu) a->state = StateGrid;
            else if(a->state == StateCell) a->state = StateGrid;
            else if(a->state == StateGrid) a->cursor = ZoneC;
        }
        furi_mutex_release(a->mutex); return;
    }

    // ── SETTINGS ──
    if(a->state == StateSettings) {
        if(ev->type == InputTypePress) {
            bool u = a->dpad[0], d = a->dpad[1], l = a->dpad[2], r = a->dpad[3];
            bool on_header = (a->settings_selector < 0);
            if(u && !d && !l && !r) { // pure up
                if(a->settings_selector >= 0) a->settings_selector--;
                if(a->settings_selector < -1) a->settings_selector = -1;
            } else if(d && !u && !l && !r) { // pure down
                if(a->settings_selector < srows[a->settings_page]-1) a->settings_selector++;
            } else if(l && !u && !d && !r) { // pure left
                if(on_header) { a->settings_page = (a->settings_page + 1) % 2; }
                else { settings_change(a, -1); }
            } else if(r && !u && !d && !l) { // pure right
                if(on_header) { a->settings_page = (a->settings_page + 1) % 2; }
                else { settings_change(a, 1); }
            } else if(u && l && on_header) {
                a->settings_page = (a->settings_page + 1) % 2;
            } else if(u && r && on_header) {
                a->settings_page = (a->settings_page + 1) % 2;
            }
        }
        if(ev->key == InputKeyOk && ev->type == InputTypePress) { settings_save(a); a->state = StateGrid; }
        furi_mutex_release(a->mutex); return;
    }

    // ── REPEAT: auto-select only in cell ──
    if(ev->type == InputTypeRepeat && a->state == StateCell) {
        uint32_t now = furi_get_tick();
        int held = -1;
        for(int i = 0; i < 4; i++)
            if(a->dpad[i] && (now - a->press_tick[i]) >= AUTO_SELECT_MS) { held = i; break; }
        if(held >= 0 && a->cell_cursor >= 0) do_cell_select(a);
        furi_mutex_release(a->mutex); return;
    }

    // ── PRESS ──
    if(ev->type == InputTypePress) {
        if(a->state == StateGrid) a->cursor = z;
        else if(z != ZoneNone) a->cell_cursor = (int)z;
        furi_mutex_release(a->mutex); return;
    }

    // ── RELEASE ──
    if(ev->type == InputTypeRelease && free) {
        if(a->state == StateGrid && a->cursor != ZoneNone) do_grid_enter(a);
        else if(a->state == StateCell) do_cell_select(a);
        else if(a->state == StateMenu) do_menu_select(a);
    }

    // ── OK ──
    if(ev->key == InputKeyOk && ev->type == InputTypePress) {
        if(a->state == StateGrid && a->cursor != ZoneNone) do_grid_enter(a);
        else if(a->state == StateCell) do_cell_select(a);
        else if(a->state == StateMenu) do_menu_select(a);
    }

    furi_mutex_release(a->mutex);
}