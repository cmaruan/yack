#include "mm/pages.h"

#include "kernel.h"
#include "memlayout.h"
#include "spinlock.h"

struct page {
        u32 magic_number;
        struct list_head free_list;
};

struct page_registry {
        struct list_head pr_freepages;
        struct spinlock pr_spinlock;
        int pr_shoud_lock;
};
static struct page_registry registry_ = {
    .pr_freepages = LIST_HEAD_INIT(registry_.pr_freepages),
};

void *
kpalloc()
{
        struct page *page;
        if (registry_.pr_shoud_lock)
                spinlock_acquire(&registry_.pr_spinlock);
        page = list_first_entry_or_null(&registry_.pr_freepages, struct page,
                                        free_list);
        list_del(&page->free_list);

        if (registry_.pr_shoud_lock)
                spinlock_release(&registry_.pr_spinlock);

        if (page) {
                kassert(page->magic_number == 0xDEADBEAF);
        }
        // TODO: I might need to map this page somewhere...
        return page;
}

void
kpfree_range(void *start, void *end)
{
        void *first = (void *)MM_PAGEUP(start);
        void *last = (void *)MM_PAGEUP(end);
        klog(DEBUG, "pages: first = %p, last = %p, count = %u\n", first, last,
             ((last - first) / MM_PGSIZE));
        for (void *curr = first; curr < last; curr += MM_PGSIZE) {
                kpfree(curr);
        }
}

void
kpfree(void *address)
{
        kassert(address && mm_is_page_aligned(address));
        struct page *page = (struct page *)address;
        page->magic_number = 0xDEADBEAF;
        if (registry_.pr_shoud_lock)
                spinlock_acquire(&registry_.pr_spinlock);
        list_add_tail(&page->free_list, &registry_.pr_freepages);
        if (registry_.pr_shoud_lock)
                spinlock_release(&registry_.pr_spinlock);
}