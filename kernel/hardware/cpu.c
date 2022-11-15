#include "hardware/cpu.h"

struct cpu cpus_[1];

struct cpu*
this_cpu()
{
        return &cpus_[0];
}
void
cpu_init()
{
}