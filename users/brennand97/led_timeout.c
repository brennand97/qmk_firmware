#include "led_timeout.h"

static uint16_t rout_tg;                        // Timeout Toggle. Toggle idle LED time out on or off
static uint16_t rout_vi;                        // Timeout Value Increase. Increase idle time out before LED disabled
static uint16_t rout_vd;                        // Timeout Value Decrease. Decrease idle time out before LED disabled
static uint16_t rout_fm;                        // RGB timeout fast mode toggle

static uint16_t idle_timer;                     // Idle LED timeout timer
static uint8_t idle_second_counter;             // Idle LED seconds counter, counts seconds not milliseconds
static uint8_t key_event_counter;               // This counter is used to check if any keys are being held

void led_timeout_init(uint16_t rout_tg_keycode, uint16_t rout_vi_keycode, uint16_t rout_vd_keycode, uint16_t rout_fm_keycode) {
    rout_tg = rout_tg_keycode;
    rout_vi = rout_vi_keycode;
    rout_vd = rout_vd_keycode;
    rout_fm = rout_fm_keycode;

    idle_second_counter = 0;                            // Counter for number of seconds keyboard has been idle.
    key_event_counter = 0;                              // Counter to determine if keys are being held, neutral at 0.
    rgb_time_out_seconds = RGB_DEFAULT_TIME_OUT;        // RGB timeout initialized to its default configure in keymap.h
    rgb_time_out_enable = false;                        // Disable RGB timeout by default. Enable using toggle key.
    rgb_time_out_user_value = false;                    // Has to have the same initial value as rgb_time_out_enable.
    rgb_enabled_flag = true;                            // Initially, keyboard RGB is enabled. Change to false config.h initializes RGB disabled.
    rgb_time_out_fast_mode_enabled = false;             // RGB timeout fast mode disabled initially.
    rgb_time_out_saved_flag = rgb_matrix_get_flags();   // Save RGB matrix state for when keyboard comes back from ide.
}

void led_timeout_tick(void) {
    if(rgb_time_out_enable && rgb_enabled_flag) {
        // If the key event counter is not zero then some key was pressed down but not released, thus reset the timeout counter.
        if (key_event_counter) {
            idle_second_counter = 0;
        } else if (timer_elapsed(idle_timer) > MILLISECONDS_PER_SECOND) {
            idle_second_counter++;
            idle_timer = timer_read();
        }

        if (idle_second_counter >= rgb_time_out_seconds) {
            rgb_time_out_saved_flag = rgb_matrix_get_flags();
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            rgb_enabled_flag = false;
            idle_second_counter = 0;
        }
    }
}

bool led_timeout_event(uint16_t keycode, keyrecord_t *record) {
    // Increment key event counter for every press and decrement for every release.
    if (record->event.pressed) {
        key_event_counter++;
    } else {
        key_event_counter--;
    }

    if (rgb_time_out_enable) {
        idle_timer = timer_read();
        // Reset the seconds counter. Without this, something like press> leave x seconds> press, would be x seconds on the effective counter not 0 as it should.
        idle_second_counter = 0;
        if (!rgb_enabled_flag) {
            rgb_matrix_enable_noeeprom();
            rgb_matrix_set_flags(rgb_time_out_saved_flag);
            rgb_enabled_flag = true;
        }
    }

    if (record->event.pressed) {
        if (keycode == rout_tg) {
            // Toggle idle LED timeout on or off
            rgb_time_out_enable = !rgb_time_out_enable;
            rgb_time_out_user_value = rgb_time_out_enable;
            return false;
        } else if (keycode == rout_vi) {
            // Increase idle LED timeout value in seconds
            // Only increase if current value is lower than RGB_TIME_OUT_MAX. Don't care what value the result will be
            // Modity RGB_TIME_OUT_STEP for bigger or smaller increments
            if (!rgb_time_out_fast_mode_enabled && rgb_time_out_seconds <= RGB_TIME_OUT_MAX) {
                rgb_time_out_seconds += RGB_TIME_OUT_STEP;
            }
            return false;
        } else if (keycode == rout_vd) {
            // Decrease idle LED timeout value in seconds
            // Only decrease if current value is higher than minimum value and the result is larger than zero
            // Modity RGB_TIME_OUT_STEP for bigger or smaller decrements
            if (!rgb_time_out_fast_mode_enabled && rgb_time_out_seconds > RGB_TIME_OUT_MIN) {
                rgb_time_out_seconds -= RGB_TIME_OUT_STEP;
            }
            return false;
        } else if (keycode == rout_fm) {
            if (rgb_time_out_fast_mode_enabled) {
                rgb_time_out_seconds = rgb_time_out_saved_seconds;
            } else {
                rgb_time_out_saved_seconds = rgb_time_out_seconds;
                rgb_time_out_seconds = RGB_FAST_MODE_TIME_OUT;
            }
            rgb_time_out_fast_mode_enabled = !rgb_time_out_fast_mode_enabled;
            return false;
        }
    }

    return true;
}
