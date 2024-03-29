/* SPDX-License-Identifier: GPL-2.0-only */

#include <arch/io.h>
#include <console/console.h>
#include <device/device.h>
#include <delay.h>

#include "ec.h"
#include "chip.h"

static u16 ec_cmd_reg = 0;
static u16 ec_data_reg = 0;

static inline u8 __ec_read(u8 addr)
{
	outb(addr, ec_cmd_reg);
	return inb(ec_data_reg);
}

static inline void __ec_write(u8 addr, u8 data)
{
	outb(addr, ec_cmd_reg);
	outb(data, ec_data_reg);
}

static int ec_ready(void)
{
	u16 timeout = EC_TIMEOUT;

	if (!ec_cmd_reg || !ec_data_reg) {
		printk(BIOS_DEBUG, "Invalid ports: cmd=0x%x data=0x%x\n",
		       ec_cmd_reg, ec_data_reg);
		return -1;
	}

	while (__ec_read(EC_MAILBOX_COMMAND) != 0 && --timeout) {
		udelay(10);
		if ((timeout & 0xff) == 0)
			printk(BIOS_SPEW, ".");
	}
	if (!timeout) {
		printk(BIOS_DEBUG, "Timeout waiting for EC to be ready.\n");
		return -1;
	}
	return 0;
}

int send_ec_command(u8 command)
{
	if (ec_ready() < 0)
		return -1;
	__ec_write(EC_MAILBOX_COMMAND, command);
	return ec_ready();
}

int send_ec_command_data(u8 command, u8 data)
{
	if (ec_ready() < 0)
		return -1;
	__ec_write(EC_MAILBOX_DATA, data);
	__ec_write(EC_MAILBOX_COMMAND, command);
	return ec_ready();
}

u8 read_ec_command_byte(u8 command)
{
	send_ec_command(command);
	return __ec_read(EC_MAILBOX_DATA);
}

u8 ec_read(u8 addr)
{
	if (send_ec_command_data(EC_RAM_READ, addr) < 0)
		return 0;
	return __ec_read(EC_MAILBOX_DATA);
}

int ec_write(u8 addr, u8 data)
{
	if (ec_ready() < 0)
		return -1;
	__ec_write(EC_MAILBOX_DATA, addr);
	__ec_write(EC_MAILBOX_DATA_H, data);
	__ec_write(EC_MAILBOX_COMMAND, EC_RAM_WRITE);
	return ec_ready();
}

void ec_set_bit(u8 addr, u8 bit)
{
	ec_write(addr, ec_read(addr) | (1 << bit));
}

void ec_clr_bit(u8 addr, u8 bit)
{
	ec_write(addr, ec_read(addr) &  ~(1 << bit));
}

void ec_set_ports(u16 cmd_reg, u16 data_reg)
{
	ec_cmd_reg = cmd_reg;
	ec_data_reg = data_reg;
}

static void mec1308_enable(struct device *dev)
{
	DEVTREE_CONST struct ec_smsc_mec1308_config *conf = dev->chip_info;

	if (conf->mailbox_port) {
		ec_cmd_reg = conf->mailbox_port;
		ec_data_reg = conf->mailbox_port + 1;
	}
}

struct chip_operations ec_smsc_mec1308_ops = {
	.name = "SMSC MEC1308 EC Mailbox Interface",
	.enable_dev = mec1308_enable
};
