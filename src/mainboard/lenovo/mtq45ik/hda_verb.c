/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <device/azalia_device.h>

const u32 cim_verb_data[] = {
	/* coreboot specific header */
	0x11d41882,
	0x17aa3049,	// Subsystem ID
	11,	// Number of entries

	/* Pin Widget Verb Table */

	AZALIA_PIN_CFG(0, 0x11, 0x02214030),
	AZALIA_PIN_CFG(0, 0x12, 0x01014010),
	AZALIA_PIN_CFG(0, 0x13, 0x911711f0),
	AZALIA_PIN_CFG(0, 0x14, 0x02a19021),
	AZALIA_PIN_CFG(0, 0x15, 0x0181302e),
	AZALIA_PIN_CFG(0, 0x16, 0x41011012),
	AZALIA_PIN_CFG(0, 0x17, 0x01a19020),
	AZALIA_PIN_CFG(0, 0x18, 0x99331122),
	AZALIA_PIN_CFG(0, 0x1a, 0x91f711f0),
	AZALIA_PIN_CFG(0, 0x1b, 0x4145f1a0),
	AZALIA_PIN_CFG(0, 0x24, 0x41016011),

	/* HDMI */
	0x80862803,
	0x80860101,
	1,

	AZALIA_PIN_CFG(0, 0x03, 0x18560010)
};

const u32 pc_beep_verbs[0] = {};

const u32 pc_beep_verbs_size = ARRAY_SIZE(pc_beep_verbs);
const u32 cim_verb_data_size = ARRAY_SIZE(cim_verb_data);

