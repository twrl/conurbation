#include "uefi/tables.h"
#include "uefi/graphics_output.h"
#include "conurbation/hwres/addrspace.hh"
#include "conurbation/mem/liballoc.h"
#include "conurbation/mem/pagealloc.hh"
//#include "conurbation/obmodel/svclocate.hh"
#include "conurbation/obmodel/service.hh"
#include "conurbation/status.hh"
#include "conurbation/logging.hh"
#include "conurbation/rng.hh"

#include "stringbuilder.hh"

#include "string.h"

#include "conurbation/acpi/tables.hh"
#include "conurbation/acpi/madt.hh"
#include "conurbation/acpi/hpet.hh"

int sprintf(char16_t* buf, const char16_t* fmt, ...);
extern "C" auto get_cpuid(uint32_t leaf, uint32_t subleaf, uint32_t* returns) -> void;

namespace Conurbation {

    auto uefi_address_map_import(UEFI::efi_system_table_t* SystemTable, Conurbation::HwRes::address_space_t* Phy,
        Conurbation::HwRes::address_space_t* Virt, logging_p& log) -> _<uintptr_t>;
    auto print_cpuid_info(UEFI::efi_system_table_t* SystemTable, logging_p& log) -> void;
    auto enumerate_acpi_tables(UEFI::efi_system_table_t* SystemTable, logging_p& log) -> void;
    auto uefi_gop_modes(UEFI::efi_system_table_t* SystemTable, service_locator_p& sl) -> void;

    extern "C" auto kernel_main(UEFI::handle_t ImageHandle, UEFI::efi_system_table_t* SystemTable) -> UEFI::status_t
    {

        service_locator_p& services_ = *new service_locator_t();
        services_.set(*new efi_alloc_service_t(SystemTable));
        services_.set(*new logging_t(SystemTable));
        services_.set(*new lfsr_rng_service_t());

        // ObModel::service_locator_t::page_alloc_service(new Mem::efi_alloc_service_t(SystemTable));

        logging_p& log = *static_cast<logging_p*>(services_.get<logging_p>());

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

        log.begin_group(u"String Builder");
        string_builder_t* sb = new string_builder_t();
        sb->append(u"GUID: ").append("8868e871-e4f1-11d3-bc22-0080c73c8881"_guid);
        log.info(u"test", sb->to_string());
        delete sb;
        sb = new string_builder_t();
        sb->append(u"Signed: ").append(-3892).append(u' ').append(-3892L, u"x");
        log.info(u"test", sb->to_string());
        delete sb;
        string_t& str = format(u"GUID {}, uint 0x{16x}", "8868e871-e4f1-11d3-bc22-0080c73c8881"_guid, uint8_t(14));
        log.info(u"test", str);
        log.end_group();

        log.stack_trace(3);

        uefi_gop_modes(SystemTable, services_);

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

    auto enumerate_acpi_tables(UEFI::efi_system_table_t* SystemTable, logging_p& log) -> void
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

            if (strncmp(rsdp->xsdt_address->ptrs[i]->signature, "HPET", 4) == 0) {
                log.begin_group(u"High Precision Event Timer");
                ACPI::hpet_table_t* hpet = reinterpret_cast<ACPI::hpet_table_t*>(rsdp->xsdt_address->ptrs[i]);
                log.trace(
                    u"ACPI", u"HPET with %d comparators (base address 0x%16x)", hpet->num_comparators, hpet->address.address);
                log.end_group();
            }

            if (strncmp(rsdp->xsdt_address->ptrs[i]->signature, "APIC", 4) == 0) {
                ACPI::madt_table_t* mt = reinterpret_cast<ACPI::madt_table_t*>(rsdp->xsdt_address->ptrs[i]);
                size_t length = mt->length - sizeof(ACPI::madt_table_t);
                size_t offset = sizeof(ACPI::madt_table_t);
                log.begin_group(u"Multiple APIC Descriptor Table");
                while (offset < length) {
                    ACPI::madt_entry_header_t* me
                        = reinterpret_cast<ACPI::madt_entry_header_t*>(reinterpret_cast<uintptr_t>(mt) + offset);
                    switch (me->entry_type) {
                        case ACPI::madt_entry_type_t::local_apic:
                            log.trace(u"ACPI", u"Local APIC %d (processor: %d, flags: 0x%8x)",
                                reinterpret_cast<ACPI::madt_entry_lapic_t*>(me)->apic_id,
                                reinterpret_cast<ACPI::madt_entry_lapic_t*>(me)->processor_id,
                                reinterpret_cast<ACPI::madt_entry_lapic_t*>(me)->flags);
                            break;
                        case ACPI::madt_entry_type_t::io_apic:
                            log.trace(u"ACPI", u"IO APIC %d (apic base: 0x%16x, GSI base: %d)",
                                reinterpret_cast<ACPI::madt_entry_ioapic_t*>(me)->apic_id,
                                reinterpret_cast<ACPI::madt_entry_ioapic_t*>(me)->ioapic_address,
                                reinterpret_cast<ACPI::madt_entry_ioapic_t*>(me)->gsi_base);
                            break;
                        case ACPI::madt_entry_type_t::int_src_override:
                            log.trace(u"ACPI", u"Interrupt Source Override (bus %d, irq: %d, gsi: %d)",
                                reinterpret_cast<ACPI::madt_entry_isoverride_t*>(me)->bus_source,
                                reinterpret_cast<ACPI::madt_entry_isoverride_t*>(me)->irq_source,
                                reinterpret_cast<ACPI::madt_entry_isoverride_t*>(me)->gsi);
                        default:
                            /* code */
                            break;
                    }
                    offset += me->entry_length;
                }
                log.end_group();
            }

            ++i;
        }
        log.end_group();

        // kfree(reinterpret_cast<void*>(strbuf));
        log.end_group();
    };

    auto print_cpuid_info(UEFI::efi_system_table_t* SystemTable, logging_p& log) -> void
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

    auto uefi_gop_modes(UEFI::efi_system_table_t* SystemTable, service_locator_p& sl) -> void
    {
        logging_p& log = *static_cast<logging_p*>(sl.get<logging_p>());

        guid_t gop_guid = UEFI::protocol_guid_v<UEFI::efi_graphics_output_p>;

        UEFI::efi_graphics_output_p* gop;
        UEFI::efi_graphics_output_mode_information_t* mi;
        uintptr_t misize;
        UEFI::status_t st = SystemTable->BootServices->LocateProtocol(&gop_guid, nullptr, reinterpret_cast<void**>(&gop));

        if (st == UEFI::status_t::Success) {
            log.begin_group(u"UEFI Graphics Output Protocol");
            log.trace(u"UEFI", u"Active mode: %d (%dx%d)", gop->Mode->Mode, gop->Mode->Info->HorizontalResolution,
                gop->Mode->Info->VerticalResolution);
            log.trace(u"UEFI", u"Framebuffer 0x%16x (%d bytes)", gop->Mode->FramebufferBase, gop->Mode->FramebufferSize);

            log.begin_group(u"Supported Modes");
            for (int i = 0; i < gop->Mode->MaxMode; ++i) {
                gop->QueryMode(gop, i, &misize, &mi);
                switch (mi->PixelFormat) {
                    case UEFI::efi_graphics_pixel_format_t::PixelBlueGreenRedReserved8BitPerColor:
                        log.trace(u"UEFI", u"%d: %d*%d (%d ppsl) 32-bit BGR", i, mi->HorizontalResolution,
                            mi->VerticalResolution, mi->PixelsPerScanLine);
                        break;
                    case UEFI::efi_graphics_pixel_format_t::PixelRedGreenBlueReserved8BitPerColor:
                        log.trace(u"UEFI", u"%d: %d*%d (%d ppsl) 32-bit RGB", i, mi->HorizontalResolution,
                            mi->VerticalResolution, mi->PixelsPerScanLine);
                        break;
                    case UEFI::efi_graphics_pixel_format_t::PixelBltOnly:
                        log.trace(u"UEFI", u"%d: %d*%d (%d ppsl) BLT Only", i, mi->HorizontalResolution,
                            mi->VerticalResolution, mi->PixelsPerScanLine);
                        break;
                    case UEFI::efi_graphics_pixel_format_t::PixelBitMask:
                        log.trace(u"UEFI", u"%d: %d*%d (%d ppsl) %d:%d:%d", i, mi->HorizontalResolution,
                            mi->VerticalResolution, mi->PixelsPerScanLine, __builtin_popcount(mi->PixelInformation.RedMask),
                            __builtin_popcount(mi->PixelInformation.GreenMask),
                            __builtin_popcount(mi->PixelInformation.BlueMask));
                        break;
                    default:
                        log.trace(u"UEFI", u"%d: Unknown Mode", i);
                }
                /* code */
            }
            log.end_group();
            log.end_group();
        }
        else {
            log.warn(u"UEFI", u"Graphics Output Protocol not found");
        }
    }

    auto uefi_address_map_import(UEFI::efi_system_table_t* SystemTable, Conurbation::HwRes::address_space_t* Phy,
        Conurbation::HwRes::address_space_t* Virt, logging_p& log) -> _<uintptr_t>
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

        log.trace(u"UEFI",
               u"    Base-Limit                         | Physical Base      |  Pages  | Attributes         | Type    ")
            .trace(u"UEFI", u"  "
                            u"-------------------------------------+--------------------+--------------------+----------------"
                            u"---------");

        while (map_offset < map_limit) {
            UEFI::memory_descriptor_t* descriptor = reinterpret_cast<UEFI::memory_descriptor_t*>(map_offset);
            log.trace(u"UEFI", u"    %16x-%16x  | 0x%16x | %6d  | 0x%16x | %s", descriptor->VirtualStart,
                descriptor->VirtualStart + (4096 * descriptor->NumberOfPages) - 1, descriptor->PhysicalStart,
                descriptor->NumberOfPages, descriptor->Attribute, UEFI::efiMemoryTypeToString(descriptor->Type));

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
