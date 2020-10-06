/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2017, Linaro Limited
 */
#ifndef KERNEL_EMBEDDED_SP_H
#define KERNEL_EMBEDDED_SP_H

#include <compiler.h>
#include <kernel/embedded_ts.h>
#include <kernel/linker.h>
#include <stdint.h>
#include <tee_api_types.h>
#include <util.h>


#define __embedded_sp __section(".rodata.embedded_sp" __SECTION_FLAGS_RODATA)

#define for_each_embedded_sp(_sp) \
	for (_sp = &__rodata_embedded_sp_start; _sp < &__rodata_embedded_sp_end; \
	     _sp = (const struct embedded_ts *)				   \
		   ROUNDUP((vaddr_t)_sp + sizeof(*_sp) + _sp->size,	   \
			   __alignof__(struct embedded_ts)))

#endif /* KERNEL_EMBEDDED_SP_H */

