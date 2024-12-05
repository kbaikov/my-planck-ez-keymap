#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"

enum planck_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
};


enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _LAYER4,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(KC_ESCAPE,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSPC,KC_TAB,KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,LT(4,KC_SCLN),KC_QUOTE,KC_LEFT_SHIFT,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMMA,KC_DOT,KC_SLASH,KC_ENTER,KC_LEFT_CTRL,KC_LEFT_GUI,KC_LEFT_ALT,KC_LEFT_ALT,LOWER,KC_SPACE,KC_NO,RAISE,KC_UP,KC_LEFT,KC_DOWN,KC_RIGHT),

  [_LOWER] = LAYOUT_planck_grid(KC_TILD,KC_EXLM,KC_AT,KC_HASH,KC_DLR,KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_TRANSPARENT,KC_DELETE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_PIPE,KC_PIPE,KC_TRANSPARENT,KC_TRANSPARENT,KC_LBRC,KC_RBRC,KC_EQUAL,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_UNDS,KC_BSLS,KC_TRANSPARENT,KC_TRANSPARENT,KC_LCBR,KC_RCBR,KC_TRANSPARENT,LALT(LCTL(KC_DELETE)),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_BSPC,KC_NO,KC_TRANSPARENT,KC_PAGE_UP,KC_HOME,KC_PGDN,KC_END),

  [_RAISE] = LAYOUT_planck_grid(KC_GRAVE,KC_MS_BTN1,KC_MS_UP,KC_MS_BTN2,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_7,KC_8,KC_9,KC_KP_ASTERISK,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_4,KC_5,KC_6,KC_KP_MINUS,KC_KP_PLUS,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_1,KC_2,KC_3,KC_KP_SLASH,KC_KP_ASTERISK,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_DELETE,KC_NO,KC_TRANSPARENT,KC_0,KC_DOT,KC_COMMA,KC_EQUAL),

  [_ADJUST] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_F7,KC_F8,KC_F9,KC_F10,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_F4,KC_F5,KC_F6,KC_F11,QK_BOOT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_F1,KC_F2,KC_F3,KC_F12,KC_TRANSPARENT,LALT(LCTL(KC_DELETE)),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_LAYER4] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_MS_BTN1,KC_MS_UP,KC_MS_BTN2,KC_TRANSPARENT,KC_TRANSPARENT,KC_PAGE_UP,KC_HOME,KC_UP,KC_END,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_PGDN,KC_LEFT,KC_DOWN,KC_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

};

const uint16_t PROGMEM combo0[] = { KC_J, KC_U, COMBO_END};
const uint16_t PROGMEM combo1[] = { KC_K, KC_I, COMBO_END};
const uint16_t PROGMEM combo2[] = { KC_E, KC_D, COMBO_END};
const uint16_t PROGMEM combo3[] = { KC_R, KC_F, COMBO_END};
const uint16_t PROGMEM combo4[] = { KC_D, KC_C, COMBO_END};
const uint16_t PROGMEM combo5[] = { KC_F, KC_V, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, KC_LPRN),
    COMBO(combo1, KC_RPRN),
    COMBO(combo2, KC_LCBR),
    COMBO(combo3, KC_RCBR),
    COMBO(combo4, KC_LBRC),
    COMBO(combo5, KC_RBRC),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
            
          }
  return true;
}

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo+=1;
            } else {
                muse_tempo-=1;
            }
        }
    } else {
        if (clockwise) {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_DOWN);
            unregister_code(KC_MS_WH_DOWN);
        #else
            register_code(KC_PGDN);
            unregister_code(KC_PGDN);
        #endif
        } else {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_UP);
            unregister_code(KC_MS_WH_UP);
        #else
            register_code(KC_PGUP);
            unregister_code(KC_PGUP);
        #endif
        }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
        return false;
    default:
        return true;
    }
}
#endif

uint8_t layer_state_set_user(uint8_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}



// Custom QMK here
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// Globally defines all keyoverrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&delete_key_override
};