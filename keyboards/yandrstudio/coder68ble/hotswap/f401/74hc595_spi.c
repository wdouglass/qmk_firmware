#include "74hc595.h"
#include "cums_spi_master.h"
#include "gpio.h"
#include "matrix.h"
#include "wait.h"

#ifdef DIRECT_PINS
#    error invalid DIRECT_PINS for 74hc595 matrix
#elif (DIODE_DIRECTION == ROW2COL)
extern const pin_t col_pins[MATRIX_COLS];
extern const uint8_t mask_of_each_595[NUM_OF_74HC595][MATRIX_ROWS];
#elif (DIODE_DIRECTION == COL2ROW)
extern const pin_t row_pins[MATRIX_ROWS];
extern const uint8_t mask_of_each_595[NUM_OF_74HC595][MATRIX_COLS];
#else
#   error DIODE_DIRECTION must be defined
#endif

#if (DIODE_DIRECTION == COL2ROW)
void select_cols(void) {
    uint8_t i = 0;
    spi_start(true, 0, 2);
    writePinLow(SPI_74HC595_CS);
    for (i = 0; i < NUM_OF_74HC595; ++i) {
        spi_write(SR_74HC595_ONES_ONEP);
    }
    writePinHigh(SPI_74HC595_CS); // output to storge registor
    spi_stop();
}
#else
void select_rows(void) {
    uint8_t i = 0;
    spi_start(true, 0, 2);
    writePinLow(SPI_74HC595_CS);
    for (i = 0; i < NUM_OF_74HC595; ++i) {
        spi_write(SR_74HC595_ONES_ONEP);
    }
    writePinHigh(SPI_74HC595_CS); // output to storge registor
    spi_stop();
}
#endif
