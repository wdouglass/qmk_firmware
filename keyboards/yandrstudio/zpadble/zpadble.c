/* Copyright 2021 JasonRen(biu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "zpadble.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        {0,  1,  3,  4,  6,  7,  9,  10,  12,  13,  15,  16},
        {17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,   NO_LED},
        {28,  29,  30,  31,  32,  33,  34,  35,  36,  37,   NO_LED,  38},
        {39,  41,  42,  44,   NO_LED,  45,  47,   NO_LED,  48,  49,   NO_LED,  51}
    },
    {
      // LED Index to Physical Position
        {0,0},{20,0},{0,0},{41,0},{61,0},{56,0},{81,0},{102,0},{112,0},{122,0},{143,0},{168,0},{163,0},{183,0},{224,0},{204,0},{224,0},
        {0,21},{20,21},{41,21},{61,21},{81,21},{102,21},{122,21},{143,21},{163,21},{183,21},{204,21},
        {0,43},{20,43},{41,43},{61,43},{81,43},{102,43},{122,43},{143,43},{163,43},{183,43},{224,43},
        {0,64},{0,64},{20,64},{41,64},{56,64},{61,64},{102,64},{112,64},{122,64},{163,64},{183,64},{168,64},{224,64}
    },
    {
      // LED Index to Flag
      4,4,2,4,4, 2,4,4,2,4,
      4,2,4,4,2, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      2,4,4,2,4, 4,2,4,4,4,
      2,4
    }
};


#endif
