#include "ll/uefi/abi.hh"
#include "ll/uefi/protocols/device_path_utilities.hh"
#include "ll/uefi/protocols/device_path.hh"
#include "ll/uefi/protocols/file.hh"
#include "ll/uefi/protocols/graphics_output.hh"
#include "ll/uefi/protocols/load_file.hh"
#include "ll/uefi/protocols/loaded_image.hh"
#include "ll/uefi/protocols/simple_file_system.hh"
#include "ll/uefi/protocols/simple_text_input.hh"
#include "ll/uefi/protocols/simple_text_output.hh"

namespace ll::UEFI {

    template <> constexpr guid_t protocol_guid_v<Protocols::device_path_utilities_p> = "0379BE4E-D706-437d-B037-EDB82FB772A4"_guid;
    template <> constexpr guid_t protocol_guid_v<Protocols::device_path_p> = "09576e91-6d3f-11d2-8e39-00a0c969723b"_guid;

    template <> constexpr guid_t protocol_guid_v<Protocols::graphics_output_p> = "9042a9de-23dc-4a38-96fb-7aded080516a"_guid;
    template <> constexpr guid_t protocol_guid_v<Protocols::loaded_image_p> = "5B1B31A1-9562-11d2-8E3F-00A0C969723B"_guid;
    template <> constexpr guid_t protocol_guid_v<Protocols::simple_file_system_p> = "0964e5b22-6459-11d2-8e39-00a0c969723b"_guid;
    template <> constexpr guid_t protocol_guid_v<Protocols::simple_text_input_p> = "387477c1-69c7-11d2-8e39-00a0c969723b"_guid;
    template <> constexpr guid_t protocol_guid_v<Protocols::simple_text_output_p> = "387477c2-69c7-11d2-8e39-00a0c969723b"_guid;

}
