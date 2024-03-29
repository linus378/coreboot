/* SPDX-License-Identifier: GPL-2.0-only */

#include <southbridge/intel/bd82x6x/pch.h>
#include <southbridge/intel/common/gpio.h>

const struct southbridge_usb_port mainboard_usb_ports[] = {
	{ 1, 0, 0 }, /* P0 (left, fan side), OC 0 */
	{ 1, 0, 1 }, /* P1 (left touchpad side), OC 1 */
	{ 1, 1, 3 }, /* P2: dock, OC 3 */
	{ 1, 1, -1 }, /* P3: wwan, no OC */
	{ 1, 1, -1 }, /* P4: Wacom tablet on X230t, otherwise empty */
	{ 1, 1, -1 }, /* P5: Expresscard, no OC */
	{ 0, 0, -1 }, /* P6: Empty */
	{ 1, 2, -1 }, /* P7: dock, no OC */
	{ 0, 0, -1 }, /* P8: Empty */
	{ 1, 2, 5 }, /* P9: Right (EHCI debug), OC 5 */
	{ 1, 1, -1 }, /* P10: fingerprint reader, no OC */
	{ 1, 1, -1 }, /* P11: bluetooth, no OC. */
	{ 1, 1, -1 }, /* P12: wlan, no OC */
	{ 1, 1, -1 }, /* P13: webcam, no OC */
};
