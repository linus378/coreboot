## SPDX-License-Identifier: GPL-2.0-only

bootblock-y += variants/$(VARIANT_DIR)/gpio.c
romstage-y += variants/$(VARIANT_DIR)/gpio.c
ramstage-$(CONFIG_MAINBOARD_USE_LIBGFXINIT) += variants/$(VARIANT_DIR)/gma-mainboard.ads
bootblock-y += variants/$(VARIANT_DIR)/early_init.c
romstage-y += variants/$(VARIANT_DIR)/early_init.c
ramstage-y += variants/$(VARIANT_DIR)/hda_verb.c
