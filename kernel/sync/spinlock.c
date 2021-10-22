#include <stdatomic.h>
#include <icebox/sync/spinlock.h>

__attribute__((noinline)) void sl_lock(struct spinlock* sl)
{
    while (atomic_flag_test_and_set(&sl->__flag)) {}
    return;
}

void sl_release(struct spinlock* sl)
{
    atomic_flag_clear(&sl->__flag);
}

