/*
 *
 * Copyright (C) 2015 Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <libpayload-config.h>
#include <libpayload.h>
#include <commonlib/bsd/fmap_serialized.h>
#include <coreboot_tables.h>
#include <cbfs.h>
#include <boot_device.h>
#include <stdint.h>
#include <arch/virtual.h>

/* Private fmap cache. */
static struct fmap *_fmap_cache;

static enum cb_err fmap_find_area(struct fmap *fmap, const char *name, size_t *offset,
				  size_t *size)
{
	for (size_t i = 0; i < le32toh(fmap->nareas); ++i) {
		if (strncmp((const char *)fmap->areas[i].name, name, FMAP_STRLEN) != 0)
			continue;
		if (offset)
			*offset = le32toh(fmap->areas[i].offset);
		if (size)
			*size = le32toh(fmap->areas[i].size);
		return CB_SUCCESS;
	}

	return CB_ERR;
}

static bool fmap_is_signature_valid(struct fmap *fmap)
{
	return memcmp(fmap->signature, FMAP_SIGNATURE, sizeof(fmap->signature)) == 0;
}

static bool fmap_setup_cache(void)
{
	/* Use FMAP cache if available */
	if (lib_sysinfo.fmap_cache
	    && fmap_is_signature_valid((struct fmap *)phys_to_virt(lib_sysinfo.fmap_cache))) {
		_fmap_cache = (struct fmap *)phys_to_virt(lib_sysinfo.fmap_cache);
		return true;
	}

	return false;
}

enum cb_err fmap_locate_area(const char *name, size_t *offset, size_t *size)
{
	if (!_fmap_cache && !fmap_setup_cache())
		return CB_ERR;

	return fmap_find_area(_fmap_cache, name, offset, size);
}
