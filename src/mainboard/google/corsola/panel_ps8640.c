/* SPDX-License-Identifier: GPL-2.0-only */

#include <console/console.h>
#include <delay.h>
#include <drivers/parade/ps8640/ps8640.h>
#include <edid.h>
#include <gpio.h>
#include <soc/i2c.h>
#include <soc/regulator.h>

#include "gpio.h"
#include "panel.h"

static void bridge_ps8640_power_on(void)
{
	/*
	 * PS8640 power-on sequence is described in chapter 14, PS8640_DS_V1.4_20200210.docx
	 * - set VDD12 to be 1.2V
	 * - delay 100us
	 * - set VDD33 to be 3.3V
	 * - pull hign PD#
	 * - pull down RST#
	 * - delay 2ms
	 * - pull high RST#
	 * - delay more than 50ms (55ms for margin)
	 * - pull down RST#
	 * - delay more than 50ms (55ms for margin)
	 * - pull high RST#
	 */

	/* Set VRF12 to 1.2V and VCN33 to 3.3V */
	mainboard_set_regulator_voltage(MTK_REGULATOR_VRF12, 1200000);
	udelay(100);
	mainboard_set_regulator_voltage(MTK_REGULATOR_VCN33, 3300000);
	udelay(200);

	/* Turn on bridge */
	gpio_output(GPIO_EDPBRDG_PWREN, 1);
	gpio_output(GPIO_EDPBRDG_RST_L, 0);
	mdelay(2);
	gpio_output(GPIO_EDPBRDG_RST_L, 1);
	mdelay(55);
	gpio_output(GPIO_EDPBRDG_RST_L, 0);
	mdelay(55);
	gpio_output(GPIO_EDPBRDG_RST_L, 1);
}

static void panel_power_on(void)
{
	/* Turn on the panel */
	gpio_output(GPIO_EN_PP3300_DISP_X, 1);
	bridge_ps8640_power_on();
}

static int bridge_ps8640_get_edid(struct edid *edid)
{
	const u8 chip = 0x8;

	if (ps8640_init(BRIDGE_I2C, chip) < 0) {
		printk(BIOS_ERR, "%s: Can't init PS8640 bridge\n", __func__);
		return -1;
	}
	if (ps8640_get_edid(BRIDGE_I2C, chip, edid) < 0) {
		printk(BIOS_ERR, "%s: Can't get panel's edid\n", __func__);
		return -1;
	}
	return 0;
}

static struct panel_description ps8640_bridge = {
	.configure_backlight = backlight_control,
	.power_on = panel_power_on,
	.get_edid = bridge_ps8640_get_edid,
	.disp_path = DISP_PATH_MIPI,
	.orientation = LB_FB_ORIENTATION_NORMAL,
};

struct panel_description *get_ps8640_description(void)
{
	mtk_i2c_bus_init(BRIDGE_I2C, I2C_SPEED_FAST);
	return &ps8640_bridge;
}
