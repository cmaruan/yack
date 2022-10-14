#include "kernel.h"
#include "memlayout.h"
#include "mm/pages.h"

struct page {
        uint32_t magic_number;
        struct list_head free_list;
};

LIST_HEAD(free_pages_);

static void kfree_(void *address);

void
kfree_range(void *start, void *end)
{
        klog(KDEBUG, "kfree_range(%p, %p)\n", start, end);
        void *first = (void *)MM_PAGEUP(start);
        void *last = (void *)MM_PAGEDOWN(end);
        klog(KDEBUG, "pages: first = %p, last = %p, count = %u\n", first, last,
             ((last - first) / MM_PGSIZE));
        for (void *curr = first; curr < last; curr += MM_PGSIZE) {
                kfree_(curr);
        }
}

static void
kfree_(void *address)
{
        struct page *page = (struct page *)address;
        page->magic_number = 0xDEADBEAF;
        list_add_tail(&page->free_list, &free_pages_);
}

void
kfree(void *address)
{
        kassert(address && mm_is_page_aligned(address));
        struct page *page = (struct page *)address;
        kassert(page->magic_number == 0xDEADBEAF);
        kfree_(page);
}