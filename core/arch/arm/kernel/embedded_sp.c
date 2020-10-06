// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (c) 2017, Linaro Limited
 */
#include <crypto/crypto.h>
#include <initcall.h>
#include <kernel/embedded_sp.h>
#include <kernel/embedded_ts.h>
#include <kernel/ts_store.h>
#include <stdio.h>
#include <string.h>
#include <trace.h>
#include <utee_defines.h>
#include <util.h>
#include <zlib.h>

static const struct embedded_ts *find_embedded_sp(const TEE_UUID *uuid)
{
	const struct embedded_ts *sp;

	for_each_embedded_sp(sp)
		if (!memcmp(&sp->uuid, uuid, sizeof(*uuid)))
			return sp;

	return NULL;
}

static TEE_Result embedded_sp_open(const TEE_UUID *uuid,
				   struct ts_store_handle **h)
{
	return emb_ts_open(uuid, h, find_embedded_sp);
}

TEE_TS_REGISTER_TS_STORE(2) = {
	.description = "Embedded SP",
	.open = embedded_sp_open,
	.get_size = emb_ts_get_size,
	.get_tag = emb_ts_get_tag,
	.read = emb_ts_read,
	.close = emb_ts_close,
};

static TEE_Result embedded_sp_init(void)
{
	const struct embedded_ts *sp;
	char __maybe_unused msg[60] = { '\0', };

	for_each_embedded_sp(sp) {
		if (sp->uncompressed_size)
			snprintf(msg, sizeof(msg),
				 " (compressed, uncompressed %u)",
				 sp->uncompressed_size);
		else
			msg[0] = '\0';
		DMSG("SP %pUl size %u%s", (void *)&sp->uuid, sp->size, msg);
	}

	return TEE_SUCCESS;
}

service_init(embedded_sp_init);
