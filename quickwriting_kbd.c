#include "app.h"
#include "draw.h"
#include "input.h"

int32_t quickwriting_kbd_app(void* p) {
    UNUSED(p);
    App* a = malloc(sizeof(App));
    a->mutex = furi_mutex_alloc(FuriMutexTypeNormal);
    a->state = StateGrid;
    a->mode = ModeLetters;
    a->text_len = 0;
    a->text[0] = 0;
    a->shift = 0;
    a->caps_lock = 0;
    a->cursor = ZoneNone;
    a->cell_cursor = (int)ZoneC;
    for(int i = 0; i < 4; i++) { a->dpad[i] = 0; a->press_tick[i] = 0; }
    a->running = 1;
    a->back_short = 0;
    a->settings_page = 0;
    a->settings_selector = -1;
    settings_load(a);

    ViewPort* vp = view_port_alloc();
    view_port_draw_callback_set(vp, render_callback, a);
    view_port_input_callback_set(vp, input_callback, a);

    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, vp, GuiLayerFullscreen);

    while(a->running) {
        view_port_update(vp);
        furi_delay_ms(50);
    }

    gui_remove_view_port(gui, vp);
    view_port_free(vp);
    furi_record_close(RECORD_GUI);
    furi_mutex_free(a->mutex);
    free(a);
    return 0;
}