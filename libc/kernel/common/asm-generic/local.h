/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/
#ifndef _ASM_GENERIC_LOCAL_H
#define _ASM_GENERIC_LOCAL_H
#include <linux/percpu.h>
#include <linux/hardirq.h>
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#include <asm/atomic.h>
#include <asm/types.h>
typedef struct
{
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 atomic_long_t a;
} local_t;
#define LOCAL_INIT(i) { ATOMIC_LONG_INIT(i) }
#define local_read(l) atomic_long_read(&(l)->a)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define local_set(l,i) atomic_long_set((&(l)->a),(i))
#define local_inc(l) atomic_long_inc(&(l)->a)
#define local_dec(l) atomic_long_dec(&(l)->a)
#define local_add(i,l) atomic_long_add((i),(&(l)->a))
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define local_sub(i,l) atomic_long_sub((i),(&(l)->a))
#define __local_inc(l) local_set((l), local_read(l) + 1)
#define __local_dec(l) local_set((l), local_read(l) - 1)
#define __local_add(i,l) local_set((l), local_read(l) + (i))
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define __local_sub(i,l) local_set((l), local_read(l) - (i))
#define cpu_local_read(v) local_read(&__get_cpu_var(v))
#define cpu_local_set(v, i) local_set(&__get_cpu_var(v), (i))
#define cpu_local_inc(v) local_inc(&__get_cpu_var(v))
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define cpu_local_dec(v) local_dec(&__get_cpu_var(v))
#define cpu_local_add(i, v) local_add((i), &__get_cpu_var(v))
#define cpu_local_sub(i, v) local_sub((i), &__get_cpu_var(v))
#define __cpu_local_inc(v) __local_inc(&__get_cpu_var(v))
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define __cpu_local_dec(v) __local_dec(&__get_cpu_var(v))
#define __cpu_local_add(i, v) __local_add((i), &__get_cpu_var(v))
#define __cpu_local_sub(i, v) __local_sub((i), &__get_cpu_var(v))
#endif
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */