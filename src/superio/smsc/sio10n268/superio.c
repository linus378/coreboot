/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/device.h>
#include <device/pnp.h>
#include <pc80/keyboard.h>

#include "sio10n268.h"

static void init(struct device *dev)
{
	if (!dev->enabled)
		return;

	switch (dev->path.pnp.device) {
	case SIO10N268_FDC: /* TODO. */
		break;
	case SIO10N268_PP: /* TODO. */
		break;
	case SIO10N268_KBDC:
		/* TODO: This is still hardcoded. */
		pc_keyboard_init(NO_AUX_DEVICE);
		break;
	// [..] The rest: TODO
	}
}

static struct device_operations ops = {
	.read_resources   = pnp_read_resources,
	.set_resources    = pnp_set_resources,
	.enable_resources = pnp_enable_resources,
	.enable           = pnp_enable,
	.init             = init,
};

/* TODO: FDC, PP, AUX. */
static struct pnp_info pnp_dev_info[] = {
	{ NULL, SIO10N268_KBDC, PNP_IO0 | PNP_IO1, 0x07f8, 0x07f8, },
};

static void enable_dev(struct device *dev)
{
	pnp_enable_devices(dev, &ops, ARRAY_SIZE(pnp_dev_info), pnp_dev_info);
}

struct chip_operations superio_smsc_sio10n268_ops = {
	.name = "SMSC SIO10N268 Super I/O",
	.enable_dev = enable_dev,
};
