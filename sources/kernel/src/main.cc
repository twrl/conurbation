#include "uefi/tables.h"
#include "conurbation/hwres/addrspace.h"
#include "conurbation/mem/liballoc.h"
#include "conurbation/status.h"

namespace Conurbation {

    auto uefi_address_map_import(UEFI::efi_system_table_t* SystemTable, Conurbation::HwRes::address_space_t* Phy,
        Conurbation::HwRes::address_space_t* Virt) -> _<std::uintptr_t>;

    extern "C" auto kernel_main(UEFI::handle_t ImageHandle, UEFI::efi_system_table_t* SystemTable) -> UEFI::status_t
    {

        SystemTable->ConOut->SetAttribute(SystemTable->ConOut, 0x0A);

        SystemTable->ConOut->OutputString(SystemTable->ConOut, u"         _____                        _           _   _      "
                                                               u"       \r\n        /  __ \\                      | |   "
                                                               u"    "
                                                               u"  | | (_)            \r\n        | /  \\/ ___  _ __  _   _ _ "
                                                               u"__| |__   __ _| |_ _  ___  _ __  \r\n        | |    / "
                                                               u"_ \\| '_ \\| | | | '__| '_ \\ / _` | __| |/ _ \\| '_ \\ \r\n "
                                                               u"       | \\__/\\ (_) | | | | |_| | |  | |_) | (_| | "
                                                               u"|_| | (_) | | | |\r\n         \\____/\\___/|_| |_|\\__,_|_|  "
                                                               u"|_.__/ \\__,_|\\__|_|\\___/|_| |_|\r\n                 "
                                                               u"                                                   \r\n");

        SystemTable->ConOut->SetAttribute(SystemTable->ConOut, 0x0F);

        SystemTable->ConOut->OutputString(SystemTable->ConOut,
            u"Conurbation Operating System v "
            u"0.2+0.57721566490153286060651209008240243104215933593992\r\n      "
            u"                             [Euler-Mascheroni]\r\n\r\n");

        SystemTable->ConOut->SetAttribute(SystemTable->ConOut, 0x07);
        SystemTable->ConOut->OutputString(SystemTable->ConOut,
            u"For sanity: we're running on an x86-64 compatible with SSE enabled and UEFI 2.x compatible firmware.\r\n");

        HwRes::address_space_t* Phy = new HwRes::address_space_t(0, -1);
        HwRes::address_space_t* Virt = new HwRes::address_space_t(0, -1);
        Phy->first()->usage(HwRes::address_usage_t::noexist)->backing_mode(HwRes::address_backing_t::none);
        Virt->first()->usage(HwRes::address_usage_t::noexist)->backing_mode(HwRes::address_backing_t::none);

        _<std::uintptr_t> efi_map_key = uefi_address_map_import(SystemTable, Phy, Virt);

        return UEFI::status_t::Success;
    }

    auto uefi_address_map_import(UEFI::efi_system_table_t* SystemTable, Conurbation::HwRes::address_space_t* Phy,
        Conurbation::HwRes::address_space_t* Virt) -> _<std::uintptr_t>
    {
        std::uintptr_t map_size = 1;
        std::uintptr_t descr_size;
        std::uintptr_t map_key;
        std::uint32_t descr_version;
        void* map = nullptr;

        // typedef status_t(efiabi efi_get_memory_map_f)(uintptr_t* memoryMapSize, memory_descriptor_t* memoryMap, uintptr_t*
        // mapKey, uintptr_t* descriptorSize, uint32_t* descriptorVersion);
        SystemTable->BootServices->GetMemoryMap(
            &map_size, reinterpret_cast<UEFI::memory_descriptor_t*>(map), &map_key, &descr_size, &descr_version);

        void* map_buffer = kmalloc(map_size);
        // if (!map_buffer)
        //    return status_t::MemoryAllocationError;

        map = static_cast<void*>(map_buffer);
        SystemTable->BootServices->GetMemoryMap(
            &map_size, reinterpret_cast<UEFI::memory_descriptor_t*>(map), &map_key, &descr_size, &descr_version);

        std::uintptr_t map_offset = reinterpret_cast<std::uintptr_t>(map);
        std::uintptr_t map_limit = map_offset + map_size;
        while (map_offset < map_limit) {
            UEFI::memory_descriptor_t* descriptor = reinterpret_cast<UEFI::memory_descriptor_t*>(map_offset);
            HwRes::address_region_t* pr = Phy->define_region(descriptor->PhysicalStart, descriptor->NumberOfPages * 4096)
                                              ->backing_mode(HwRes::address_backing_t::self);
            HwRes::address_region_t* vr = Virt->define_region(descriptor->VirtualStart, descriptor->NumberOfPages * 4096);

            switch (descriptor->Type) {
                case UEFI::memory_type_t::EfiConventionalMemory:
                    vr->backing_mode(HwRes::address_backing_t::page)
                        ->backing_region(pr)
                        ->usage(HwRes::address_usage_t::available);
                    pr->usage(HwRes::address_usage_t::inuse);
                    break;
                case UEFI::memory_type_t::EfiBootServicesCode:
                case UEFI::memory_type_t::EfiBootServicesData:
                case UEFI::memory_type_t::EfiLoaderCode:
                case UEFI::memory_type_t::EfiLoaderData:
                    vr->backing_mode(HwRes::address_backing_t::page)
                        ->backing_region(pr)
                        ->usage(HwRes::address_usage_t::reclaimable)
                        ->reclaim_policy(HwRes::address_reclaim_t::EFI_boot_services);
                    pr->usage(HwRes::address_usage_t::inuse);
                    break;
                case UEFI::memory_type_t::EfiACPIReclaimMemory:
                    vr->backing_mode(HwRes::address_backing_t::page)
                        ->backing_region(pr)
                        ->usage(HwRes::address_usage_t::reclaimable)
                        ->reclaim_policy(HwRes::address_reclaim_t::ACPI);
                    pr->usage(HwRes::address_usage_t::inuse);
                    break;
                case UEFI::memory_type_t::EfiRuntimeServicesCode:
                case UEFI::memory_type_t::EfiRuntimeServicesData:
                case UEFI::memory_type_t::EfiACPIMemoryNVS:
                    vr->backing_mode(HwRes::address_backing_t::page)
                        ->backing_region(pr)
                        ->usage(HwRes::address_usage_t::reserved);
                    pr->usage(HwRes::address_usage_t::reserved);
                    break;
                case UEFI::memory_type_t::EfiMemoryMappedIO:
                    pr->backing_mode(HwRes::address_backing_t::mmio);
                    vr->backing_mode(HwRes::address_backing_t::page)->backing_region(pr)->usage(HwRes::address_usage_t::inuse);
                    break;
                case UEFI::memory_type_t::EfiUnusableMemory:
                default: // TODO: Should we default to unusable, reserved, or conventional?
                    vr->backing_mode(HwRes::address_backing_t::none)->usage(HwRes::address_usage_t::available);
                    pr->usage(HwRes::address_usage_t::unusable);
                    break;
            }

            map_offset += descr_size;
        }

        return map_key;
    }

    extern "C" auto preinit_test(UEFI::handle_t ImageHandle, UEFI::efi_system_table_t* SystemTable) -> void
    {
        SystemTable->ConOut->OutputString(SystemTable->ConOut, u"Preinit world! (innit...)\r\n");
    }
}
