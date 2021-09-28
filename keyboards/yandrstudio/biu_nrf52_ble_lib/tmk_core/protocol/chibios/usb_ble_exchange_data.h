#pragma once


#ifdef __cplusplus
extern "C" {
#endif

/* set led state of usb */
void set_usb_led_state(uint8_t l);
void bluetooth_set_led(uint8_t l);

#ifdef __cplusplus
}
#endif
