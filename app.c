#include "app.h"

// ── Letters (lowercase) ──
const ZoneDef zones_letters[9] = {
    [ZoneUL]={"maskq",GridGlyphText,{S('a',"a"),S('s',"s"),S('k',"k"),S('m',"m"),S_NONE,S_NONE,S('q',"q"),S_NONE,S_NONE}},
    [ZoneU]={"    ",GridGlyphRect,{S_SYM,S_DEL,S_CAP,S('-',"-"),S_NONE,S(',',", "),S_SPC,S_NONE,S('.',". ")}},
    [ZoneUR]={"xpnfl",GridGlyphText,{S('p',"p"),S('f',"f"),S('n',"n"),S_NONE,S_NONE,S('l',"l"),S_NONE,S_NONE,S('x',"x")}},
    [ZoneL]={"hec  ",GridGlyphText,{S('h',"h"),S_NONE,S_NONE,S('e',"e"),S_NONE,S_NONE,S('c',"c"),S_NONE,S_NONE}},
    [ZoneC]={"    ",GridGlyphDiamond,{S_NONE,S_NONE,S_NONE,S_NONE,S_ENT,S_NONE,S_NONE,S_NONE,S_NONE}},
    [ZoneR]={"uty  ",GridGlyphText,{S_NONE,S_NONE,S('u',"u"),S_NONE,S_NONE,S('t',"t"),S_NONE,S_NONE,S('y',"y")}},
    [ZoneDL]={"vwzog",GridGlyphText,{S('v',"v"),S_NONE,S_NONE,S('w',"w"),S_NONE,S_NONE,S('o',"o"),S('g',"g"),S('z',"z")}},
    [ZoneD]={"    ",GridGlyphTriDown,{S_QDG,S_NONE,S('"',"\""),S(',',", "),S_NONE,S('.',". "),S_LET,S_SPC,S_DGT}},
    [ZoneDR]={"jbird",GridGlyphText,{S_NONE,S_NONE,S('j',"j"),S_NONE,S_NONE,S('r',"r"),S('b',"b"),S('d',"d"),S('i',"i")}},
};

// ── Caps (uppercase) ──
const ZoneDef zones_caps[9] = {
    [ZoneUL]={"MASKQ",GridGlyphText,{S('A',"A"),S('S',"S"),S('K',"K"),S('M',"M"),S_NONE,S_NONE,S('Q',"Q"),S_NONE,S_NONE}},
    [ZoneU]={"    ",GridGlyphTriUp,{S_SYM,S_DEL,S_LET,S('-',"-"),S_NONE,S(',',", "),S_SPC,S_NONE,S('.',". ")}},
    [ZoneUR]={"XPNFL",GridGlyphText,{S('P',"P"),S('F',"F"),S('N',"N"),S_NONE,S_NONE,S('L',"L"),S_NONE,S_NONE,S('X',"X")}},
    [ZoneL]={"HEC  ",GridGlyphText,{S('H',"H"),S_NONE,S_NONE,S('E',"E"),S_NONE,S_NONE,S('C',"C"),S_NONE,S_NONE}},
    [ZoneC]={"    ",GridGlyphTriUp,{S_NONE,S_NONE,S_NONE,S_NONE,S_ENT,S_NONE,S_NONE,S_NONE,S_NONE}},
    [ZoneR]={"UTY  ",GridGlyphText,{S_NONE,S_NONE,S('U',"U"),S_NONE,S_NONE,S('T',"T"),S_NONE,S_NONE,S('Y',"Y")}},
    [ZoneDL]={"VWZOG",GridGlyphText,{S('V',"V"),S_NONE,S_NONE,S('W',"W"),S_NONE,S_NONE,S('O',"O"),S('G',"G"),S('Z',"Z")}},
    [ZoneD]={"    ",GridGlyphTriDown,{S_QDG,S_NONE,S('"',"\""),S(',',", "),S_NONE,S('.',". "),S_LET,S_SPC,S_DGT}},
    [ZoneDR]={"JBIRD",GridGlyphText,{S_NONE,S_NONE,S('J',"J"),S_NONE,S_NONE,S('R',"R"),S('B',"B"),S('D',"D"),S('I',"I")}},
};

// ── Symbols ──
const ZoneDef zones_symbols[9] = {
    [ZoneUL]={"?`{/\\",GridGlyphText,{S('?',"?"),S('{',"{"),S('`',"`"),S('/',"/"),S_NONE,S_NONE,S('\\',"\\"),S_NONE,S_NONE}},
    [ZoneU]={"    ",GridGlyphRect,{S_SYM,S_DEL,S_CAP,S_NONE,S_NONE,S_NONE,S_NONE,S_NONE,S_LET}},
    [ZoneUR]={"!^}% ",GridGlyphText,{S('^',"^"),S('}',"}"),S('!',"!"),S_NONE,S_NONE,S('*',"*"),S_NONE,S_NONE,S('%',"%")}},
    [ZoneL]={",;_  ",GridGlyphText,{S(',',","),S_NONE,S_NONE,S(';',";"),S_NONE,S_NONE,S('_',"_"),S_NONE,S_NONE}},
    [ZoneC]={"    ",GridGlyphRect,{S_NONE,S_NONE,S_NONE,S_NONE,S_ENT,S_NONE,S_NONE,S_NONE,S_NONE}},
    [ZoneR]={"\":& ",GridGlyphText,{S_NONE,S_NONE,S('"',"\""),S(';',";"),S_NONE,S(':',":"),S_NONE,S_NONE,S('&',"&")}},
    [ZoneDL]={"|~ [ ",GridGlyphText,{S('|',"|"),S_NONE,S_NONE,S('~',"~"),S_NONE,S_NONE,S(',',","),S('[',"["),S('@',"@")}},
    [ZoneD]={"    ",GridGlyphTriDown,{S_NONE,S_NONE,S_NONE,S_NONE,S_NONE,S_NONE,S_LET,S_SPC,S_LET}},
    [ZoneDR]={"#].+ ",GridGlyphText,{S_NONE,S_NONE,S('$',"$"),S_NONE,S_NONE,S('+',"+"),S('#',"#"),S(']',"]"),S('.',".")}},
};

// ── Digits (grid) ──
const ZoneDef zones_digits[9] = {
    [ZoneUL]={"1/{< ",GridGlyphText,{S('1',"1"),S('{',"{"),S('<',"<"),S('/',"/"),S_NONE,S_NONE,S('=',"="),S_NONE,S_NONE}},
    [ZoneU]={"    ",GridGlyphRect,{S_SYM,S_DEL,S_CAP,S_NONE,S_NONE,S_NONE,S_NONE,S_NONE,S_LET}},
    [ZoneUR]={"2*}> ",GridGlyphText,{S('>',">"),S('}',"}"),S('2',"2"),S_NONE,S_NONE,S('*',"*"),S_NONE,S_NONE,S('%',"%")}},
    [ZoneL]={"357  ",GridGlyphText,{S('3',"3"),S('2',"2"),S('1',"1"),S('5',"5"),S_NONE,S_NONE,S('7',"7"),S('8',"8"),S('9',"9")}},
    [ZoneC]={"    ",GridGlyphCircle,{S_NONE,S_NONE,S_NONE,S_NONE,S_ENT,S_NONE,S_NONE,S_NONE,S_NONE}},
    [ZoneR]={" 468 ",GridGlyphText,{S_NONE,S_NONE,S('4',"4"),S_NONE,S_NONE,S('6',"6"),S_NONE,S_NONE,S('8',"8")}},
    [ZoneDL]={",9-[<",GridGlyphText,{S('<',"<"),S_NONE,S_NONE,S('9',"9"),S_NONE,S_NONE,S(',',","),S('[',"["),S('-',"-")}},
    [ZoneD]={"    ",GridGlyphTriDown,{S_QDG,S_NONE,S_NONE,S_NONE,S_NONE,S_NONE,S_LET,S_SPC,S_LET}},
    [ZoneDR]={".0+]>",GridGlyphText,{S_NONE,S_NONE,S('>',">"),S_NONE,S_NONE,S('0',"0"),S('+',"+"),S(']',"]"),S('.',".")}},
};

// ── Menu 3x3: U=DGT, L=EXT, R=CFG, D=ENT ──
const CellSlot menu_slots[9] = {
    S_NONE, S_DGT, S_NONE,
    S_EXT,  S_EXT, S_SET,
    S_NONE, S_ENT, S_NONE,
};

// ── Helpers ──
GridZone zone_from_dpad(bool u,bool d,bool l,bool r) {
    if(u&&l) return ZoneUL;
    if(u&&r) return ZoneUR;
    if(d&&l) return ZoneDL;
    if(d&&r) return ZoneDR;
    if(u) return ZoneU;
    if(d) return ZoneD;
    if(l) return ZoneL;
    if(r) return ZoneR;
    return ZoneC;
}
bool all_dpad_released(App* a) { return !a->dpad[0]&&!a->dpad[1]&&!a->dpad[2]&&!a->dpad[3]; }
char to_upper_ascii(char c) { return (c>='a'&&c<='z')?c-'a'+'A':c; }

void append_char(App* a, char c) {
    if(a->text_len<TEXT_BUF_SIZE-1){
        if(a->shift||a->caps_lock) c=to_upper_ascii(c);
        a->text[a->text_len++]=c; a->text[a->text_len]=0;
        if(a->shift&&!a->caps_lock) a->shift=0;
    }
}
void backspace(App* a) { if(a->text_len) a->text[--a->text_len]=0; }

const ZoneDef* current_zones(App* a) {
    switch(a->mode) {
        case ModeCaps:    return zones_caps;
        case ModeSymbols: return zones_symbols;
        case ModeDigits:  return zones_digits;
        default:          return zones_letters;
    }
}
void return_to_grid(App* a) { a->state=StateGrid; }

void do_action(App* a, SlotType t, char ch) {
    switch(t){
        case ActChar:        if(ch) append_char(a,ch); return_to_grid(a); return;
        case ActSpace:       append_char(a,' '); return_to_grid(a); return;
        case ActBackspace:   backspace(a); return_to_grid(a); return;
        case ActEnter:       append_char(a,'\n'); return_to_grid(a); return;
        case ActShift:
            if(a->caps_lock) a->caps_lock=0;
            else if(a->shift){a->shift=0;a->caps_lock=1;} else a->shift=1;
            return_to_grid(a); return;
        case ActCapsLock: a->mode=ModeCaps; return_to_grid(a); return;
        case ActUncaps:   a->caps_lock=0; a->shift=0; return_to_grid(a); return;
        case ActModeLetters: a->mode=ModeLetters; return_to_grid(a); return;
        case ActModeCaps:    a->mode=ModeCaps; return_to_grid(a); return;
        case ActModeSymbols: a->mode=ModeSymbols; return_to_grid(a); return;
        case ActModeDigits:  a->mode=ModeDigits; return_to_grid(a); return;
        case ActQuickDigits: a->state=StateGrid; a->mode=ModeDigits; a->cursor=ZoneNone; return;
        case ActSettings:
            a->state=StateSettings; a->settings_page=0; a->settings_selector=-1; return;
        case ActExit: a->running=0; return;
    }
}

// ── Settings persistence ──
void settings_load(App* a) {
    SettingsData dflt = SETTINGS_DEFAULT;
    a->settings = dflt;
    Storage* s = furi_record_open(RECORD_STORAGE);
    File* f = storage_file_alloc(s);
    if(storage_file_open(f, SETTINGS_PATH, FSAM_READ, FSOM_OPEN_EXISTING)) {
        char buf[128]; uint16_t r = storage_file_read(f, buf, sizeof(buf)-1);
        if(r > 0) {
            buf[r] = 0;
            int gox,goy,gcw,gch, cox,coy,ccw,cch,cgap;
            int n = sscanf(buf, "%d %d %d %d %d %d %d %d %d",
                &gox,&goy,&gcw,&gch, &cox,&coy,&ccw,&cch,&cgap);
            if(n == 9) {
                a->settings.grid_ox=gox; a->settings.grid_oy=goy;
                a->settings.grid_cw=gcw; a->settings.grid_ch=gch;
                a->settings.cell_ox=cox; a->settings.cell_oy=coy;
                a->settings.cell_cw=ccw; a->settings.cell_ch=cch;
                a->settings.cell_gap=cgap;
            }
        }
    }
    storage_file_close(f); storage_file_free(f);
    furi_record_close(RECORD_STORAGE);
}

void settings_save(App* a) {
    Storage* s = furi_record_open(RECORD_STORAGE);
    storage_common_mkdir(s, SETTINGS_DIR);
    File* f = storage_file_alloc(s);
    if(storage_file_open(f, SETTINGS_PATH, FSAM_WRITE, FSOM_CREATE_ALWAYS)) {
        char buf[128];
        snprintf(buf,sizeof(buf), "%d %d %d %d %d %d %d %d %d",
            a->settings.grid_ox, a->settings.grid_oy,
            a->settings.grid_cw, a->settings.grid_ch,
            a->settings.cell_ox, a->settings.cell_oy,
            a->settings.cell_cw, a->settings.cell_ch,
            a->settings.cell_gap);
        storage_file_write(f, buf, strlen(buf));
    }
    storage_file_close(f); storage_file_free(f);
    furi_record_close(RECORD_STORAGE);
}