#include "conurbation/uefi/tables.hh"
#include "jones/jones_loaded_image.hh"

extern "C" auto kernel_main(Conurbation::UEFI::handle_t ImageHandle, Conurbation::UEFI::efi_system_table_t* SystemTable) -> Conurbation::UEFI::status_t {

    Jones::jones_loaded_image_p* jones_loaded_;// = reinterpret_cast<Jones::jones_loaded_image_p*>(ImageHandle);
    SystemTable->BootServices->OpenProtocol(ImageHandle, &Conurbation::UEFI::protocol_guid_v<Jones::jones_loaded_image_p>, reinterpret_cast<void**>(&jones_loaded_), ImageHandle, nullptr, 2);



    return Conurbation::UEFI::status_t::Success;

}
