#include "satan.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _FUNC 1
#define _EDIT 2 // edit layer
#define _ESHFT 3 // edit layer shifted (selecting)

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define KC_CUT LCTL(KC_X)
#define KC_COPY LCTL(KC_C)
#define KC_PASTE LCTL(KC_V)

#define P_WORD  LCTL(KC_LEFT) // prev word
#define N_WORD  LCTL(KC_RIGHT) // next word
#define B_LINE  KC_HOME // start of line
#define E_LINE  KC_END // end of line

enum custom_keycodes {
	M_ARR = SAFE_RANGE, // =>
	M_TRPLTICKS, // ```
	M_FUNC, // function
	M_CONST, // const
	M_VAR, // var
	M_LET, // let
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// DEFAULT LAYER 0
	[_BASE] = KEYMAP_ANSI(
	KC_GESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,  KC_EQL,   KC_BSLS, \
	KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,  KC_RBRC,  KC_BSPACE, \
	KC_LCTL, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,            KC_ENT,  \
	KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,            KC_RSFT, \
	XXXXXXX, KC_LGUI,KC_LALT,                KC_SPC,                                 KC_RALT,MO(_FUNC),TT(_EDIT),XXXXXXX),

	// FUNCTION LAYER
	[_FUNC] = KEYMAP_ANSI(
	M_TRPLTICKS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,  KC_F11,  KC_F12,   KC_TILD, \
	KC_TAB,     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_PSCR, XXXXXXX, XXXXXXX,  KC_DEL, \
	KC_LCTL,    M_ARR,  XXXXXXX,XXXXXXX,M_FUNC, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,M_LET,  XXXXXXX, XXXXXXX,           KC_ENT,  \
	KC_LSFT,            XXXXXXX,XXXXXXX,M_CONST,M_VAR,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX,           KC_RSFT, \
	XXXXXXX,    KC_LGUI,KC_LALT,                KC_DEL,                                 KC_RALT, MO(_FUNC),XXXXXXX, XXXXXXX),

	// EDIT LAYER
	[_EDIT] = KEYMAP_ANSI(
	TO(_BASE), B_LINE, E_LINE,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, KC_7,   KC_8,   KC_9,   KC_PLUS, XXXXXXX, XXXXXXX,  KC_TILD, \
	KC_TAB,    P_WORD, KC_UP,   N_WORD,   KC_PGUP, XXXXXXX, XXXXXXX, KC_4,   KC_5,   KC_6,   KC_MINS, XXXXXXX, XXXXXXX,  KC_DEL, \
	KC_LCTL,   KC_LEFT,KC_DOWN, KC_RIGHT, KC_PGDN, XXXXXXX, XXXXXXX, KC_1,   KC_2,   KC_3,   KC_ASTR, XXXXXXX,           KC_ENT,  \
	TG(_ESHFT),           XXXXXXX, KC_CUT,   KC_COPY, KC_PASTE,XXXXXXX, XXXXXXX,KC_0,   KC_COMM,KC_DOT,  KC_SLSH,           KC_RSFT, \
	XXXXXXX,   KC_LGUI,XXXXXXX,                    KC_DEL,                                   XXXXXXX, XXXXXXX, TT(_EDIT),XXXXXXX),

	// MARK LAYER (SHIFTED EDIT)
	[_ESHFT] = KEYMAP_ANSI(
	TO(_EDIT), LSFT(B_LINE), LSFT(E_LINE),  XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, KC_7,   KC_8,   KC_9,   KC_PLUS, XXXXXXX, XXXXXXX,  KC_TILD, \
	KC_TAB,    LSFT(P_WORD), LSFT(KC_UP),   LSFT(N_WORD),   KC_PGUP, XXXXXXX, XXXXXXX, KC_4,   KC_5,   KC_6,   KC_MINS, XXXXXXX, XXXXXXX,  KC_DEL, \
	KC_LCTL,   LSFT(KC_LEFT),LSFT(KC_DOWN), LSFT(KC_RIGHT), KC_PGDN, XXXXXXX, XXXXXXX, KC_1,   KC_2,   KC_3,   KC_ASTR, XXXXXXX,           KC_ENT,  \
	TG(_ESHFT),              XXXXXXX,       KC_CUT,         KC_COPY, KC_PASTE,XXXXXXX, XXXXXXX,KC_0,   KC_COMM,KC_DOT,  KC_SLSH,           KC_RSFT, \
	XXXXXXX,   KC_LGUI,      XXXXXXX,                                KC_DEL,                                   XXXXXXX, XXXXXXX, TT(_EDIT),XXXXXXX),
};

bool process_macros(uint16_t keycode, keyrecord_t *record) {
	if (record->event.pressed) {
		switch(keycode) {
			case M_ARR:
				SEND_STRING("=>");
				return false;
				break;
			case M_TRPLTICKS:
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