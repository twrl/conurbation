#pragma once

#include "uefi/efitypes.h"

struct efi_file_p;

extern "C" {
    typedef efi_status_t (efi_file_open_f)(efi_file_p* this, efi_file_p** newHandle, char16_t* fileName, uint64_t openMode, uint64_t attributes);
    typedef efi_status_t (efi_file_close_f)(efi_file_p* this);
    typedef efi_status_t (efi_file_delete_f)(efi_file_p* this);
    typedef efi_status_t (efi_file_read_f)(efi_file_p* this, uintptr_t* bufferSize, void* buffer);
    typedef efi_status_t (efi_file_write_f)(efi_file_p* this, uintptr_t* bufferSize, void* buffer);
    typedef efi_status_t (efi_file_set_position_f)(efi_file_p* this, uint64_t position);
    typedef efi_status_t (efi_file_get_position_f)(efi_file_p* this, uint64_t* position);
    typedef efi_status_t (efi_file_get_info_f)(efi_file_p* this, guid_t* informationType, uintptr_t* bufferSize, void* buffer);
    typedef efi_status_t (efi_file_set_info_f)(efi_file_p* this, guid_t* informationType, uintptr_t bufferSize, void* buffer);
    typedef efi_status_t (efi_file_flush_f)(efi_file_p* this);
}

struct efi_file_p {
            uint64_t                    Revision;
    efiapi  efi_file_open_f*            Open;
    efiapi  efi_file_close_f*           Close;
    efiapi  efi_file_delete_f*          Delete;
    efiapi  efi_file_read_f*            Read;
    efiapi  efi_file_write_f*           Write;
    efiapi  efi_file_get_position_f*    GetPosition;
    efiapi  efi_file_set_position_f*    SetPosition;
    efiapi  efi_file_get_info_f*        GetInfo;
    efiapi  efi_file_set_info_f*        SetInfo;
    efiapi  efi_file_flush_f*           Flush;
};

struct efi_file_info_t {
    uint64_t        Size;
    uint64_t        FileSize;
    uint64_t        PhysicalSize;
    efi_time_t      CreateTime;
    efi_time_t      LastAccessTime;
    efi_time_t      ModificationTime;
    uint64_t        Attribute;
    //char16_t      FileName;
};
