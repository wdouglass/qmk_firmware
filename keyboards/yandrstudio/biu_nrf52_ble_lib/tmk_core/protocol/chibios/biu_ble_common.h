#pragma once

#include "report.h"
#include <stdint.h>

// NRF RESET, WakeUp
#ifndef BIUNRF52ResetPin
#    define BIUNRF52ResetPin A1
#endif
#ifndef BIUNRF52WKPin
#    define BIUNRF52WKPin A3
#endif

// STM32 WakeUp
#ifndef BIUSTM32WKPin
#    define BIUSTM32WKPin A0
#endif


// UART SETTING
#ifndef BIUNRF52RxPin
#    define BIUNRF52RxPin A10
#endif
#ifndef BIUNRF52TxPin
#    define BIUNRF52TxPin A9
#endif
#ifndef BIUNRF52UartBaud
#    define BIUNRF52UartBaud 115200
#endif

// ADC SETTING
// #define SAMPLE_BATTERY
#ifdef SAMPLE_BATTERY
#   ifndef BATTERY_LEVEL_PIN
#       define BATTERY_LEVEL_PIN B0 // Adc pin
#   endif
#   ifndef BATTERY_LEVEL_SW_PIN
#       define BATTERY_LEVEL_SW_PIN B1 // Adc pin
#   endif
#endif

// Battery
#ifndef BATTERY_V_HEI
#    define BATTERY_V_HEI 3750 // 3.75V
#endif
#ifndef BATTERY_V_LOW
#    define BATTERY_V_LOW 3500 // 3.5V
#endif
#ifndef BATTERY_V_MAX
#    define BATTERY_V_MAX 5000 // 5V
#endif
#ifndef BATTERY_ADC_MAX
#    define BATTERY_ADC_MAX 3080
#endif


// TIMEOUT INTERVAL SETTING
#define BiuNrf52MsgTimeout               150           /* milliseconds  */
#define BiuNrf52MsgShortTimeout          10            /* milliseconds  */
#define BiuNrf52MsgRecvTimeout           2000          /* 2 second      */

#define BiuNrf52ResetTimeout             30000          /* 30 second    */
#define BiuNrf52InitTimeout              1500           /* 1.5 second   */
#define BiuNrf52KeepConnectionTimeout    30000          /* 30 second    */
#define BiuNrf52SystemOffTimeoutFast     120000         /* 2 minute     */
#define BiuNrf52SystemOffTimeout         120000         /* 5 minute     */
// #define BiuNrf52SystemOffTimeout         300000         /* 5 minute     */
#define BatteryUpdateInterval            60000          /* 1 minute     */

#define BiuStm32IdleTimeout              10000           /* 10 second     */

enum bluetooth_state {
    WORKING,
    SLEEPING,
    WAITING,
    STOPWORK
};

#ifdef __cplusplus
extern "C" {
#endif

bool bluetooth_init(void);
bool bluetooth_init_pre(void);
bool bluetooth_init_pos(void);
void bluetooth_task(void);
void bluetooth_send_resive_task(bool);
void bluetooth_battery_task(void);
void bluetooth_wakeup_task(void);
bool bluetooth_is_connected(void);
bool bluetooth_is_configured(void);
void bluetooth_wakeup_once(void);
void bluetooth_unpair_all(void);
void bluetooth_unpair_one(uint8_t device_id);
void bluetooth_unpair_current(void);
void bluetooth_pair(void);
void bluetooth_clear_buf(void);
void bluetooth_switch_one(uint8_t device_id);
uint8_t bluetooth_working_state(void);
// void bluetooth_power_manager(void);
void bluetooth_send_battery_level(void);

bool bluetooth_buffer_op(bool sendbuf, uint8_t op);

void bluetooth_send_keyboard(report_keyboard_t *report);
uint8_t bluetooth_get_led(void);

#ifdef EXTRAKEY_ENABLE
void bluetooth_send_extra(uint8_t report_id, uint16_t keycode);
#endif

#ifdef MOUSE_ENABLE
void bluetooth_send_mouse(report_mouse_t *report);
#endif

#ifdef NKRO_ENABLE
void bluetooth_send_keyboard_nkro(report_keyboard_t *report);
#endif

#ifdef JOYSTICK_ENABLE
void bluetooth_send_joystick(joystick_report_t *report);
#endif


#ifdef __cplusplus
}
#endif
