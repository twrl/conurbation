#include "uefi/tables.h"
#include "conurbation/hwres/addrspace.hh"
#include "conurbation/mem/liballoc.h"
#include "conurbation/obmodel/svclocate.hh"
#include "conurbation/status.hh"
#include "conurbation/logging.hh"

#include "conurbation/acpi/tables.hh"

int sprintf(char16_t* buf, const char16_t* fmt, ...);
extern "C" auto get_cpuid(uint32_t leaf, uint32_t subleaf, uint32_t* returns) -> void;

namespace Conurbation {

    auto uefi_address_map_import(UEFI::efi_system_table_t* SystemTable, Conurbation::HwRes::address_space_t* Phy,
        Conurbation::HwRes::address_space_t* Virt, logging_t& log) -> _<uintptr_t>;
    auto print_cpuid_info(UEFI::efi_system_table_t* SystemTable, logging_t& log) -> void;
    auto enumerate_acpi_tables(UEFI::efi_system_table_t* SystemTable, logging_t& log) -> void;

    extern "C" auto kernel_main(UEFI::handle_t ImageHandle, UEFI::efi_system_table_t* SystemTable) -> UEFI::status_t
    {
        ObModel::service_locator_t::page_alloc_service(new Mem::efi_alloc_service_t(SystemTable));

        logging_t& log = *new logging_t(SystemTable);

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

        log.info(u"", u"Conurbation Operating System v0.2.1");
        log.debug(u"kernel_main", u"For sanity: we're supposed to be running on an x86-64 "
                                  u"compatible with SSE enabled and UEFI 2.x compatible "
                                  u"firmware. If you can still see this without meeting that "
                                  u"spec then something unholy strange is happening...");

        UEFI::time_t time;
        SystemTable->RuntimeServices->GetTime(&time, nullptr);
        log.info(u"UEFI", u"Current time: %d/%d/%d %d:%d:%d:%d", time.Day, time.Month, time.Year, time.Hour, time.Minute,
            time.Second, time.Nanosecond);

        log.begin_group(u"test");
        log.panic(u"test", u"PANIC!");
        log.error(u"test", u"ERROR");
        log.warn(u"test", u"Warning");
        log.info(u"test", u"info");
        log.trace(u"test", u"trace");
        log.debug(u"test", u"debug");
        log.end_group();

        print_cpuid_info(SystemTable, log);
        enumerate_acpi_tables(SystemTable, log);

        HwRes::address_space_t* Phy = new HwRes::address_space_t(0, -1);
        HwRes::address_space_t* Virt = new HwRes::address_space_t(0, -1);
        // FIXME: Use CPUID 8000_0008h to set the parameters for the Phy and Virt address spaces
        Phy->first()->usage(HwRes::address_usage_t::noexist)->backing_mode(HwRes::address_backing_t::none);
        Virt->first()->usage(HwRes::address_usage_t::noexist)->backing_mode(HwRes::address_backing_t::none);

        _<uintptr_t> efi_map_key = uefi_address_map_import(SystemTable, Phy, Virt, log);

        return UEFI::status_t::Success;
    }

    auto enumerate_acpi_tables(UEFI::efi_system_table_t* SystemTable, logging_t& log) -> void
    {
        log.begin_group(u"ACPI Discovery");

        constexpr guid_t efi_guid_acpi = "8868e871-e4f1-11d3-bc22-0080c73c8881"_guid;
        UEFI::efi_configuration_t* cfg = SystemTable->ConfigurationTable;
        size_t i = 0;
        while (i < SystemTable->NumberOfTableEntries) {
            if (cfg[i].VendorGuid == efi_guid_acpi)
                break;
            ++i;
        };
        if (i >= SystemTable->NumberOfTableEntries) {
            log.warn(u"ACPI", u"ACPI 2.0+ tables not found");
            return;
        }

        ACPI::root_pointer_t* rsdp = reinterpret_cast<ACPI::root_pointer_t*>(cfg[i].VendorTable);

        log.trace(u"ACPI", u"Found RSDptr at 0x%16x", rsdp);

        size_t num_entries = (rsdp->xsdt_address->length - sizeof(ACPI::acpi_sdt_header_t)) / 8;

        log.trace(u"ACPI", u"Found XSDT at 0x%16x with %d ACPI 2.0+ tables", rsdp->xsdt_address, num_entries);

        log.begin_group(u"Tables:");
        i = 0;
        while (i < num_entries) {

            log.trace(u"ACPI", u"0x%16x: %c%c%c%c (length: %d bytes of which %d data)", rsdp->xsdt_address->ptrs[i],
                rsdp->xsdt_address->ptrs[i]->signature[0], rsdp->xsdt_address->ptrs[i]->signature[1],
                rsdp->xsdt_address->ptrs[i]->signature[2], rsdp->xsdt_address->ptrs[i]->signature[3],
                rsdp->xsdt_address->ptrs[i]->length, rsdp->xsdt_address->ptrs[i]->length - sizeof(ACPI::acpi_sdt_header_t));
            i++;
        }
        log.end_group();

        // kfree(reinterpret_cast<void*>(strbuf));
        log.end_group();
    };

    auto print_cpuid_info(UEFI::efi_system_table_t* SystemTable, logging_t& log) -> void
    {
        log.begin_group(u"CPU Info");

        uint32_t _buf[4];
        uint8_t* _buf_byte = reinterpret_cast<uint8_t*>(_buf);

        get_cpuid(0, 0, _buf);
        // char16_t _vendor[15];

        log.trace(u"CPUID", u"vendor: %c%c%c%c%c%c%c%c%c%c%c%c", _buf_byte[4], _buf_byte[5], _buf_byte[6], _buf_byte[7],
            _buf_byte[12], _buf_byte[13], _buf_byte[14], _buf_byte[15], _buf_byte[8], _buf_byte[9], _buf_byte[10],
            _buf_byte[11]);

        log.end_group();
    }

    auto uefi_address_map_import(UEFI::efi_system_table_t* SystemTable, Conurbation::HwRes::address_space_t* Phy,
        Conurbation::HwRes::address_space_t* Virt, logging_t& log) -> _<uintptr_t>
    {
        uintptr_t map_size = 2048;
        uintptr_t descr_size;
        uintptr_t map_key;
        uint32_t descr_version;
        void* map = kmalloc(map_size);

        log.begin_group(u"System Memory Map");

        UEFI::status_t st = UEFI::status_t::BufferTooSmall;

        while (st != UEFI::status_t::Success) {

            if (!map) {
                log.error(u"UEFI", u"Unable to allocate UEFI Memory Map Buffer");

                return status_t::MemoryAllocationError;
            }

            // typedef status_t(efiabi efi_get_memory_map_f)(uintptr_t* memoryMapSize, memory_descriptor_t* memoryMap,
            // uintptr_t*
            // mapKey, uintptr_t* descriptorSize, uint32_t* descriptorVersion);
            st = SystemTable->BootServices->GetMemoryMap(
                &map_size, reinterpret_cast<UEFI::memory_descriptor_t*>(map), &map_key, &descr_size, &descr_version);
            if (st != UEFI::status_t::Success) {
                log.debug(u"UEFI", u"%s (0x%x): Resize buffer to %d bytes", UEFI::efiStatusToString(st), st, map_size);
                map = krealloc(map, map_size);
            }
        }
        // if (!map_buffer)
        //    return status_t::MemoryAllocationError;

        uintptr_t map_offset = reinterpret_cast<uintptr_t>(map);
        uintptr_t map_limit = map_offset + map_size;

        log.debug(u"UEFI", u"Memory map at 0x%16x-%16x (%d bytes) conatins %d descriptors of %d bytes", map_offset, map_limit,
            map_size, map_size / descr_size, descr_size);

        log.trace(u"UEFI", u"    Base-Limit                         |  Pages  | Attributes         | Type    ")
            .trace(
                u"UEFI", u"  -------------------------------------+---------+--------------------+-------------------------");

        while (map_offset < map_limit) {
            UEFI::memory_descriptor_t* descriptor = reinterpret_cast<UEFI::memory_descriptor_t*>(map_offset);
            log.trace(u"UEFI", u"    %16x-%16x  | %6d  | 0x%16x | %s", descriptor->PhysicalStart,
                descriptor->PhysicalStart + (4096 * descriptor->NumberOfPages) - 1, descriptor->NumberOfPages,
                descriptor->Attribute, UEFI::efiMemoryTypeToString(descriptor->Type));

            /*HwRes::address_region_t* pr = Phy->define_region(descriptor->PhysicalStart, descriptor->NumberOfPages * 4096)
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
            }*/

            map_offset += descr_size;
        }

        kfree(map);

        log.end_group();

        return map_key;
    }

    extern "C" auto preinit_test(UEFI::handle_t ImageHandle, UEFI::efi_system_table_t* SystemTable) -> void
    {
        SystemTable->ConOut->OutputString(SystemTable->ConOut, u"Preinit world! (innit...)\r\n");
    }
}
