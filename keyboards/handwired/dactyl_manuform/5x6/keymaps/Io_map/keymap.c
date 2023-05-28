#include QMK_KEYBOARD_H
//layers
enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
};
 
 


//combo names
enum combos {
    F_C_LAYER,
    SHIFT_R_E_RESET,
    };

// Combo swithces
const uint16_t PROGMEM layerFC[] = {KC_F, KC_C, COMBO_END};
const uint16_t PROGMEM reset[] = {KC_R, KC_E,KC_LSFT, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
 [F_C_LAYER] = COMBO(layerFC, TO(_RAISE)),
 [SHIFT_R_E_RESET] = COMBO(reset, QK_BOOT),
 };


enum tap_dances {
    TD_ESC_CAPS,
    TD_BRACKET,
    TD_F5_F2,
    TD_BACFORSHLAS,
    TD_DMP,
    TD_UPN,
};

static int dmp_tap_count = 0;
static int upn_tap_count = 0;

void dmp_finished(tap_dance_state_t *state, void *user_data) {
    dmp_tap_count = state->count;
    switch (dmp_tap_count) {
        case 1:
            register_code(KC_VOLD);
            break;
        case 2:
            register_code(KC_MUTE);
            break;
        case 3:
            register_code(KC_MPRV);
            break;
    }
}

void dmp_reset(tap_dance_state_t *state, void *user_data) {
    switch (dmp_tap_count) {
        case 1:
            unregister_code(KC_VOLD);
            break;
        case 2:
            unregister_code(KC_MUTE);
            break;
        case 3:
            unregister_code(KC_MPRV);
            break;
    }
    dmp_tap_count = 0;
}

void upn_finished(tap_dance_state_t *state, void *user_data) {
    upn_tap_count = state->count;
    switch (upn_tap_count) {
        case 1:
            register_code(KC_VOLU);
            break;
        case 2:
            register_code(KC_MPLY);
            break;
        case 3:
            register_code(KC_MNXT);
            break;
    }
}

void upn_reset(tap_dance_state_t *state, void *user_data) {
    switch (upn_tap_count) {
        case 1:
            unregister_code(KC_VOLU);
            break;
        case 2:
            unregister_code(KC_MPLY);
            break;
        case 3:
            unregister_code(KC_MNXT);
            break;
    }
    upn_tap_count = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [TD_BRACKET] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
    [TD_F5_F2] = ACTION_TAP_DANCE_DOUBLE(KC_F2 , KC_F5),
    [TD_BACFORSHLAS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
    [TD_DMP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dmp_finished, dmp_reset),
    [TD_UPN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, upn_finished, upn_reset),
};

//custom names
enum custom_keycodes {
    MAIL = SAFE_RANGE,
    GR_LAYER,
    QWERTY_LAYER
};

//Macros
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MAIL :
        if (record->event.pressed) {
            SEND_STRING("ioakeim.sogiakas@gmail.com");
        } return false;
        case GR_LAYER:
            if (record->event.pressed) {
                register_code(KC_LALT);
                register_code(KC_LSFT);
            } else {
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
            }
            return false;

            case QWERTY_LAYER:
            if (record->event.pressed) {
                register_code(KC_LALT);
                register_code(KC_LSFT);

            } else {
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
            }
            return false;
            }

    return true;
}

//Keymap /
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//QWERTY
    [_QWERTY] = LAYOUT_5x6(
        TD(TD_ESC_CAPS) , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_DEL,
        KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS,
        KC_RSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                         KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
        KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                         KC_N  , KC_M  ,KC_COMM,KC_DOT ,TD(TD_BACFORSHLAS),GR_LAYER,
                         TD(TD_DMP),TD(TD_UPN),                                                       TD(TD_BRACKET), KC_EQL,
                                         KC_SPC  , KC_LSFT ,                        KC_ENT,KC_BSPC,
                                         KC_LALT , MAIL ,                         KC_UP,  KC_DOWN,
                                         KC_LGUI , TD(TD_F5_F2) ,                        KC_LEFT, KC_RIGHT
    ),

    [_LOWER] = LAYOUT_5x6(
        KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                        KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL,
        _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,_______,KC_PLUS,
        _______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,KC_LPRN,                        KC_RPRN, KC_P4 , KC_P5 , KC_P6 ,KC_MINS,KC_PIPE,
        _______,_______,_______,_______,_______,_______,                        _______, KC_P1 , KC_P2 , KC_P3 ,KC_EQL ,KC_UNDS,
                                                _______,KC_PSCR,            _______, KC_P0,
                                                _______,_______,            _______,_______,
                                                _______,_______,            _______,_______,
                                            TO(_QWERTY),TO(_LOWER),         _______,_______

    ),

    [_RAISE] = LAYOUT_5x6(
          KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
          _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC,_______,KC_NUM,KC_INS ,KC_SCRL,KC_MUTE,
          _______,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_LPRN,                        KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_VOLU,
          _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,KC_VOLD,
                                                  _______,_______,            KC_EQL ,_______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______,
                                                  TO(_QWERTY),TO(_LOWER),            _______,_______
    ),
//greece
   
};

