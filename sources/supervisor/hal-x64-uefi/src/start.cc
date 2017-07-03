#include "ll/uefi/abi.hh"
#include "ll/uefi/tables/system.hh"
#include "ll/uefi/protocols/graphics_output.hh"
#include "ll/uefi/protocols/loaded_image.hh"
#include "ll/elf64.hh"

extern elf64_dyn_t _DYNAMIC[];

namespace Conurbation {
auto hal_main(ll::UEFI::handle_t ImageHandle, ll::UEFI::Tables::system_table_t* SystemTable) -> ll::UEFI::status_t;
}

namespace {

    typedef void (preinit_entry_point_f)(ll::UEFI::handle_t, ll::UEFI::Tables::system_table_t*);
    typedef void (init_entry_point_f)();

    extern "C" void enable_sse();

}

[[gnu::section(".init_array")]]
init_entry_point_f* init[]  = {
    &enable_sse
};

[[gnu::section(".text.start")]]
efiabi extern "C" auto _start(ll::UEFI::handle_t ImageHandle, ll::UEFI::Tables::system_table_t* SystemTable) -> ll::UEFI::status_t {

    ll::UEFI::status_t _r;
    ll::UEFI::Protocols::loaded_image_p* LoadedImage;

    _r = SystemTable->BootServices->HandleProtocol(ImageHandle, &ll::UEFI::protocol_guid_v<ll::UEFI::Protocols::loaded_image_p>, reinterpret_cast<void**>(&LoadedImage));
    if (_r != ll::UEFI::status_t::Success) return ll::UEFI::status_t::Aborted;

    uintptr_t ImageBase = reinterpret_cast<uintptr_t>(LoadedImage->ImageBase);

    SystemTable->console_out->ClearScreen(SystemTable->console_out);
    SystemTable->console_out->OutputString(SystemTable->console_out, u"Hello World!\r\n");

    enable_sse();

    // Iterate through _DYNAMIC doing useful things, like getting the addresses of the preinit and init arrays

    preinit_entry_point_f** preinit_array = nullptr;
    init_entry_point_f** init_array = nullptr;
    elf64_rela_t* rela_array = nullptr;
    size_t preinit_array_count = 0, init_array_count = 0, relasz = 0, relaent = 0;

    elf64_dyn_t* dyn = _DYNAMIC;
    while (dyn->d_tag != elf_dynamic_tag_t::Null) {
        switch (dyn->d_tag) {
        case elf_dynamic_tag_t::InitArray:
            init_array = reinterpret_cast<init_entry_point_f**>(dyn->d_un.d_ptr);
            break;
        case elf_dynamic_tag_t::InitArraySz:
            init_array_count = dyn->d_un.d_val / sizeof(init_entry_point_f*);
            break;
        case elf_dynamic_tag_t::PreinitArray:
            preinit_array = reinterpret_cast<preinit_entry_point_f**>(dyn->d_un.d_ptr);
            break;
        case elf_dynamic_tag_t::PreinitArraySz:
            preinit_array_count = dyn->d_un.d_val / sizeof(preinit_entry_point_f*);
            break;
        case elf_dynamic_tag_t::RelaSz:
            relasz = dyn->d_un.d_val;
            if (!!relaent) relaent = relasz / relaent;
        case elf_dynamic_tag_t::RelaEnt:
            relaent = dyn->d_un.d_val;
            if (!!relasz) relaent = relasz / relaent;
        case elf_dynamic_tag_t::Rela:
            rela_array = reinterpret_cast<elf64_rela_t*>(dyn->d_un.d_ptr);
            break;
        default:

            break;
        }
        ++dyn;
    }

    for (int i = 0; i < relaent; ++i)
    {
        auto reloc = rela_array[i];
        uint64_t* _t;
        switch (reloc.type()) {
        case elf64_reloc_type_t::amd64_relative:
            _t = reinterpret_cast<uint64_t*>(reloc.r_offset + ImageBase);
            *_t += ImageBase;
            break;
        }
    }

    // Preinit immediately after relocations
    for (int i = 0; i < preinit_array_count; ++i)
    {
        // NOTE: Non-standard behaviour here, but we are a kernel. Preinitializers in the core are passed the UEFI context
        preinit_array[i](ImageHandle, SystemTable);
    }

    // We can now make non-trivial calls

    // Init
    for (int i = 0; i < init_array_count; ++i)
    {
        init_array[i]();
    }

    return Conurbation::hal_main(ImageHandle, SystemTable);

    // We're going to want to self-relocate into the higher-half, but we can't do that before ExitBootServices.
    // So gather ye data from UEFI now...

    ll::UEFI::Protocols::graphics_output_p* gop;
    SystemTable->BootServices->LocateProtocol(&ll::UEFI::protocol_guid_v<ll::UEFI::Protocols::graphics_output_p>, nullptr, reinterpret_cast<void**>(&gop));

    // Exit Boot Services (:o)
    uintptr_t memoryMapSize = 0, memoryMapKey, memoryMapDescriptorSize;
    uint32_t memoryMapDescriptorVersion;
    ll::UEFI::memory_descriptor_t* memoryMap = nullptr;

    SystemTable->BootServices->GetMemoryMap(&memoryMapSize, memoryMap, &memoryMapKey, &memoryMapDescriptorSize, &memoryMapDescriptorVersion);
    memoryMapSize += memoryMapDescriptorSize;
    SystemTable->BootServices->AllocatePool(ll::UEFI::memory_type_t::OsData, memoryMapSize, reinterpret_cast<void**>(&memoryMap));
    SystemTable->BootServices->GetMemoryMap(&memoryMapSize, memoryMap, &memoryMapKey, &memoryMapDescriptorSize, &memoryMapDescriptorVersion);
    SystemTable->BootServices->ExitBootServices(ImageHandle, memoryMapKey);

    //SystemTable->RuntimeServices->SetVirtualAddressMap();

    __builtin_unreachable();

}
