#pragma once

#include "ll/uefi/abi.hh"

namespace ll::UEFI::Protocols {

    struct file_p;

    typedef status_t(efiabi file_open_f)(
        file_p * file, file_p** newHandle, const char16_t* fileName, uint64_t openMode, uint64_t attributes);
    typedef status_t(efiabi file_close_f)(file_p * file);
    typedef status_t(efiabi file_delete_f)(file_p * file);
    typedef status_t(efiabi file_read_f)(file_p * file, uintptr_t * bufferSize, void* buffer);
    typedef status_t(efiabi file_write_f)(file_p * file, uintptr_t * bufferSize, void* buffer);
    typedef status_t(efiabi file_set_position_f)(file_p * file, uint64_t position);
    typedef status_t(efiabi file_get_position_f)(file_p * file, uint64_t * position);
    typedef status_t(efiabi file_get_info_f)(
        file_p * file, guid_t * informationType, uintptr_t * bufferSize, void* buffer);
    typedef status_t(efiabi file_set_info_f)(
        file_p * file, guid_t * informationType, uintptr_t bufferSize, void* buffer);
    typedef status_t(efiabi file_flush_f)(file_p * file);

    struct file_p {
        uint64_t Revision;
        file_open_f* Open;
        file_close_f* Close;
        file_delete_f* Delete;
        file_read_f* Read;
        file_write_f* Write;
        file_get_position_f* GetPosition;
        file_set_position_f* SetPosition;
        file_get_info_f* GetInfo;
        file_set_info_f* SetInfo;
        file_flush_f* Flush;
    };

    struct file_info_t {
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
