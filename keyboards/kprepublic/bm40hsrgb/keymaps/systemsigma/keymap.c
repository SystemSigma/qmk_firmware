// #include QMK_:KEYBOARD_H
#include <keyboards/bm40hsrgb/bm40hsrgb.h>
// #include "quantum.h"
#include "snake.h"

enum layers {
L_BASE = 0,
L_NAV,
L_NUM,
L_RGB,
L_FUNC,
L_SNAKE,
};

char quarter_count = 0;
char half_count = 0;

enum custom_keycodes {
  QUARTER = SAFE_RANGE,
  HALF,
  SNAKE,
  DIRRGHT,
  DIRUP,
  DIRLEFT,
  DIRDOWN
};

enum {
	TD_ESC_CAPS
};

qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS)
};

//custom rgb
void rgb_matrix_indicators_user(void) {

    //reset key  indicator red
    if(IS_LAYER_ON(L_RGB)) {
        rgb_matrix_set_color(0, 255, 0, 0);
    }
}

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case MYNAME:
//             if (record->event.pressed) {
//                 // when keycode QMKBEST is pressed
//                 SEND_STRING("Andrea Franceschetti");
//             } else {
//                 // when keycode QMKBEST is released
//             }
//             break;
//     }
//     return true;
// }


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DIRUP:
      if (snake_status.last_moved_direction != DIRECTION_DOWN) {
        snake_status.direction = DIRECTION_UP;
      }
      return false;
      break;
    case DIRDOWN:
      if (snake_status.last_moved_direction != DIRECTION_UP) {
        snake_status.direction = DIRECTION_DOWN;
      }
      return false;
      break;
    case DIRLEFT:
      if (snake_status.last_moved_direction != DIRECTION_RIGHT) {
        snake_status.direction = DIRECTION_LEFT;
      }
      return false;
      break;
    case DIRRGHT:
      if (snake_status.last_moved_direction != DIRECTION_LEFT) {
         snake_status.direction = DIRECTION_RIGHT;
      }

      // corner
      if (record->event.pressed) {
        quarter_count += 1;
      } else {
        quarter_count -= 1;
      }
      if (quarter_count == 4) {
        reset_keyboard();
      }
      return false;
      break;
    case QUARTER:
      // corner
      if (record->event.pressed) {
        quarter_count += 1;
      } else {
        quarter_count -= 1;
      }
      if (quarter_count == 4) {
        reset_keyboard();
      }
      return false;
      break;
    case HALF:
      if (record->event.pressed) {
        half_count += 1;
      } else {
        half_count -= 1;
      }
      if (half_count == 2) {
        layer_move(L_RGB);
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
      }
      return false;
      break;
    case SNAKE:
        layer_move(L_SNAKE);
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_SNAKE);
        snake_init();
      return false;
      break;
  }
  return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[L_BASE] = LAYOUT_planck_mit
		(KC_TAB,    KC_Q,         KC_W,      KC_E,       KC_R,       KC_T,     KC_Y,     KC_U,          KC_I,       KC_O,        KC_P,       KC_BSPC,
		 TD(TD_ESC_CAPS),    KC_A,         KC_S,      KC_D,       KC_F,       KC_G,     KC_H,     KC_J,          KC_K,       KC_L,        KC_SCLN,    KC_QUOT,
		 KC_LSFT,   KC_Z,         KC_X,      KC_C,       KC_V,       KC_B,     KC_N,     KC_M,          KC_COMM,    KC_DOT,      KC_SLSH,    KC_RSFT,
		 KC_LCTL,   KC_LGUI,      KC_LALT,   MO(L_FUNC), MO(L_NUM),        KC_SPC,       MO(L_NAV),     KC_EQL,     TG(L_RGB),   KC_RGUI,    KC_ENT),

	[L_NAV] = LAYOUT_planck_mit
		(KC_TRNS,     KC_WSCH,      KC_WFWD,   KC_END,    KC_BTN1,    KC_VOLU,  KC_WH_L,  KC_WH_D,     KC_WH_U,   KC_WH_R,  KC_PSCR,    KC_TRNS,
		 KC_NO,       LALT(KC_TAB), KC_WBAK,   KC_HOME,   KC_FIND,    KC_VOLD,  KC_LEFT,  KC_DOWN,     KC_UP,     KC_RGHT,  KC_NO,      KC_NO,
		 KC_NO,       KC_UNDO,      KC_CUT,    KC_COPY,   KC_PSTE,    KC_MUTE,  KC_MS_L,  KC_MS_D,     KC_MS_U,   KC_MS_R,  KC_NO,      KC_NO,
		 KC_TRNS,     KC_TRNS,      KC_TRNS,   KC_TRNS,   KC_DEL,        KC_TRNS,         KC_TRNS,     KC_NO,     KC_TRNS,  KC_TRNS,    KC_TRNS),

	[L_NUM] = LAYOUT_planck_mit
		(KC_TILD,   KC_EXLM,      KC_AT,     KC_HASH,   KC_DLR,     KC_PERC,  KC_CIRC,  KC_AMPR,   KC_ASTR,    KC_LPRN,  KC_RPRN,  KC_PIPE,
		 KC_GRV,    KC_1,         KC_2,      KC_3,      KC_4,       KC_5,     KC_6,     KC_7,      KC_8,       KC_9,     KC_0,      KC_BSLS,
		 KC_NO,     KC_MINUS,     KC_LCBR,   KC_LBRC,   KC_LPRN,    KC_NO,    KC_NO,    KC_RPRN,   KC_RBRC,    KC_RCBR,  KC_PLUS,     KC_NO,
		 KC_TRNS,   KC_TRNS,      KC_TRNS,   KC_NO,     KC_TRNS,         KC_TRNS,       KC_UNDS,   KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS),

	[L_RGB] = LAYOUT_planck_mit
		(RESET,     KC_NO, 	  KC_NO,     KC_NO,     KC_NO,       KC_NO,    KC_NO,    KC_NO,     KC_ASUP,     RGB_HUI,     RGB_SAI,   RGB_VAI,
		 DEBUG,     KC_NO,        KC_NO,     KC_NO,     KC_NO,       KC_NO,    KC_NO,    KC_NO,     KC_ASDN,     RGB_HUD,     RGB_SAD,   RGB_VAD,
		 KC_ASTG,   KC_NO,        KC_NO,     KC_NO,     KC_NO,       KC_NO,    KC_NO,    KC_NO,     KC_ASRP,     KC_NO,       KC_NO,     KC_NO,
		 SNAKE,   KC_TRNS,      KC_TRNS,   KC_TRNS,   KC_TRNS,           KC_NO,       KC_TRNS,   KC_TRNS,   TG(L_RGB),   RGB_MOD,   RGB_TOG),

	[L_FUNC] = LAYOUT_planck_mit
		(KC_NO,     KC_NO,        KC_NO,      KC_NO,    KC_NO,       KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,     KC_NO,
		 KC_F12,    KC_F1,        KC_F2,      KC_F3,    KC_F4,       KC_F5,    KC_F6,    KC_F7,     KC_F8,    KC_F9,    KC_F10,    KC_F11,
		 KC_NO,     KC_NO,        KC_NO,      KC_NO,    KC_NO,       KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,     KC_NO,
		 KC_TRNS,   KC_TRNS,      KC_TRNS,    KC_NO,    KC_TRNS,         KC_TRNS,        KC_TRNS,   KC_NO,    KC_TRNS,  KC_TRNS,   KC_TRNS),

    [L_SNAKE] = LAYOUT_planck_mit
        (QUARTER, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QUARTER, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, HALF,    XXXXXXX, XXXXXXX, HALF,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DIRUP,   XXXXXXX, \
        QUARTER, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,      XXXXXXX, XXXXXXX, DIRLEFT, DIRDOWN, DIRRGHT \
        ),

};

