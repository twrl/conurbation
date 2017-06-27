#include "ll/uefi/abi.hh"
#include "ll/uefi/tables/system.hh"
#include "ll/uefi/protocols/graphics_output.hh"
#include "ll/elf64.hh"

extern elf64_dyn_t _DYNAMIC[];

namespace Conurbation {
auto exec_main() -> void;
}

namespace {

    typedef void (preinit_entry_point_f)(ll::UEFI::handle_t, ll::UEFI::Tables::system_table_t*);
    typedef void (init_entry_point_f)();

    extern "C" void enable_sse();

}

[[gnu::section(".text.start")]]
extern "C" auto _start(ll::UEFI::handle_t ImageHandle, ll::UEFI::Tables::system_table_t* SystemTable) -> ll::UEFI::status_t {

    enable_sse();

    // Iterate through _DYNAMIC doing useful things, like getting the addresses of the preinit and init arrays

    preinit_entry_point_f** preinit_array = nullptr;
    init_entry_point_f** init_array = nullptr;
    size_t preinit_array_count, init_array_count;

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
        default:
            break;
        }
        ++dyn;
    }

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

    Conurbation::exec_main();

    __builtin_unreachable();

}
