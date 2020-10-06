/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2017, Linaro Limited
 */
#ifndef KERNEL_EMBEDDED_SP_H
#define KERNEL_EMBEDDED_SP_H

#include <kernel/embedded_ts.h>
#include <stdint.h>
#include <tee_api_types.h>

#define for_each_embedded_sp(_sp) \
	SCATTERED_ARRAY_FOREACH(_sp, embedded_sps, struct embedded_ts)

#endif /* KERNEL_EMBEDDED_SP_H */

