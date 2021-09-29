#include "distributors.h"
#include "usb_util.h"
#include "biu_ble_common.h"
#include "usb_main.h"
#include "outputselect.h"
#include "print.h"
#include "quantum.h"
#include "matrix.h"
#include "uart.h"
#include <string.h>
#include <hal.h>
#include <ch.h>





#if NUM_OF_74HC595 > 0
#include "74hc595.h"
#endif



extern keymap_config_t keymap_config;
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values

#ifndef NUM_OF_74HC595
    #ifdef DIRECT_PINS
    #    error invalid DIRECT_PINS for 74hc595 matrix
    #elif (DIODE_DIRECTION == ROW2COL)
        const pin_t out_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
    #elif (DIODE_DIRECTION == COL2ROW)
        const pin_t out_pins[MATRIX_COLS] = MATRIX_COL_PINS;
    #else
    #   error DIODE_DIRECTION must be defined
    #endif
#endif

#ifdef DIRECT_PINS
#    error invalid DIRECT_PINS for 74hc595 matrix
#elif (DIODE_DIRECTION == ROW2COL)
    const pin_t in_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#elif (DIODE_DIRECTION == COL2ROW)
    const pin_t in_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
#else
#   error DIODE_DIRECTION must be defined
#endif


static struct {
    uint32_t fast_shale_sleep_update;
} state;



/* start ========================================================================= */
/* stm32 power manager */

static int test_aaa = 0;
void wakeup_stm32_env(void *arg) {
    // chSysLockFromISR();
    // SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);


    /* we must reinit clocks after waking up ESPECIALLY if use HSE or HSI+PLL */
    // NVIC_SystemReset();


    // halInit();
    // chSysInit();
    // stm32_gpio_init();
    // rccResetAHB1(STM32_GPIO_EN_MASK);
    // rccEnableAHB1(STM32_GPIO_EN_MASK, true);
    // halInit();
    uprintf("test_a is %d\n", test_aaa);
    // set_exti_off_input_pin();
    // matrix_init();
    test_aaa++;
    // chSysUnlockFromISR();
}

static void inline set_exti_off_input_pin(void) {
#if (DIODE_DIRECTION == COL2ROW)
    for (uint8_t i = 0; i < MATRIX_ROWS; ++i) {
        palDisableLineEvent(in_pins[i]);
    }
#else
    for (uint8_t i = 0; i < MATRIX_COLS; ++i) {
        palDisableLineEvent(in_pins[i]);
    }
#endif
}

static void inline set_matrix_hold_on(void) {
#if NUM_OF_74HC595 > 0
    #if (DIODE_DIRECTION == COL2ROW)
    select_cols();
    #else
    select_rows();
    #endif
#else
    #if (DIODE_DIRECTION == COL2ROW)
    for (uint8_t i = 0; i < MATRIX_COLS; ++i) {
        palSetLine(out_pins[i]);
    }
    #else
    for (uint8_t i = 0; i < MATRIX_ROWS; ++i) {
        palSetLine(out_pins[i]);
    }
    #endif
#endif
}


static void inline set_exti_on_input_pin(void) {
#if (DIODE_DIRECTION == COL2ROW)
    for (uint8_t i = 0; i < MATRIX_ROWS; ++i) {
        palSetLineMode(in_pins[i], PAL_MODE_INPUT_PULLDOWN);
        palEnableLineEvent(in_pins[i], PAL_EVENT_MODE_RISING_EDGE);
        // palSetLineCallback(in_pins[i], wakeup_stm32_env, NULL);
    }
#else
    for (uint8_t i = 0; i < MATRIX_COLS; ++i) {
        palSetLineMode(in_pins[i], PAL_MODE_INPUT_PULLDOWN);
        palEnableLineEvent(in_pins[i], PAL_EVENT_MODE_RISING_EDGE);
        // palSetLineCallback(in_pins[i], wakeup_stm32_env, NULL);
    }
#endif
}

static void inline stopMode(void) {
    palEnableLineEvent(BIUSTM32WKPin, PAL_EVENT_MODE_FALLING_EDGE); /* NC */
    set_matrix_hold_on();
    set_exti_on_input_pin();
    uprintf("Enter into Sleep model\n");
    usbStop(&USB_DRIVER);
    // usbDisconnectBus(&USB_DRIVER);

    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
    /* debugging */
    // DBGMCU->CR |= DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_SLEEP | DBGMCU_CR_DBG_STANDBY;

    /* clear PDDS and LPDS bits */
    PWR->CR &= ~(PWR_CR_PDDS | PWR_CR_LPDS);

    /* set LPDS and clear  */
    PWR->CR  |= (PWR_CR_LPDS | PWR_CR_CSBF | PWR_CR_CWUF);

    /* enable wakeup pin */
    PWR->CSR |= PWR_CSR_EWUP;

    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    __DSB();
    __WFI();

    chSysLock();

    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;

    PWR->CR |= PWR_CR_CWUF;
    PWR->CR |= PWR_CR_CSBF;

    stm32_clock_init();
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

    halInit();

    palDisableLineEvent(BIUSTM32WKPin);
    set_exti_off_input_pin();
    // usbInit();
    restart_usb_driver(&USB_DRIVER);
    // usbConnectBus(&USB_DRIVER);
    // uprintf("Level out  Sleep model\n");

    // start the uart data trans
    uart_init(BIUNRF52UartBaud, true);

    // hang up the reset pin
    palSetLineMode(BIUNRF52ResetPin, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLine(BIUNRF52ResetPin);
    // set the adc read sw off
#   ifdef BATTERY_LEVEL_SW_PIN
        setPinOutput(BATTERY_LEVEL_SW_PIN);
        writePinHigh(BATTERY_LEVEL_SW_PIN);
#   endif

    // set wakeup nrf pin
    palSetLineMode(BIUNRF52WKPin, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLine(BIUNRF52WKPin);
    chSysUnlock();
}



static void inline bleutooth_clear_keyboard(void) {
    report_keyboard_t * keyboard_report = (report_keyboard_t*)malloc(sizeof(report_keyboard_t));
    // not clear mods
    #ifdef NKRO_ENABLE
        if (keymap_config.nkro) {
            memset(keyboard_report, 0, sizeof(report_keyboard_t));
            bluetooth_send_keyboard_nkro(keyboard_report);
        } else
    #endif
    {
        memset(keyboard_report, 0, sizeof(report_keyboard_t));
        bluetooth_send_keyboard(keyboard_report);
    }
    #ifdef EXTRAKEY_ENABLE
        bluetooth_send_extra(REPORT_ID_CONSUMER, 0);
        bluetooth_send_extra(REPORT_ID_SYSTEM, 0);
    #endif
    #ifdef MOUSE_ENABLE
        report_mouse_t * mouse_report = (report_mouse_t*)malloc(sizeof(report_mouse_t));
        memset(keyboard_report, 0, sizeof(report_mouse_t));
        bluetooth_send_mouse(mouse_report);
    #endif
    #ifdef JOYSTICK_ENABLE
        joystick_report_t * joystick_report = (joystick_report_t*)malloc(sizeof(joystick_report_t));
        memset(keyboard_report, 0, sizeof(joystick_report_t));
        bluetooth_send_joystick(joystick_report);
    #endif
    uint8_t try_time = 0;
    while (!bluetooth_buffer_op(true, 1) || try_time < 6) {
        bluetooth_send_resive_task(true);
        try_time++;
    }
    if (try_time>=10) {
        bluetooth_buffer_op(true, 0);
    }
}
static bool inline matrix_is_zero(void) {
    uint32_t sum_of_matrix = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; ++i) {
        sum_of_matrix += matrix[i];
    }
    return (sum_of_matrix == 0);
}

// static uint8_t once_a0 = 0;
void bluetooth_power_manager(void) {
    if (matrix_is_zero()) {
        if (state.fast_shale_sleep_update != 0 && timer_elapsed32(state.fast_shale_sleep_update) > BiuStm32IdleTimeout) {
            if (bluetooth_buffer_op(true, 1)) {
                bleutooth_clear_keyboard();
                stopMode();
            }
            state.fast_shale_sleep_update = timer_read32();
        } else if (state.fast_shale_sleep_update == 0) {
            state.fast_shale_sleep_update = timer_read32();
        }
    } else {
        state.fast_shale_sleep_update = timer_read32();
    }
}
/* end ========================================================================= */
