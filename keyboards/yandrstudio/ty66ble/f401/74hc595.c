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
    uint8_t i = 0, col = 0;
    spi_start(true, 0, 2);
    writePinLow(SPI_74HC595_CS);
    matrix_io_delay();
    for (col = 0; col < MATRIX_COLS; col++) {
#   if (COL_F2L_FOR_595 == TRUE)
        for (i = 0; i < NUM_OF_74HC595; ++i) {
            spi_write(mask_of_each_595[i][col]);
        }
#   else
        for (i = NUM_OF_74HC595; i >=1 ; --i) {
            spi_write(mask_of_each_595[i][col]);
        }
#   endif
    }
    writePinHigh(SPI_74HC595_CS); // output to storge registor
    matrix_io_delay();
    spi_stop();
}
#else
void select_rows(void) {
    uint8_t i = 0, row = 0;
    spi_start(true, 0, 2);
    writePinLow(SPI_74HC595_CS);
    for (row = 0; row < MATRIX_ROWS; row++) {
#   if (COL_F2L_FOR_595 == TRUE)
       for (i = 0; i < NUM_OF_74HC595; ++i) {
           spi_write(mask_of_each_595[i][row]);
       }
#   else
       for (i = NUM_OF_74HC595; i >=1 ; --i) {
           spi_write(mask_of_each_595[i][row]);
       }
#   endif
    }
    writePinHigh(SPI_74HC595_CS); // output to storge registor
    spi_stop();
}
#endif
