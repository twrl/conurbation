#include "conurbation/uefi/console.hh"

namespace Conurbation::UEFI {

    console_logging_t::console_logging_t(efi_simple_text_output_p* stop): ConOut_(stop) {}

    auto console_logging_t::error(const char16_t* Message) -> console_logging_t* {
        auto m = ConOut_->Mode->Attribute;
        ConOut_->SetAttribute(ConOut_, 0x04);
        ConOut_->OutputString(ConOut_, u"  [ERROR]   ");
        ConOut_->OutputString(ConOut_, Message);
        ConOut_->OutputString(ConOut_, u"\r\n");
        ConOut_->SetAttribute(ConOut_, m);
        return this;
    }

    auto console_logging_t::warn(const char16_t* Message) -> console_logging_t* {
        auto m = ConOut_->Mode->Attribute;
        ConOut_->SetAttribute(ConOut_, 0x0E);
        ConOut_->OutputString(ConOut_, u"  [WARN]    ");
        ConOut_->OutputString(ConOut_, Message);
        ConOut_->OutputString(ConOut_, u"\r\n");
        ConOut_->SetAttribute(ConOut_, m);
        return this;
    }

    auto console_logging_t::info(const char16_t* Message) -> console_logging_t* {
        auto m = ConOut_->Mode->Attribute;
        ConOut_->SetAttribute(ConOut_, 0x07);
        ConOut_->OutputString(ConOut_, u"  [INFO]    ");
        ConOut_->OutputString(ConOut_, Message);
        ConOut_->OutputString(ConOut_, u"\r\n");
        ConOut_->SetAttribute(ConOut_, m);
        return this;
    }

    auto console_logging_t::debug(const char16_t* Message) -> console_logging_t* {
        auto m = ConOut_->Mode->Attribute;
        ConOut_->SetAttribute(ConOut_, 0x08);
        ConOut_->OutputString(ConOut_, u"  [DEBUG]   ");
        ConOut_->OutputString(ConOut_, Message);
        ConOut_->OutputString(ConOut_, u"\r\n");
        ConOut_->SetAttribute(ConOut_, m);
        return this;
    }

    auto console_logging_t::operator new (size_t size, efi_system_table_t* SystemTable) -> void* {
        void* buf;
        SystemTable->BootServices->AllocatePool(memory_type_t::EfiLoaderData, size, &buf);
        return buf;
    }

    auto console_logging_t::operator delete (void* ptr, efi_system_table_t* SystemTable) -> void {
        SystemTable->BootServices->FreePool(ptr);
    }



}
