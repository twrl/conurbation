#include "ll.hh"
#include "ll/uefi/tables/system.hh"
#include "jones/jones_loaded_image.hh"

auto kernel_main(ll::UEFI::handle_t ImageHandle, ll::UEFI::Tables::system_table_t* SystemTable) -> ll::UEFI::status_t {

    Jones::jones_loaded_image_p* jones_loaded_;// = reinterpret_cast<Jones::jones_loaded_image_p*>(ImageHandle);
    SystemTable->BootServices->OpenProtocol(ImageHandle, &ll::UEFI::protocol_guid_v<Jones::jones_loaded_image_p>, reinterpret_cast<void**>(&jones_loaded_), ImageHandle, nullptr, 2);



    return ll::UEFI::status_t::Success;

}


[[gnu::weak]]
[[gnu::alias("_Z11kernel_mainPvPN2ll4UEFI6Tables14system_table_tE")]]
extern "C" auto _main(ll::UEFI::handle_t ImageHandle, ll::UEFI::Tables::system_table_t* SystemTable) -> ll::UEFI::status_t;
