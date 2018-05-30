#include "satan.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _GAME 1 // gaming layer
#define _ESHFT 2 // edit layer shifted (selecting)
#define _EDIT 3 // edit layer
#define _CHORD 5
#define _FUNC 10
#define _MOUSE 15 // edit layer shifted (selecting)

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define KC_CUT LCTL(KC_X)
#define KC_COPY LCTL(KC_C)
#define KC_PASTE LCTL(KC_V)

#define P_WORD  LCTL(KC_LEFT) // prev word
#define N_WORD  LCTL(KC_RIGHT) // next word
#define B_LINE  KC_HOME // start of line
#define E_LINE  KC_END // end of line

#define KC_INDNT KC_TAB
#define KC_UNIDNT LSFT(KC_TAB)

#define LT_ENTFN LT(_FUNC, KC_ENT) // enter on tap, hold for func layer

#define LT_SPCMOUS LT(_MOUSE, KC_SPACE) // space on tap, hold for mouse layer
#define MOUS_UP KC_MS_UP
#define MOUS_DN KC_MS_DOWN
#define MOUS_LT KC_MS_LEFT
#define MOUS_RT KC_MS_RIGHT
#define MOUS_B1 KC_MS_BTN1
#define MOUS_B2 KC_MS_BTN2
#define MOUS_WU KC_MS_WH_UP
#define MOUS_WD KC_MS_WH_DOWN
#define MOUS_A1 KC_MS_ACCEL0
#define MOUS_A2 KC_MS_ACCEL1
#define MOUS_A3 KC_MS_ACCEL2


enum custom_keycodes {
	M_ARR = SAFE_RANGE, // =>
	M_TRPTICKS, // ```
	M_FUNC, // function
	M_CONST, // const
	M_VAR, // var
	M_LET, // let

	CHORDING_RANGE
};

// chording shit
enum chords {
	CRD_A = CHORDING_RANGE,
	CRD_S,
	CRD_E,
	CRD_T,
	CRD_N,
	CRD_I,
	CRD_O,
	CRD_P,
};
static uint16_t chording_state = 0;
static uint8_t chording_keys_down = 0;

typedef struct {
	uint16_t bitmask;
	char* str;
}chord_string;

typedef struct {
	uint16_t bitmask;
	uint16_t keycode;
}chord_keycode;

#define CRD_BM(kc) (1 << (kc - CHORDING_RANGE))

uint16_t get_chording_bitmask(uint16_t keycode);
uint16_t get_chording_bitmask(uint16_t keycode) {
	return 1 << (keycode - CHORDING_RANGE);
}

#define CHORD_KC_TOTAL 34
const chord_keycode chording_kc[CHORD_KC_TOTAL] = {
	{CRD_BM(CRD_A), KC_A},
	{CRD_BM(CRD_S), KC_S},
	{CRD_BM(CRD_E), KC_E},
	{CRD_BM(CRD_T), KC_T},
	{CRD_BM(CRD_N), KC_N},
	{CRD_BM(CRD_I), KC_I},
	{CRD_BM(CRD_O), KC_O},
	{CRD_BM(CRD_P), KC_P},

	{CRD_BM(CRD_A) | CRD_BM(CRD_S), KC_EXCLAIM},
	{CRD_BM(CRD_A) | CRD_BM(CRD_E), KC_AT},
	{CRD_BM(CRD_A) | CRD_BM(CRD_T), KC_Q},
	{CRD_BM(CRD_A) | CRD_BM(CRD_N), KC_H},
	{CRD_BM(CRD_A) | CRD_BM(CRD_I), KC_K},
	{CRD_BM(CRD_A) | CRD_BM(CRD_O), KC_Z},
	
	{CRD_BM(CRD_S) | CRD_BM(CRD_E), KC_X},
	{CRD_BM(CRD_S) | CRD_BM(CRD_T), KC_DOUBLE_QUOTE},
	{CRD_BM(CRD_S) | CRD_BM(CRD_N), KC_M},
	{CRD_BM(CRD_S) | CRD_BM(CRD_I), KC_W},
	{CRD_BM(CRD_S) | CRD_BM(CRD_O), KC_L},

	{CRD_BM(CRD_E) | CRD_BM(CRD_T), KC_V},
	{CRD_BM(CRD_E) | CRD_BM(CRD_N), KC_U},
	{CRD_BM(CRD_E) | CRD_BM(CRD_I), KC_D},
	{CRD_BM(CRD_E) | CRD_BM(CRD_O), KC_C},

	{CRD_BM(CRD_T) | CRD_BM(CRD_N), KC_R},
	{CRD_BM(CRD_T) | CRD_BM(CRD_I), KC_G},
	{CRD_BM(CRD_T) | CRD_BM(CRD_O), KC_B},
	{CRD_BM(CRD_T) | CRD_BM(CRD_P), KC_F},

	{CRD_BM(CRD_N) | CRD_BM(CRD_I), KC_COMMA},
	{CRD_BM(CRD_N) | CRD_BM(CRD_O), KC_Y},
	{CRD_BM(CRD_N) | CRD_BM(CRD_P), KC_J},

	{CRD_BM(CRD_I) | CRD_BM(CRD_O), KC_DOT},

	{CRD_BM(CRD_O) | CRD_BM(CRD_P), KC_QUESTION},

	{CRD_BM(CRD_A)|CRD_BM(CRD_S)|CRD_BM(CRD_E)|CRD_BM(CRD_T), KC_BSPACE},
	{CRD_BM(CRD_N)|CRD_BM(CRD_I)|CRD_BM(CRD_O)|CRD_BM(CRD_P), KC_ENTER},
};

#define CHORD_STR_TOTAL 4
const chord_string chording_str[CHORD_STR_TOTAL] = {
	{CRD_BM(CRD_A) | CRD_BM(CRD_P), SS_RALT("u")},
	{CRD_BM(CRD_S) | CRD_BM(CRD_P),  SS_RALT("a")},
	{CRD_BM(CRD_E) | CRD_BM(CRD_P),  SS_RALT("o")},
	{CRD_BM(CRD_I) | CRD_BM(CRD_P),  SS_RALT("s")},
};


bool process_chords_kc(uint16_t state) {
	for(int i = 0; i < CHORD_KC_TOTAL; i++) {
		uint16_t bitmask = chording_kc[i].bitmask;

		if (state == bitmask) {
			//todo: chording_kc[i].keycode senden irgendwie
			uint16_t keycode = chording_kc[i].keycode;
			register_code16(keycode);
  			unregister_code16(keycode);
			return false;
		}
	}
	return true;
}

bool process_chords_str(uint16_t state) {
	for(int i = 0; i < CHORD_STR_TOTAL; i++) {
		uint16_t bitmask = chording_str[i].bitmask;

		if (state == bitmask) {
			send_string(chording_str[i].str);
			return false;
		}
	}
	return true;
}

// bool process_chords_fn(uint16_t state) {
// 	for(int i = 0; i < CHORD_FN_TOTAL; i++) {
// 		uint16_t bitmask = chording_fn[i].bitmask;

// 		if (state == bitmask) {
// 			send_string(.str);
// 			return false;
// 		}
// 	}
// 	return true;
// }

bool process_chords(uint16_t keycode, keyrecord_t *record) {
	if (keycode >= CRD_A && keycode <= CRD_P) { // is actual a chording key
		if (record->event.pressed) {
			chording_keys_down++;
		}
		else { // no longer pressed
			chording_keys_down--;
			chording_state |= get_chording_bitmask(keycode);

			if (chording_keys_down <= 0) {
				chording_keys_down = 0;
				uint16_t state = chording_state;
				chording_state = 0;
				if (!process_chords_kc(state)) return false;
				if (!process_chords_str(state)) return false;
			}
		}
		return false;
	}

	return true;
}
// end chording shit

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// DEFAULT LAYER 0
	[_BASE] = KEYMAP_ANSI(
	KC_GESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,     KC_MINS, KC_EQL,   KC_BSLS, \
	KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,     KC_LBRC, KC_RBRC,  KC_BSPACE, \
	KC_LCTL, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,  KC_QUOT,           LT_ENTFN,  \
	KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT,   KC_SLSH,           KC_RSFT, \
	XXXXXXX, KC_LGUI,KC_LALT,                        LT_SPCMOUS,                     TO(_ESHFT),KC_RALT,XXXXXXX,  XXXXXXX),

	// GAMING LAYER (Nearly standard QWERTY)
	[_GAME] = KEYMAP_ANSI(
	KC_GESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,    KC_MINS,KC_EQL,   KC_BSLS, \
	KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,    KC_LBRC,KC_RBRC,  KC_BSPACE, \
	KC_LCTL, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_QUOT,          LT_ENTFN,  \
	KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT,  KC_SLSH,          KC_RSFT, \
	XXXXXXX, XXXXXXX,KC_LALT,                        KC_SPACE,                     	 XXXXXXX, KC_RALT,XXXXXXX,  XXXXXXX),

	// MARK LAYER (SHIFTED EDIT)
	[_ESHFT] = KEYMAP_ANSI(
	TO(_BASE), LSFT(B_LINE), LSFT(E_LINE),  XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, KC_7,   KC_8,   KC_9,     KC_PLUS,  XXXXXXX, XXXXXXX,  KC_DEL, \
	KC_TAB,    LSFT(P_WORD), LSFT(KC_UP),   LSFT(N_WORD),   KC_PGUP, XXXXXXX, XXXXXXX, KC_4,   KC_5,   KC_6,     KC_MINS,  XXXXXXX, XXXXXXX,  KC_BSPACE, \
	KC_LCTL,   LSFT(KC_LEFT),LSFT(KC_DOWN), LSFT(KC_RIGHT), KC_PGDN, XXXXXXX, XXXXXXX, KC_1,   KC_2,   KC_3,     KC_ASTR,  XXXXXXX,           LT_ENTFN,  \
	KC_LSFT,                 XXXXXXX,       KC_CUT,         KC_COPY, KC_PASTE,XXXXXXX, XXXXXXX,KC_0,   KC_UNIDNT,KC_INDNT, KC_SLSH,           KC_RSFT, \
	XXXXXXX,   KC_LGUI,      XXXXXXX,                                LT_SPCMOUS,                                 TG(_EDIT),XXXXXXX, XXXXXXX,  XXXXXXX),

	// EDIT LAYER
	[_EDIT] = KEYMAP_ANSI(
	TO(_BASE), B_LINE, E_LINE,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, KC_7,   KC_8, KC_9,     KC_PLUS,  XXXXXXX, XXXXXXX,  KC_DEL, \
	KC_TAB,    P_WORD, KC_UP,   N_WORD,   KC_PGUP, XXXXXXX, XXXXXXX, KC_4,   KC_5, KC_6,     KC_MINS,  XXXXXXX, XXXXXXX,  KC_BSPACE, \
	KC_LCTL,   KC_LEFT,KC_DOWN, KC_RIGHT, KC_PGDN, XXXXXXX, XXXXXXX, KC_1,   KC_2, KC_3,     KC_ASTR,  XXXXXXX,           LT_ENTFN,  \
	KC_LSFT,           XXXXXXX, KC_CUT,   KC_COPY, KC_PASTE,XXXXXXX, XXXXXXX,KC_0, KC_UNIDNT,KC_INDNT, KC_SLSH,           KC_RSFT, \
	XXXXXXX,   KC_LGUI,XXXXXXX,                    LT_SPCMOUS,                               TG(_EDIT),XXXXXXX, XXXXXXX,  XXXXXXX),

	// FUNCTION LAYER
	[_FUNC] = KEYMAP_ANSI(
	KC_GRAVE,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,    KC_F10,   KC_F11,  KC_F12,   KC_DEL, \
	M_TRPTICKS, CRD_A,  CRD_S,  CRD_E,CRD_T,XXXXXXX,XXXXXXX,CRD_N,CRD_I,CRD_O,  CRD_P,  RALT(KC_U), XXXXXXX,  KC_BSPACE, \
	KC_LCTL,    M_ARR,  XXXXXXX,XXXXXXX,M_FUNC, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,M_LET,    XXXXXXX,  XXXXXXX,           LT_ENTFN,  \
	KC_LSFT,            XXXXXXX,XXXXXXX,M_CONST,M_VAR,  XXXXXXX,XXXXXXX,XXXXXXX,DF(_GAME),DF(_BASE),DF(_CHORD),           KC_RSFT, \
	XXXXXXX,    KC_LGUI,KC_LALT,                KC_DEL,                                   XXXXXXX,  KC_RALT, XXXXXXX,  XXXXXXX),

		// FUNCTION LAYER
	[_CHORD] = KEYMAP_ANSI(
	KC_GRAVE,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,    KC_F10,   KC_F11,  KC_F12,   KC_DEL, \
	M_TRPTICKS, CRD_A,  CRD_S,  CRD_E,  CRD_T,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,CRD_N,    CRD_I,    CRD_O,   CRD_P,   KC_BSPACE, \
	KC_LCTL,    M_ARR,  XXXXXXX,XXXXXXX,M_FUNC, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,M_LET,    XXXXXXX,  XXXXXXX,           LT_ENTFN,  \
	KC_LSFT,            XXXXXXX,XXXXXXX,M_CONST,M_VAR,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,           KC_RSFT, \
	XXXXXXX,    KC_LGUI,KC_LALT,                KC_SPACE,                                   KC_LSHIFT,  KC_RALT, XXXXXXX,  XXXXXXX),

	//MOUSE LAYER (15)
	[_MOUSE]=KEYMAP_ANSI(
	XXXXXXX,MOUS_A1,MOUS_A2,MOUS_A3,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,\
	XXXXXXX,MOUS_B2,MOUS_UP,MOUS_B1,MOUS_WU,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,\
	XXXXXXX,MOUS_LT,MOUS_DN,MOUS_RT,MOUS_WD,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,		XXXXXXX,\
	XXXXXXX,	    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,		XXXXXXX,\
	XXXXXXX,XXXXXXX,XXXXXXX,                        LT_SPCMOUS,						XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX),
};

bool process_macros(uint16_t keycode, keyrecord_t *record) {
	if (record->event.pressed) {
		switch(keycode) {
			case M_ARR:
				SEND_STRING("=>");
				return false;
				break;
			case M_TRPTICKS:
				SEND_STRING("```");
				return false;
				break;
			case M_FUNC:
				SEND_STRING("function ");
				return false;
				break;
			case M_CONST:
				SEND_STRING("const ");
				return false;
				break;
			case M_VAR:
				SEND_STRING("var ");
				return false;
				break;
			case M_LET:
				SEND_STRING("let ");
				return false;
		}
	}
	return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (!process_macros(keycode, record)) {
		return false;
	}

	if (!process_chords(keycode, record)) {
		return false;
	}

	return true;
}