#pragma once

void setup_vm(void);

void create_mapping(uint64 *pgtbl, uint64 va, uint64 pa, uint64 sz, uint64 perm);

void setup_vm_final(void);