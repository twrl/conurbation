#include "conurbation/services/locator.hh"
#include "conurbation/services/diag_console.hh"
#include "uefi/tables.h"
#include "uefi/simple_text_output.h"

namespace Conurbation::Services::Console
{

    class uefi_simpletextoutput_diag_console_t : public diagnostic_console_service_p {
    private:
        UEFI::efi_simple_text_output_p* protocol_;
        UEFI::handle_t handle_;
        uintptr_t attribute_ = 0;

    public:
        uefi_simpletextoutput_diag_console_t(UEFI::efi_system_table_t* SystemTable)
            : protocol_(SystemTable->ConOut)
            , handle_(SystemTable->ConsoleOutHandle)
            , attribute_(protocol_->Mode->Attribute)
        {
        }

        virtual ~uefi_simpletextoutput_diag_console_t() {}

        virtual auto clear_screen() -> diagnostic_console_service_p& final
        {
            protocol_->ClearScreen(protocol_);
            return *this;
        }

        virtual auto background_colour() -> ega_colours_t final
        {
            return static_cast<ega_colours_t>((attribute_ & 0xf0) >> 4);
        }
        virtual auto background_colour(ega_colours_t value) -> diagnostic_console_service_p& final
        {
            attribute_ &= 0x0f;
            attribute_ |= static_cast<uintptr_t>(value) << 4;
            protocol_->SetAttribute(protocol_, attribute_);
            return *this;
        }

        virtual auto foreground_colour() -> ega_colours_t final
        {
            return static_cast<ega_colours_t>(attribute_ & 0x0f);
        }
        virtual auto foreground_colour(ega_colours_t value) -> diagnostic_console_service_p& final
        {
            attribute_ &= 0xf0;
            attribute_ |= static_cast<uintptr_t>(value);
            protocol_->SetAttribute(protocol_, attribute_);
            return *this;
        }

        virtual auto width() -> uint16_t final
        {
            uintptr_t _r, _c;
            protocol_->QueryMode(protocol_, protocol_->Mode->Mode, &_c, &_r);
            return _c;
        }

        virtual auto height() -> uint16_t final
        {
            uintptr_t _r, _c;
            protocol_->QueryMode(protocol_, protocol_->Mode->Mode, &_c, &_r);
            return _r;
        }

        virtual auto write(const string_t& msg) -> diagnostic_console_service_p& final
        {
            protocol_->OutputString(protocol_, msg);
            return *this;
        }
        virtual auto write_line() -> diagnostic_console_service_p& final
        {
            protocol_->OutputString(protocol_, u"\r\n");
            return *this;
        }
        virtual auto write_line(const string_t& msg) -> diagnostic_console_service_p& final
        {
            return write(msg).write_line();
        }
    };
}

namespace {

    [[gnu::constructor(10)]] auto uefi_console_init(UEFI::handle_t ImageHandle, UEFI::efi_system_table_t* SystemTable)
        -> void
    {
        auto _con = new Conurbation::Services::Console::uefi_simpletextoutput_diag_console_t(SystemTable);
        Conurbation::Services::locator_p::get_locator().diagnostic_console(*_con);
    }
}
