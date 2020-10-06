/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2017, Linaro Limited
 * Copyright (c) 2020, Arm Limited.
 */
#ifndef KERNEL_EARLY_TA_H
#define KERNEL_EARLY_TA_H

#include <compiler.h>
#include <kernel/embedded_ts.h>
#include <kernel/linker.h>
#include <stdint.h>
#include <tee_api_types.h>
#include <util.h>


#define __early_ta __section(".rodata.early_ta" __SECTION_FLAGS_RODATA)

#define for_each_early_ta(_ta) \
	for (_ta = &__rodata_early_ta_start; _ta < &__rodata_early_ta_end; \
	     _ta = (const struct embedded_ts *)				   \
		   ROUNDUP((vaddr_t)_ta + sizeof(*_ta) + _ta->size,	   \
			   __alignof__(struct embedded_ts)))

#endif /* KERNEL_EARLY_TA_H */

