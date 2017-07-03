#include "ll/uefi/abi.hh"
#include "ll/uefi/tables/system.hh"
#include "conurbation/system_env.hh"

namespace Conurbation {

    auto exec_main(system_environment_t&) -> void;

    system_environment_t root_env;

    auto hal_main(ll::UEFI::handle_t ImageHandle, ll::UEFI::Tables::system_table_t* SystemTable) -> ll::UEFI::status_t {

        SystemTable->console_out->OutputString(SystemTable->console_out, u"HAL Main...\r\n");

        exec_main(root_env);

        return ll::UEFI::status_t::Success;

    }

}
