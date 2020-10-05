// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (c) 2020, Arm Limited.
 */
#include <kernel/ts_store.h>

static TEE_Result check_ts_store(void)
{
	const struct ts_store_ops *op = NULL;

	SCATTERED_ARRAY_FOREACH(op, ts_stores, struct ts_store_ops)
		DMSG("TS store: \"%s\"", op->description);

	return TEE_SUCCESS;
}
service_init(check_ts_store);
