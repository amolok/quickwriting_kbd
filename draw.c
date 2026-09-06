#include "draw.h"

// ── Icon primitives ──
static void tri_up(Canvas* c,int cx,int cy,int s) {
    canvas_draw_line(c,cx-s/2,cy+s/2,cx,cy-s/2);
    canvas_draw_line(c,cx,cy-s/2,cx+s/2,cy+s/2);
    canvas_draw_line(c,cx-s/2,cy+s/2,cx+s/2,cy+s/2);
}
static void tri_dn(Canvas* c,int cx,int cy,int s) {
    canvas_draw_line(c,cx-s/2,cy-s/2,cx,cy+s/2);
    canvas_draw_line(c,cx,cy+s/2,cx+s/2,cy-s/2);
    canvas_draw_line(c,cx-s/2,cy-s/2,cx+s/2,cy-s/2);
}
static void tri_lt(Canvas* c,int cx,int cy,int s) {
    canvas_draw_line(c,cx+s/2,cy-s/2,cx-s/2,cy);
    canvas_draw_line(c,cx-s/2,cy,cx+s/2,cy+s/2);
    canvas_draw_line(c,cx+s/2,cy-s/2,cx+s/2,cy+s/2);
}
static void tri_rt(Canvas* c,int cx,int cy,int s) {
    canvas_draw_line(c,cx-s/2,cy-s/2,cx+s/2,cy);
    canvas_draw_line(c,cx+s/2,cy,cx-s/2,cy+s/2);
    canvas_draw_line(c,cx-s/2,cy-s/2,cx-s/2,cy+s/2);
}
static void rect(Canvas* c,int cx,int cy,int w,int h) { canvas_draw_frame(c,cx-w/2,cy-h/2,w,h); }
static void circ(Canvas* c,int cx,int cy,int r) { canvas_draw_circle(c,cx,cy,r); }
static void diamond(Canvas* c,int cx,int cy,int s) {
    canvas_draw_line(c,cx,cy-s/2,cx+s/2,cy);
    canvas_draw_line(c,cx+s/2,cy,cx,cy+s/2);
    canvas_draw_line(c,cx,cy+s/2,cx-s/2,cy);
    canvas_draw_line(c,cx-s/2,cy,cx,cy-s/2);
}

static void draw_slot_glyph(Canvas* c,SlotGlyph g,int cx,int cy,int sz) {
    switch(g){
        case GlyphRect:    rect(c,cx,cy,sz,sz+2); break;
        case GlyphTriUp:   tri_up(c,cx,cy,sz); break;
        case GlyphTriDown: tri_dn(c,cx,cy,sz); break;
        case GlyphTriLeft: tri_lt(c,cx,cy,sz); break;
        case GlyphTriRight:tri_rt(c,cx,cy,sz); break;
        case GlyphCircle:  circ(c,cx,cy,sz/2); break;
        case GlyphDiamond: diamond(c,cx,cy,sz); break;
        default: break;
    }
}
static void draw_grid_glyph(Canvas* c,GridGlyph g,int cx,int cy) {
    int s=8;
    switch(g){
        case GridGlyphRect:   rect(c,cx,cy,s,s+2); break;
        case GridGlyphTriUp:  tri_up(c,cx,cy,s); break;
        case GridGlyphTriDown:tri_dn(c,cx,cy,s); break;
        case GridGlyphCircle: circ(c,cx,cy,s/2); break;
        case GridGlyphDiamond: diamond(c,cx,cy,s); break;
        default: break;
    }
}

// ── Text line ──
static void draw_textline(Canvas* ca,App* a) {
    canvas_set_color(ca,ColorBlack);
    canvas_draw_line(ca,0,62,127,62);
    canvas_set_font(ca,FontPrimary);
    char b[21]; uint8_t s=a->text_len>20?a->text_len-20:0,di=0;
    for(uint8_t i=s;i<a->text_len&&di<20;i++) b[di++]=a->text[i];
    b[di]=0; canvas_draw_str(ca,4,62,b);
}

// ── Grid ──
static void draw_grid(Canvas* ca,App* a) {
    int8_t ox=a->settings.grid_ox, oy=a->settings.grid_oy, cw=a->settings.grid_cw, ch=a->settings.grid_ch;
    const ZoneDef* zs=current_zones(a);
    canvas_set_font(ca,FontSecondary);
    GridZone ord[9]={ZoneUL,ZoneU,ZoneUR,ZoneL,ZoneC,ZoneR,ZoneDL,ZoneD,ZoneDR};
    for(int i=0;i<9;i++){
        int r=i/3,col=i%3,x=ox+col*cw,y=oy+r*ch;
        bool sel=(ord[i]==a->cursor);
        const ZoneDef* zd=&zs[ord[i]];
        canvas_set_color(ca,sel?ColorBlack:ColorWhite);
        canvas_draw_box(ca,x+1,y+1,cw-2,ch-2);
        canvas_set_color(ca,sel?ColorWhite:ColorBlack);
        canvas_draw_frame(ca,x,y,cw,ch);
        if(zd->grid_glyph!=GridGlyphText) draw_grid_glyph(ca,zd->grid_glyph,x+cw/2,y+ch/2);
        else canvas_draw_str_aligned(ca,x+cw/2,y+ch/2,AlignCenter,AlignCenter,zd->grid_label);
    }
    draw_textline(ca,a);
}

// ── Cell ──
static void draw_cell(Canvas* ca,App* a) {
    int8_t ox=a->settings.cell_ox, oy=a->settings.cell_oy;
    int8_t cw=a->settings.cell_cw, ch=a->settings.cell_ch, gap=a->settings.cell_gap;
    const ZoneDef* zd=&current_zones(a)[a->sel_zone];
    canvas_set_font(ca,FontSecondary);
    for(int i=0;i<9;i++){
        int r=i/3,col=i%3,x=ox+col*(cw+gap),y=oy+r*(ch+gap);
        const CellSlot* s=&zd->slots[i];
        bool sel=(i==a->cell_cursor);
        canvas_set_color(ca,sel?ColorBlack:ColorWhite);
        canvas_draw_box(ca,x+1,y+1,cw-2,ch-2);
        canvas_set_color(ca,sel?ColorWhite:ColorBlack);
        canvas_draw_frame(ca,x,y,cw,ch);
        canvas_set_color(ca,sel?ColorWhite:ColorBlack);
        if(s->label[0]) {
            if(s->glyph!=GlyphNone) draw_slot_glyph(ca,s->glyph,x+cw/2,y+ch/2,9);
            else canvas_draw_str_aligned(ca,x+cw/2,y+ch/2,AlignCenter,AlignCenter,s->label);
        }
    }
}

// ── Menu ──
static void draw_menu(Canvas* ca,App* a) {
    int8_t ox=a->settings.cell_ox, oy=a->settings.cell_oy;
    int8_t cw=a->settings.cell_cw, ch=a->settings.cell_ch, gap=a->settings.cell_gap;
    canvas_set_font(ca,FontSecondary);
    for(int i=0;i<9;i++){
        int r=i/3,col=i%3,x=ox+col*(cw+gap),y=oy+r*(ch+gap);
        bool sel=(i==a->cell_cursor);
        const CellSlot* s=&menu_slots[i];
        canvas_set_color(ca,sel?ColorBlack:ColorWhite);
        canvas_draw_box(ca,x+1,y+1,cw-2,ch-2);
        canvas_set_color(ca,sel?ColorWhite:ColorBlack);
        canvas_draw_frame(ca,x,y,cw,ch);
        if(s->label[0]) {
            canvas_set_color(ca,sel?ColorWhite:ColorBlack);
            if(s->glyph!=GlyphNone) draw_slot_glyph(ca,s->glyph,x+cw/2,y+ch/2,9);
            else canvas_draw_str_aligned(ca,x+cw/2,y+ch/2,AlignCenter,AlignCenter,s->label);
        }
    }
    draw_textline(ca,a);
}

// ── Settings ──
static const char* page_labels[2][4] = {
    {"Grid OX","Grid OY","Grid CW","Grid CH"},
    {"Cell OX","Cell OY","Cell CW","Cell CH"},
};
static const int8_t page_rows[2] = {4,4};
static const char* spage_names[2] = {"Grid Layout","Cell Layout"};

static int8_t* sptr(App* a,int8_t pg,int8_t row) {
    if(pg==0){switch(row){case 0:return&a->settings.grid_ox;case 1:return&a->settings.grid_oy;case 2:return&a->settings.grid_cw;case 3:return&a->settings.grid_ch;}}
    else{switch(row){case 0:return&a->settings.cell_ox;case 1:return&a->settings.cell_oy;case 2:return&a->settings.cell_cw;case 3:return&a->settings.cell_ch;}}
    return NULL;
}

static void draw_settings(Canvas* ca,App* a) {
    canvas_clear(ca);
    canvas_set_font(ca,FontPrimary);
    canvas_draw_str(ca,2,10, spage_names[a->settings_page]);
    canvas_set_font(ca,FontSecondary);
    char hbuf[32];
    snprintf(hbuf,sizeof(hbuf),"gap=%d", a->settings.cell_gap);
    canvas_draw_str(ca,90,10, hbuf);
    for(int r=0; r<page_rows[a->settings_page]; r++) {
        int y = 20 + r*12;
        int8_t* p = sptr(a, a->settings_page, r);
        bool sel = (a->settings_selector == r);
        if(sel) { canvas_set_color(ca,ColorBlack); canvas_draw_box(ca,0,y-1,128,11); canvas_set_color(ca,ColorWhite); }
        else canvas_set_color(ca,ColorBlack);
        canvas_draw_str(ca,4, y+8, page_labels[a->settings_page][r]);
        if(p) { char vb[16]; snprintf(vb,sizeof(vb),"%d", *p); canvas_draw_str(ca,80, y+8, vb); }
    }
    canvas_set_color(ca,ColorBlack);
    canvas_draw_line(ca,0,62,127,62);
    canvas_set_font(ca,FontSecondary);
    canvas_draw_str(ca,2,62, "L/R=change  OK=save&exit");
}

// ── Render ──
void render_callback(Canvas* ca, void* ctx) {
    furi_assert(ctx); App* a=(App*)ctx;
    furi_mutex_acquire(a->mutex,FuriWaitForever);
    canvas_clear(ca);
    switch(a->state){
        case StateGrid: draw_grid(ca,a); break;
        case StateCell: draw_cell(ca,a); break;
        case StateMenu: draw_menu(ca,a); break;
        case StateSettings: draw_settings(ca,a); break;
    }
    furi_mutex_release(a->mutex);
}