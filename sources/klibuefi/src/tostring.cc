#include "uefi/efi_types.h"

using namespace UEFI;

__attribute__((pure)) const char16_t* UEFI::efiStatusToString(status_t status)
{
    switch (status) {
        case status_t::Success:
            return u"Success";
        case status_t::LoadError:
            return u"Load Error";
        case status_t::InvalidParameter:
            return u"Invalid Parameter";
        case status_t::Unsupported:
            return u"Unsupported";
        case status_t::BadBufferSize:
            return u"Bad Buffer Size";
        case status_t::BufferTooSmall:
            return u"Buffer Too Small";
        case status_t::NotReady:
            return u"Not Ready";
        case status_t::DeviceError:
            return u"Device Error";
        case status_t::WriteProtected:
            return u"Write Protected";
        case status_t::OutOfResources:
            return u"Out Of Resources";
        case status_t::VolumeCorrupted:
            return u"Volume Corrupted";
        case status_t::VolumeFull:
            return u"Volume Full";
        case status_t::NoMedia:
            return u"No Media";
        case status_t::MediaChanged:
            return u"Media Changed";
        case status_t::NotFound:
            return u"Not Found";
        case status_t::AccessDenied:
            return u"AccessDenied";
        case status_t::NoResponse:
            return u"No Response";
        case status_t::NoMapping:
            return u"No Mapping";
        case status_t::Timeout:
            return u"Timeout";
        case status_t::NotStarted:
            return u"Not Started";
        case status_t::AlreadyStarted:
            return u"AlreadyStarted";
        case status_t::Aborted:
            return u"Aborted";
        case status_t::ICMPError:
            return u"ICMP Error";
        case status_t::TFTPError:
            return u"TFTP Error";
        case status_t::ProtocolError:
            return u"Protocol Error";
        case status_t::IncompatibleVersion:
            return u"Incompatible Version";
        case status_t::SecurityViolation:
            return u"Security Violation";
        case status_t::CRCError:
            return u"CRC Error";
        case status_t::EndOfMedia:
            return u"End Of Media";
        case status_t::EndOfFile:
            return u"End Of File";
        default:
            return u"Unknown Error";
    }
}

__attribute__((pure)) const char16_t* UEFI::efiMemoryTypeToString(memory_type_t type)
{

    switch (type) {
        case memory_type_t::EfiReservedMemoryType:
            return u"Reserved Memory";
        case memory_type_t::EfiLoaderCode:
            return u"EFI Loader Code";
        case memory_type_t::EfiLoaderData:
            return u"EFI Loader Data";
        case memory_type_t::EfiBootServicesCode:
            return u"EFI Boot Services Code";
        case memory_type_t::EfiBootServicesData:
            return u"EFI Boot Services Data";
        case memory_type_t::EfiRuntimeServicesCode:
            return u"EFI Runtime Services Code";
        case memory_type_t::EfiRuntimeServicesData:
            return u"EFI Runtime Services Data";
        case memory_type_t::EfiConventionalMemory:
            return u"Free Memory";
        case memory_type_t::EfiUnusableMemory:
            return u"Unusable Memory";
        case memory_type_t::EfiACPIReclaimMemory:
            return u"ACPI Reclaimable Memory";
        case memory_type_t::EfiACPIMemoryNVS:
            return u"ACPI NVS Memory";
        case memory_type_t::EfiMemoryMappedIO:
            return u"Memory Mapped IO";
        case memory_type_t::EfiMemoryMappedIOPortSpace:
            return u"Memory Mapped IO Port Space";
        case memory_type_t::EfiPalCode:
            return u"PAL Code";
        case memory_type_t::OsCode:
            return u"OS Code";
        case memory_type_t::OsData:
            return u"OS Data";
        default:
            return u"Unknown";
    }
}
