/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <bootblock_common.h>
#include <southbridge/intel/i82801jx/i82801jx.h>
#include <northbridge/intel/x4x/x4x.h>


#define GPIO_DEV PNP_DEV(0x2e, IT8720F_GPIO)



void mb_get_spd_map(u8 spd_map[4])
{
	spd_map[0] = 0x50;
	spd_map[1] = 0x51;
	spd_map[2] = 0x52;
	spd_map[3] = 0x53;
}
