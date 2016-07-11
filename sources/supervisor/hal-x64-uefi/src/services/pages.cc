#include "conurbation/services/memory.hh"
#include "conurbation/uefi/tables.h"

namespace Conurbation::Services::Memory
{

    using namespace Conurbation::UEFI;

    class uefi_page_allocator_t : public page_allocator_p {
    private:
        efi_boot_services_t* boot_services_;

    public:
        uefi_page_allocator_t(UEFI::efi_system_table_t* SystemTable)
            : boot_services_(SystemTable->BootServices)
        {
        }

        virtual auto allocate(size_t num_pages) -> uintptr_t
        {
            uintptr_t pages;
            UEFI::status_t st;
            st = boot_services_->AllocatePages(
                UEFI::allocate_type_t::AllocateAnyPages, UEFI::memory_type_t::OsData, num_pages, &pages);

            if (st == UEFI::status_t::Success) {
                return pages;
            }
            else
                return 0;
        }
        virtual auto deallocate(size_t num_pages, uintptr_t base_address) -> void
        {
            boot_services_->FreePages(base_address, num_pages);
        }
    };
}

namespace {

    [[gnu::constructor(1)]] auto uefi_memory_init(
        Conurbation::UEFI::handle_t ImageHandle, Conurbation::UEFI::efi_system_table_t* SystemTable) -> void
    {
        auto _page = new Conurbation::Services::Memory::uefi_page_allocator_t(SystemTable);
        Conurbation::Services::locator_p::get_locator().page_allocator(*_page);
    }
}
