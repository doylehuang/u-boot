/*
<<<<<<< HEAD
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * David Mueller, ELSOFT AG, <d.mueller@elsoft.ch>
 *
 * (C) Copyright 2003
 * Texas Instruments, <www.ti.com>
 * Kshitij Gupta <Kshitij@ti.com>
 *
 * (C) Copyright 2004
 * ARM Ltd.
 * Philippe Robin, <philippe.robin@arm.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
=======
 * Copyright 2016 IBM Corporation
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
>>>>>>> f9b2a49f57c153c7358f9769234c0cefdf4de8d4
 */

#include <common.h>
#include <netdev.h>

#include <asm/arch/ast_scu.h>
#include <asm/arch/ast-sdmc.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

int board_init(void)
{
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;

	return 0;
}

int dram_init(void)
{
	/* dram_init must store complete ramsize in gd->ram_size */
	u32 vga = ast_scu_get_vga_memsize();
	u32 dram = ast_sdmc_get_mem_size();
	gd->ram_size = (dram - vga);

	return 0;
}

#ifdef CONFIG_FTGMAC100
int board_eth_init(bd_t *bd)
{
        return ftgmac100_initialize(bd);
}
#endif

#ifdef CONFIG_ASPEEDNIC
int board_eth_init(bd_t *bd)
{
        return aspeednic_initialize(bd);
}
#endif

/* Called by macro WATCHDOG_RESET */
#if defined(CONFIG_HW_WATCHDOG)
void hw_watchdog_reset(void)
{
	/* Restart WD2 timer */
	writel(0x4755, AST_WDT2_BASE + 0x08);
}
#endif /* CONFIG_WATCHDOG */
