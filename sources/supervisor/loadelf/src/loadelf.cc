#include "uefi/tables.h"
#include "uefi/protocol/loaded_image.h"

extern "C" void loadElf64ImageFromBuffer(void* imageBase, uintptr_t imageSize);

extern "C" efi_status_t efiapi efi_main (efi_handle_t imageHandle, efi_system_table_t* systemTable) {

    efi_handle_t* targetHandle = NULL;

    
    return Success;
    
}

extern "C" efi_status_t efiapi unloadElfImage (efi_handle_t imageHandle) {
    
}

extern "C" efi_status_t efiapi loadElfImage (efi_handle_t parentHandle, efi_system_table_t* systemTable, efi_device_path_p* file, efi_handle_t* imageHandle) {
    
    imageHandle = NULL;
    
    efi_loaded_image_p* imageProto;
    /* status = */ systemTable->BootServices->AllocatePool(EfiConventionalMemory, sizeof(efi_loaded_image_p), &imageProto);
    
    
    
    imageProto->ParentHandle = parentHandle;
    imageProto->SystemTable = systemTable;
    // imageProto->DeviceHandle 
    imageProto->FilePath = file;
    imageProto->LoadOptionsSize = 0;
    imageProto->LoadOptions = NULL;
    // imageProto->ImageBase
    // imageProto->ImageSize
    imageProto->ImageCodeType = EfiLoaderCode;
    imageProto->ImageDataType = EfiLoaderData;
    imageProto->Unload = &unloadElfImage;
    
    systemTable->BootServices->InstallProtocolInterface(imageHandle, efi_protocol<efi_loaded_image_p>::guid, EFI_NATIVE_INTERFACE, (void**)imageProto);
    return Success;
    
}

