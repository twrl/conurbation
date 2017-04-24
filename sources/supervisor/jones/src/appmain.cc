#include "conurbation/uefi/tables.hh"
#include "jones/jones.hh"
#include "jones/jones_loadable.hh"

using namespace Conurbation::UEFI;

namespace Jones {

    efiabi extern "C" auto efi_main(handle_t ImageHandle, efi_system_table_t* SystemTable) -> status_t {

        status_t status;

        jones_p* jones_;
        jones_loadable_p* loadable_;

        efi_device_path_p* imagePath_;

        status = SystemTable->BootServices->LocateProtocol(&protocol_guid_v<Jones::jones_p>, nullptr, reinterpret_cast<void**>(&jones_));
        if (status == status_t::NotFound) {
            // Load the driver and try again...
        }



        jones_->GetLoader(imagePath_, &loadable_);
        


        return status_t::Success;



    }

}
