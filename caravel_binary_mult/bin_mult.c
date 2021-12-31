/*
 * SPDX-FileCopyrightText: 2020 Efabless Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "verilog/dv/caravel/defs.h"

#define PROJECT_ID 7

#define REG_CONFIG_HIGH          (*(volatile uint32_t*)0x30000000)
// #define REG      0x30FFFC00

#define REG_CONFIG_LOW          (*(volatile uint32_t*)0x30000001)

// #define OPENRAM(addr)       (*(uint32_t*)(SRAM_BASE_ADDR + (addr & 0x3fc)))

// #define WBRAM(addr)       (*(uint32_t*)(SRAM_BASE_ADDR ))



void main()
{
	/* 
	IO Control Registers
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 3-bits | 1-bit | 1-bit | 1-bit  | 1-bit  | 1-bit | 1-bit   | 1-bit   | 1-bit | 1-bit | 1-bit   |

	Output: 0000_0110_0000_1110  (0x1808) = GPIO_MODE_USER_STD_OUTPUT
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 110    | 0     | 0     | 0      | 0      | 0     | 0       | 1       | 0     | 0     | 0       |
	
	 
	Input: 0000_0001_0000_1111 (0x0402) = GPIO_MODE_USER_STD_INPUT_NOPULL
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 001    | 0     | 0     | 0      | 0      | 0     | 0       | 0       | 0     | 1     | 0       |

	*/

    // 8 outputs for MATRIX MULT
	reg_mprj_io_8  =   GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_9  =   GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_10 =   GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_11 =   GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_12 =   GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_13 =   GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_14 =   GPIO_MODE_USER_STD_OUTPUT;

    // debug
    reg_mprj_io_20 =   GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_21 =   GPIO_MODE_USER_STD_OUTPUT;

    /* Apply configuration */
    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);

    reg_la0_iena = 0; // input enable off
    reg_la0_oenb = 0; // output enable on

    // allow Caravel to write to the shared RAM
    // reg_la0_data &= ~(1 << SRAM_WRITE_PORT); 

    // load the function data into sram
 

    // read 1 address back just to check
    
    // activate the project by setting the 1st bit of 1st bank of LA - depends on the project ID
    reg_la0_data = (1 << PROJECT_ID);
    uint32_t mem_img_high = 0x0C3E1A00;
    uint32_t mem_img_low = 0x061BB76D;

    // set wishbone data 
    REG_CONFIG_LOW = mem_img_low;
    REG_CONFIG_HIGH = mem_img_high;

}
