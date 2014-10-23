#include "uefi/tables.h"
#include "stdlib.h"
#include "ConSup/mib.h"

char earlyDataArea[16 * 4096];

uintptr_t wkmib_hal_arch[3] = { 2UL, 1UL, 0UL };

extern "C" void halmain(efi_system_table_t* efiSystemTable) {

    init_malloc(earlyDataArea, 16 * 4096);
    set_external_alloc(NULL);

    ConSup::kernel_root_mib = new ConSup::mib_c::mib_c();

    chunk_t ch = {(void*)"x64-uefi", 9 };

    ConSup::kernel_root_mib->set(wkmib_hal_arch, &ch);
}
