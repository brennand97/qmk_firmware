#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

#define MILLISECONDS_PER_SECOND 1000

// ===================================== Configurable Defaults =====================================

#define RGB_DEFAULT_TIME_OUT 300
#define RGB_FAST_MODE_TIME_OUT 30
#define RGB_TIME_OUT_MAX 600
#define RGB_TIME_OUT_MIN 10
#define RGB_TIME_OUT_STEP 10

// ==================================================================================================

bool rgb_enabled_flag;                  // Current LED state flag. If false then LED is off.
bool rgb_time_out_enable;               // Idle LED toggle enable. If false then LED will not turn off after idle timeout.
bool rgb_time_out_fast_mode_enabled;    // Enable flag for RGB timeout fast mode
bool rgb_time_out_user_value;           // This holds the toggle value set by user with ROUT_TG. It's necessary as RGB_TOG changes timeout enable.
uint16_t rgb_time_out_seconds;          // Idle LED timeout value, in seconds not milliseconds
uint16_t rgb_time_out_saved_seconds;    // The saved user config for RGB timeout period
led_flags_t rgb_time_out_saved_flag;    // Store LED flag before timeout so it can be restored when LED is turned on again.

void led_timeout_init(uint16_t rout_tg_keycode, uint16_t rout_vi_keycode, uint16_t rout_vd_keycode, uint16_t rout_fm_keycode);
void led_timeout_tick(void);
bool led_timeout_event(uint16_t keycode, keyrecord_t *record);

#endif
