/* Copyright 2022 JasonRen(biu)
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


#include "ec_switch.h"
#include "matrix.h"
#include "debug.h"

#ifndef LOW_THRESHOLD
#    define LOW_THRESHOLD 200
#endif

#ifndef HIGH_THRESHOLD
#    define HIGH_THRESHOLD 300
#endif

void matrix_init_custom(void) {
    ecsm_config_t ecsm_config = {.low_threshold = LOW_THRESHOLD, .high_threshold = HIGH_THRESHOLD};

    ecs_init(&ecsm_config);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool updated = ecs_matrix_scan(current_matrix);

    static int print_dely_cnt = 0;
    if (print_dely_cnt++ == 300) {
        print_dely_cnt = 0;
        ecs_print_matrix();
        print("\n");
    }

    return updated;
}


