#ifndef __KERNEL_GDT_H__
#define __KERNEL_GDT_H__

#include <stdint.h>

/*
 * GDT creation and loading functions
 */
void gdt_load_global_descirptor_table(void);

void gdt_create_flat_layout(void);

#endif
