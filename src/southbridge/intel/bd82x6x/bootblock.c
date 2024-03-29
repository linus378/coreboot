/* SPDX-License-Identifier: GPL-2.0-only */

#include <arch/bootblock.h>
#include <device/pci_ops.h>
#include <southbridge/intel/common/early_spi.h>
#include "pch.h"

static void setup_port80(void)
{
	/* Enable port 80 POST */
	if (CONFIG(POST_DEVICE_PCI_PCIE))
		RCBA32(GCS) |= 0x04; /* ... on PCI(e) */
	else
		RCBA32(GCS) &= (~0x04); /* ... on LPC */
}

static void set_spi_speed(void)
{
	u32 fdod;
	u8 ssfc;

	/* Observe SPI Descriptor Component Section 0 */
	RCBA32(0x38b0) = 0x1000;

	/* Extract the Write/Erase SPI Frequency from descriptor */
	fdod = RCBA32(0x38b4);
	fdod >>= 24;
	fdod &= 7;

	/* Set Software Sequence frequency to match */
	ssfc = RCBA8(0x3893);
	ssfc &= ~7;
	ssfc |= fdod;
	RCBA8(0x3893) = ssfc;
}

void bootblock_early_southbridge_init(void)
{
	enable_spi_prefetching_and_caching();

	early_pch_init();

	setup_port80();
	set_spi_speed();

	/* Enable upper 128bytes of CMOS */
	RCBA32(RC) = (1 << 2);
}
