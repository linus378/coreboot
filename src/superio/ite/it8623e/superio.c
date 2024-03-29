/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <device/device.h>
#include <device/pnp.h>
#include <pc80/keyboard.h>
#include <superio/conf_mode.h>
#include <superio/ite/common/env_ctrl.h>

#include "chip.h"
#include "it8623e.h"

static void it8623e_init(struct device *dev)
{
	const struct superio_ite_it8623e_config *conf = dev->chip_info;
	const struct resource *res;

	if (!dev->enabled)
		return;

	switch (dev->path.pnp.device) {
	case IT8623E_EC:
		res = probe_resource(dev, PNP_IDX_IO0);
		if (!conf || !res)
			break;
		ite_ec_init(res->base, &conf->ec);
		break;
	case IT8623E_KBCK:
		pc_keyboard_init(NO_AUX_DEVICE);
		break;
	case IT8623E_KBCM:
		break;
	}
}

static struct device_operations ops = {
	.read_resources   = pnp_read_resources,
	.set_resources    = pnp_set_resources,
	.enable_resources = pnp_enable_resources,
	.enable           = pnp_alt_enable,
	.init             = it8623e_init,
	.ops_pnp_mode     = &pnp_conf_mode_870155_aa,
};

static struct pnp_info pnp_dev_info[] = {
	{ NULL, IT8623E_FDC, PNP_IO0 | PNP_IRQ0 | PNP_DRQ0, 0x0ff8, },
	{ NULL, IT8623E_SP1, PNP_IO0 | PNP_IRQ0, 0x0ff8, },
	{ NULL, IT8623E_SP2, PNP_IO0 | PNP_IRQ0, 0x0ff8, },
	{ NULL, IT8623E_PP, PNP_IO0 | PNP_IO1 | PNP_IRQ0 | PNP_DRQ0,
		0x0ff8, 0x0ff8, },
	{ NULL, IT8623E_EC, PNP_IO0 | PNP_IO1 | PNP_IRQ0, 0x0ff0, 0x0ff0, },
	{ NULL, IT8623E_KBCK, PNP_IO0 | PNP_IO1 | PNP_IRQ0, 0x0fff, 0x0fff, },
	{ NULL, IT8623E_KBCM, PNP_IRQ0, },
	{ NULL, IT8623E_GPIO, PNP_IO0 | PNP_IO1 | PNP_IO2 | PNP_IRQ0,
		0x0fff, 0x0fe0, 0x0fff, },
};

static void enable_dev(struct device *dev)
{
	pnp_enable_devices(dev, &ops, ARRAY_SIZE(pnp_dev_info), pnp_dev_info);
}

struct chip_operations superio_ite_it8623e_ops = {
	.name = "ITE IT8623E Super I/O",
	.enable_dev = enable_dev,
};
