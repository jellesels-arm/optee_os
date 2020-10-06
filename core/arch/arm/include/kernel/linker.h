/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2017, Linaro Limited
 */
#ifndef __KERNEL_LINKER_H
#define __KERNEL_LINKER_H

#include <kernel/dt.h>
#include <kernel/early_ta.h>
#include <types_ext.h>

/*
 * Symbols exported by the link script.
 */


/*
 * These addresses will be the start or end of the exception binary search
 * index table (.ARM.exidx section)
 */
extern const uint8_t __exidx_start[];
extern const uint8_t __exidx_end[];
extern const uint8_t __extab_start[];
extern const uint8_t __extab_end[];

#define VCORE_UNPG_RX_PA	((unsigned long)__vcore_unpg_rx_start)
#define VCORE_UNPG_RX_SZ	((size_t)__vcore_unpg_rx_size)
#define VCORE_UNPG_RO_PA	((unsigned long)__vcore_unpg_ro_start)
#define VCORE_UNPG_RO_SZ	((size_t)__vcore_unpg_ro_size)
#define VCORE_UNPG_RW_PA	((unsigned long)__vcore_unpg_rw_start)
#define VCORE_UNPG_RW_SZ	((size_t)__vcore_unpg_rw_size)
#define VCORE_NEX_RW_PA	((unsigned long)__vcore_nex_rw_start)
#define VCORE_NEX_RW_SZ	((size_t)__vcore_nex_rw_size)
#define VCORE_INIT_RX_PA	((unsigned long)__vcore_init_rx_start)
#define VCORE_INIT_RX_SZ	((size_t)__vcore_init_rx_size)
#define VCORE_INIT_RO_PA	((unsigned long)__vcore_init_ro_start)
#define VCORE_INIT_RO_SZ	((size_t)__vcore_init_ro_size)

#define VCORE_START_VA		((vaddr_t)__text_start)

extern const uint8_t __vcore_unpg_rx_start[];
extern const uint8_t __vcore_unpg_rx_size[];
extern const uint8_t __vcore_unpg_ro_start[];
extern const uint8_t __vcore_unpg_ro_size[];
extern const uint8_t __vcore_unpg_rw_start[];
extern const uint8_t __vcore_unpg_rw_size[];
extern const uint8_t __vcore_nex_rw_start[];
extern const uint8_t __vcore_nex_rw_size[];
extern const uint8_t __vcore_init_rx_start[];
extern const uint8_t __vcore_init_rx_size[];
extern const uint8_t __vcore_init_ro_start[];
extern const uint8_t __vcore_init_ro_size[];

extern const uint8_t __text_start[];
extern const uint8_t __end[];

extern const uint8_t __identity_map_init_start[];
extern const uint8_t __identity_map_init_end[];

extern uint8_t __data_start[];
extern const uint8_t __data_end[];
extern const uint8_t __rodata_start[];
extern const uint8_t __rodata_end[];
extern const uint8_t __bss_start[];
extern const uint8_t __bss_end[];
extern const uint8_t __nozi_start[];
extern const uint8_t __nozi_end[];
extern const uint8_t __nozi_stack_start[];
extern const uint8_t __nozi_stack_end[];
extern const uint8_t __init_start[];
extern const uint8_t __init_end[];

extern uint8_t __heap1_start[];
extern const uint8_t __heap1_end[];
extern uint8_t __heap2_start[];
extern const uint8_t __heap2_end[];

extern uint8_t __nex_heap_start[];
extern const uint8_t __nex_heap_end[];

extern const uint8_t __pageable_part_start[];
extern const uint8_t __pageable_part_end[];
extern const uint8_t __pageable_start[];
extern const uint8_t __pageable_end[];

#define ASAN_SHADOW_PA	((paddr_t)__asan_shadow_start)
#define ASAN_SHADOW_SZ	((size_t)__asan_shadow_size)
extern const uint8_t __asan_shadow_start[];
extern const uint8_t __asan_shadow_end[];
extern const uint8_t __asan_shadow_size[];

#define ASAN_MAP_PA	((paddr_t)__asan_map_start)
#define ASAN_MAP_SZ	((size_t)__asan_map_size)
extern const uint8_t __asan_map_start[];
extern const uint8_t __asan_map_end[];
extern const uint8_t __asan_map_size[];

extern const vaddr_t __ctor_list;
extern const vaddr_t __ctor_end;


extern const struct dt_driver __rodata_dtdrv_start;
extern const struct dt_driver __rodata_dtdrv_end;

extern const struct embedded_ts __rodata_early_ta_start;
extern const struct embedded_ts __rodata_early_ta_end;

/* Generated by core/arch/arm/kernel/link.mk */
extern const char core_v_str[];

#endif /*__KERNEL_LINKER_H*/

