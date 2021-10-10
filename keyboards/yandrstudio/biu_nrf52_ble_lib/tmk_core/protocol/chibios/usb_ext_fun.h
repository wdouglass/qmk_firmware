#pragma once

// TESTING
// extern uint8_t blinkLed;

#include <ch.h>
#include <hal.h>

#ifndef USB_DRIVER
#define USB_DRIVER USBD1
#endif


/* Restart the USB driver and bus */
void restart_usb_driver(USBDriver *usbp);
