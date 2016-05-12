#include "uefi/tables.h"

UEFI::uint32_t foo;

extern "C" auto efiabi efi_main(UEFI::handle_t ImageHandle, UEFI::efi_system_table_t* SystemTable) -> UEFI::status_t
{

    SystemTable->ConOut->OutputString(SystemTable->ConOut,
        u"     _____                        _           _   _             \r\n        /  __ \\                      | |       "
        u"  | | (_)            \r\n        | /  \\/ ___  _ __  _   _ _ __| |__   __ _| |_ _  ___  _ __  \r\n        | |    / "
        u"_ \\| '_ \\| | | | '__| '_ \\ / _` | __| |/ _ \\| '_ \\ \r\n        | \\__/\\ (_) | | | | |_| | |  | |_) | (_| | "
        u"|_| | (_) | | | |\r\n         \\____/\\___/|_| |_|\\__,_|_|  |_.__/ \\__,_|\\__|_|\\___/|_| |_|\r\n                 "
        u"                                                   \r\n");

    return UEFI::status_t::Success;
}
