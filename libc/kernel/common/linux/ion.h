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
#ifndef _LINUX_ION_H
#define _LINUX_ION_H
#include <linux/ioctl.h>
#include <linux/types.h>
struct ion_handle;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
enum ion_heap_type {
 ION_HEAP_TYPE_SYSTEM,
 ION_HEAP_TYPE_SYSTEM_CONTIG,
 ION_HEAP_TYPE_CARVEOUT,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 ION_HEAP_TYPE_CUSTOM,
 ION_NUM_HEAPS = 16,
};
#define ION_HEAP_SYSTEM_MASK (1 << ION_HEAP_TYPE_SYSTEM)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define ION_HEAP_SYSTEM_CONTIG_MASK (1 << ION_HEAP_TYPE_SYSTEM_CONTIG)
#define ION_HEAP_CARVEOUT_MASK (1 << ION_HEAP_TYPE_CARVEOUT)
#define ION_FLAG_CACHED 1  
#define ION_FLAG_CACHED_NEEDS_SYNC 2  

#define ION_IS_CACHED(__flags)  ((__flags) & ION_FLAG_CACHED)

#ifdef __KERNEL__
struct ion_device;
struct ion_heap;
struct ion_mapper;
struct ion_client;
struct ion_buffer;

/* This should be removed some day when phys_addr_t's are fully
   plumbed in the kernel, and all instances of ion_phys_addr_t should
   be converted to phys_addr_t.  For the time being many kernel interfaces
   do not accept phys_addr_t's that would have to */
#define ion_phys_addr_t unsigned long

/**
 * struct ion_platform_heap - defines a heap in the given platform
 * @type:   type of the heap from ion_heap_type enum
 * @id:     unique identifier for heap.  When allocating (lower numbers
 *      will be allocated from first)
 * @name:   used for debug purposes
 * @base:   base address of heap in physical memory if applicable
 * @size:   size of the heap in bytes if applicable
 *
 * Provided by the board file.
 */
struct ion_platform_heap {
    enum ion_heap_type type;
    unsigned int id;
    const char *name;
    ion_phys_addr_t base;
    size_t size;
    unsigned int has_outer_cache;
};

/**
 * struct ion_platform_data - array of platform heaps passed from board file
 * @nr:     number of structures in the array
 * @heaps:  array of platform_heap structions
 *
 * Provided by the board file in the form of platform data to a platform device.
 */
struct ion_platform_data {
    int nr;
    struct ion_platform_heap heaps[];
};

/**
 * ion_reserve() - reserve memory for ion heaps if applicable
 * @data:   platform data specifying starting physical address and
 *      size
 *
 * Calls memblock reserve to set aside memory for heaps that are
 * located at specific memory addresses or of specfic sizes not
 * managed by the kernel
 */
void ion_reserve(struct ion_platform_data *data);

/**
 * ion_client_create() -  allocate a client and returns it
 * @dev:    the global ion device
 * @name:   used for debugging
 */
struct ion_client *ion_client_create(struct ion_device *dev,
                     const char *name);

/**
 * ion_client_destroy() -  free's a client and all it's handles
 * @client: the client
 *
 * Free the provided client and all it's resources including
 * any handles it is holding.
 */
void ion_client_destroy(struct ion_client *client);

/**
 * ion_alloc - allocate ion memory
 * @client:     the client
 * @len:        size of the allocation
 * @align:      requested allocation alignment, lots of hardware blocks
 *          have alignment requirements of some kind
 * @heap_id_mask:   mask of heaps to allocate from, if multiple bits are set
 *          heaps will be tried in order from highest to lowest
 *          id
 * @flags:      heap flags, the low 16 bits are consumed by ion, the
 *          high 16 bits are passed on to the respective heap and
 *          can be heap custom
 *
 * Allocate memory in one of the heaps provided in heap mask and return
 * an opaque handle to it.
 */
struct ion_handle *ion_alloc(struct ion_client *client, size_t len,
                 size_t align, unsigned int heap_id_mask,
                 unsigned int flags);

/**
 * ion_free - free a handle
 * @client: the client
 * @handle: the handle to free
 *
 * Free the provided handle.
 */
void ion_free(struct ion_client *client, struct ion_handle *handle);

/**
 * ion_phys - returns the physical address and len of a handle
 * @client: the client
 * @handle: the handle
 * @addr:   a pointer to put the address in
 * @len:    a pointer to put the length in
 *
 * This function queries the heap for a particular handle to get the
 * handle's physical address.  It't output is only correct if
 * a heap returns physically contiguous memory -- in other cases
 * this api should not be implemented -- ion_sg_table should be used
 * instead.  Returns -EINVAL if the handle is invalid.  This has
 * no implications on the reference counting of the handle --
 * the returned value may not be valid if the caller is not
 * holding a reference.
 */
int ion_phys(struct ion_client *client, struct ion_handle *handle,
         ion_phys_addr_t *addr, size_t *len);

/**
 * ion_map_dma - return an sg_table describing a handle
 * @client: the client
 * @handle: the handle
 *
 * This function returns the sg_table describing
 * a particular ion handle.
 */
struct sg_table *ion_sg_table(struct ion_client *client,
                  struct ion_handle *handle);

/**
 * ion_map_kernel - create mapping for the given handle
 * @client: the client
 * @handle: handle to map
 *
 * Map the given handle into the kernel and return a kernel address that
 * can be used to access this address.
 */
void *ion_map_kernel(struct ion_client *client, struct ion_handle *handle);

/**
 * ion_unmap_kernel() - destroy a kernel mapping for a handle
 * @client: the client
 * @handle: handle to unmap
 */
void ion_unmap_kernel(struct ion_client *client, struct ion_handle *handle);

/**
 * ion_share_dma_buf() - given an ion client, create a dma-buf fd
 * @client: the client
 * @handle: the handle
 */
int ion_share_dma_buf(struct ion_client *client, struct ion_handle *handle);

/**
 * ion_import_dma_buf() - given an dma-buf fd from the ion exporter get handle
 * @client: the client
 * @fd:     the dma-buf fd
 *
 * Given an dma-buf fd that was allocated through ion via ion_share_dma_buf,
 * import that fd and return a handle representing it.  If a dma-buf from
 * another exporter is passed in this function will return ERR_PTR(-EINVAL)
 */
struct ion_handle *ion_import_dma_buf(struct ion_client *client, int fd);

#endif /* __KERNEL__ */

/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct ion_allocation_data {
 size_t len;
 size_t align;
 unsigned int heap_mask;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 unsigned int flags;
 struct ion_handle *handle;
};
struct ion_fd_data {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct ion_handle *handle;
 int fd;
};
struct ion_handle_data {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct ion_handle *handle;
};
struct ion_custom_data {
 unsigned int cmd;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 unsigned long arg;
};
/* struct ion_flush_data - data passed to ion for flushing caches
 *
 * @handle: handle with data to flush
 * @fd:   fd to flush
 * @vaddr:  userspace virtual address mapped with mmap
 * @offset: offset into the handle to flush
 * @length: length of handle to flush
 *
 * Performs cache operations on the handle. If p is the start address
 * of the handle, p + offset through p + offset + length will have
 * the cache operations performed
 */
struct ion_flush_data {
  struct ion_handle *handle;
  int fd;
  void *vaddr;
  unsigned int offset;
  unsigned int length;
};

/* struct ion_flag_data - information about flags for this buffer
 *
 * @handle: handle to get flags from
 * @flags:  flags of this handle
 *
 * Takes handle as an input and outputs the flags from the handle
 * in the flag field.
 */
struct ion_flag_data {
  struct ion_handle *handle;
  unsigned long flags;
};
#define ION_IOC_MAGIC 'I'
#define ION_IOC_ALLOC _IOWR(ION_IOC_MAGIC, 0,   struct ion_allocation_data)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define ION_IOC_FREE _IOWR(ION_IOC_MAGIC, 1, struct ion_handle_data)
#define ION_IOC_MAP _IOWR(ION_IOC_MAGIC, 2, struct ion_fd_data)
#define ION_IOC_SHARE _IOWR(ION_IOC_MAGIC, 4, struct ion_fd_data)
#define ION_IOC_IMPORT _IOWR(ION_IOC_MAGIC, 5, struct ion_fd_data)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define ION_IOC_SYNC _IOWR(ION_IOC_MAGIC, 7, struct ion_fd_data)
#define ION_IOC_CUSTOM _IOWR(ION_IOC_MAGIC, 6, struct ion_custom_data)

/**
 * DOC: ION_IOC_CLEAN_CACHES - clean the caches
 *
 * Clean the caches of the handle specified.
 */
#define ION_IOC_CLEAN_CACHES  _IOWR(ION_IOC_MAGIC, 20, \
            struct ion_flush_data)
/**
 * DOC: ION_MSM_IOC_INV_CACHES - invalidate the caches
 *
 * Invalidate the caches of the handle specified.
 */
#define ION_IOC_INV_CACHES  _IOWR(ION_IOC_MAGIC, 21, \
            struct ion_flush_data)
/**
 * DOC: ION_MSM_IOC_CLEAN_CACHES - clean and invalidate the caches
 *
 * Clean and invalidate the caches of the handle specified.
 */
#define ION_IOC_CLEAN_INV_CACHES  _IOWR(ION_IOC_MAGIC, 22, \
            struct ion_flush_data)
#endif

