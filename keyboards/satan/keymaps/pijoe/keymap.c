#include "satan.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _GAME 1 // gaming layer
#define _ESHFT 2 // edit layer shifted (selecting)
#define _EDIT 3 // edit layer
#define _FUNC 4
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
};

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
	M_TRPTICKS, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,  KC_PSCR,  XXXXXXX, XXXXXXX,  KC_BSPACE, \
	KC_LCTL,    M_ARR,  XXXXXXX,XXXXXXX,M_FUNC, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,M_LET,    XXXXXXX,  XXXXXXX,           LT_ENTFN,  \
	KC_LSFT,            XXXXXXX,XXXXXXX,M_CONST,M_VAR,  XXXXXXX,XXXXXXX,XXXXXXX,DF(_GAME),DF(_BASE),XXXXXXX,           KC_RSFT, \
	XXXXXXX,    KC_LGUI,KC_LALT,                KC_DEL,                                   XXXXXXX,  KC_RALT, XXXXXXX,  XXXXXXX),

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

	return true;
}