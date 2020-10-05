/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2015-2019, Linaro Limited
 * Copyright (c) 2020, Arm Limited.
 */
#ifndef __KERNEL_TS_STORE_H
#define __KERNEL_TS_STORE_H

#include <tee_api_types.h>

struct ts_store_handle;
struct ts_store_ops {
	/*
	 * Human-readable string to describe where the TS comes from.
	 * For debug purposes only.
	 */
	const char *description;
	/*
	 * Open a TS. Does not guarantee that the TS is valid or even exists.
	 */
	TEE_Result (*open)(const TEE_UUID *uuid,
			   struct ts_store_handle **h);
	/*
	 * Return the size of the unencrypted TS binary, that is: the TS
	 * header (struct ts_head) plus the ELF data.
	 */
	TEE_Result (*get_size)(const struct ts_store_handle *h,
			       size_t *size);

	/*
	 * Return the tag or hash of the TA binary. Used to uniquely
	 * identify the binary also if the binary happens to be updated.
	 */
	TEE_Result (*get_tag)(const struct ts_store_handle *h,
			      uint8_t *tag, unsigned int *tag_len);
	/*
	 * Read the TS sequentially, from the start of the TS header (struct
	 * ts_head) up to the end of the ELF.
	 * The TEE core is expected to read *exactly* get_size() bytes in total
	 * unless an error occurs. Therefore, an implementation may rely on the
	 * condition (current offset == total size) to detect the last call to
	 * this function.
	 * @data: pointer to secure memory where the TS bytes should be copied.
	 * If @data == NULL and @len != 0, the function should just skip @len
	 * bytes.
	 */
	TEE_Result (*read)(struct ts_store_handle *h, void *data,
			   size_t len);
	/*
	 * Close a TS handle. Do nothing if @h == NULL.
	 */
	void (*close)(struct ts_store_handle *h);
};

struct ts_store_handle;

/*
 * Registers a TS storage.
 *
 * A TS is loaded from the first TS storage in which the TS can be found.
 * TS storage is searched in order of priority, where lower values are
 * tried first.
 *
 * Note prio must be unique per storage in order to avoid dependency on
 * registration order. This is enforced by a deliberate linker error in
 * case of conflict.
 *
 * Also note that TS storage is sorted lexicographically instead of
 * numerically.
 */
#define TEE_TS_REGISTER_TS_STORE(prio) \
	int __tee_ts_store_##prio __unused; \
	SCATTERED_ARRAY_DEFINE_PG_ITEM_ORDERED(ts_stores, prio, \
					       struct ts_store_ops)
#endif /*__KERNEL_TS_STORE_H*/
