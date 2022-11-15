/**
 * @file mm/pages.h
 * @author Cristian Bosin (cmaruanbosin@gmail.com)
 * @brief This header contains the signature of functions used manage pages
 within the kernel.
 * @version 0.1
 * @date 2022-10-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#if !defined(KERNEL_MM_PAGES_H)
#define KERNEL_MM_PAGES_H

#include "list.h"

/// @brief Allocate a page
/// @return Address to page
void *kpalloc();

/// @brief Free a page
/// @param page Page address. Must be aligned
void kpfree(void *page);

/// @brief Free range of memory. `start` and `end` are not required to be
/// page aligned
/// @param start Address belonging to the first page to be freed
/// @param end Address belonging to the last page to be freed
void kpfree_range(void *start, void *end);

#endif  // KERNEL_MM_PAGES_H
