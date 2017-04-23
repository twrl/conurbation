#pragma once

#include "conurbation/uefi/efi_types.hh"
#include "conurbation/uefi/abi.hh"

namespace Conurbation::UEFI
{

    struct efi_file_p;

    typedef status_t(efiabi efi_file_open_f)(
        efi_file_p * this, efi_file_p * *newHandle, const char16_t* fileName, uint64_t openMode, uint64_t attributes);
    typedef status_t(efiabi efi_file_close_f)(efi_file_p * this);
    typedef status_t(efiabi efi_file_delete_f)(efi_file_p * this);
    typedef status_t(efiabi efi_file_read_f)(efi_file_p * this, uintptr_t * bufferSize, void* buffer);
    typedef status_t(efiabi efi_file_write_f)(efi_file_p * this, uintptr_t * bufferSize, void* buffer);
    typedef status_t(efiabi efi_file_set_position_f)(efi_file_p * this, uint64_t position);
    typedef status_t(efiabi efi_file_get_position_f)(efi_file_p * this, uint64_t * position);
    typedef status_t(efiabi efi_file_get_info_f)(
        efi_file_p * this, guid_t * informationType, uintptr_t * bufferSize, void* buffer);
    typedef status_t(efiabi efi_file_set_info_f)(
        efi_file_p * this, guid_t * informationType, uintptr_t bufferSize, void* buffer);
    typedef status_t(efiabi efi_file_flush_f)(efi_file_p * this);

    struct efi_file_p {
        uint64_t Revision;
        efi_file_open_f* Open;
        efi_file_close_f* Close;
        efi_file_delete_f* Delete;
        efi_file_read_f* Read;
        efi_file_write_f* Write;
        efi_file_get_position_f* GetPosition;
        efi_file_set_position_f* SetPosition;
        efi_file_get_info_f* GetInfo;
        efi_file_set_info_f* SetInfo;
        efi_file_flush_f* Flush;
    };

    struct efi_file_info_t {
        uint64_t Size;
        uint64_t FileSize;
        uint64_t PhysicalSize;
        time_t CreateTime;
        time_t LastAccessTime;
        time_t ModificationTime;
        uint64_t Attribute;
        // char16_t      FileName;
    };
}
