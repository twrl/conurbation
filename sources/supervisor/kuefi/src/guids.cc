#include "conurbation/uefi/protocol/device_path.hh"
#include "conurbation/uefi/protocol/file.hh"
#include "conurbation/uefi/protocol/graphics_output.hh"
#include "conurbation/uefi/protocol/loaded_image.hh"
#include "conurbation/uefi/protocol/simple_file_system.hh"
#include "conurbation/uefi/protocol/simple_text_input.hh"
#include "conurbation/uefi/protocol/simple_text_output.hh"

using namespace Conurbation::UEFI;

template <> constexpr guid_t protocol_guid_v<efi_device_path_utilities_p> = "0379BE4E-D706-437d-B037-EDB82FB772A4"_guid;
template <> constexpr guid_t protocol_guid_v<efi_device_path_p> = "09576e91-6d3f-11d2-8e39-00a0c969723b"_guid;

template <> constexpr guid_t protocol_guid_v<efi_graphics_output_p> = "9042a9de-23dc-4a38-96fb-7aded080516a"_guid;
template <> constexpr guid_t protocol_guid_v<efi_loaded_image_p> = "5B1B31A1-9562-11d2-8E3F-00A0C969723B"_guid;
template <> constexpr guid_t protocol_guid_v<efi_simple_file_system_p> = "0964e5b22-6459-11d2-8e39-00a0c969723b"_guid;
template <> constexpr guid_t protocol_guid_v<efi_simple_text_input_p> = "387477c1-69c7-11d2-8e39-00a0c969723b"_guid;
template <> constexpr guid_t protocol_guid_v<efi_simple_text_output_p> = "387477c2-69c7-11d2-8e39-00a0c969723b"_guid;
