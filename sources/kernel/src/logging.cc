#include "conurbation/logging.hh"
#include "conurbation/mem/liballoc.h"

size_t vasprintf(char16_t* buf, const char16_t* fmt, va_list args);

namespace Conurbation {

    auto logging_t::begin_group(const char16_t* title) -> logging_t &
    {
        int i = 0;
        while (i < group_lvl_) {
            stop_->OutputString(stop_, u"    ");
            ++i;
        }
        stop_->OutputString(stop_, title);
        stop_->OutputString(stop_, u"\r\n");
        ++group_lvl_;
        return *this;
    }

    auto logging_t::end_group() -> logging_t &
    {
        if (group_lvl_ > 0) {
            group_lvl_ -= 1;
            int i = 0;
            while (i < group_lvl_) {
                stop_->OutputString(stop_, u"    ");
                ++i;
            }
            stop_->OutputString(stop_, u"\r\n");
        }
        return *this;
    }

    auto logging_t::log(log_level_t level, const char16_t* source, const char16_t* message, va_list args) -> logging_t &
    {
        int i = 0;
        char16_t* buf = reinterpret_cast<char16_t*>(kcalloc(2, 128));

        while (i < group_lvl_) {
            stop_->OutputString(stop_, u"    ");
            ++i;
        }
        switch (level) {
            case log_level_t::panic:
                stop_->SetAttribute(stop_, 0x4F);
                break;
            case log_level_t::error:
                stop_->SetAttribute(stop_, 0x0C);
                break;
            case log_level_t::warn:
                stop_->SetAttribute(stop_, 0x0E);
                break;
            case log_level_t::info:
                stop_->SetAttribute(stop_, 0x0F);
                break;
            case log_level_t::trace:
                stop_->SetAttribute(stop_, 0x07);
                break;
            case log_level_t::debug:
                stop_->SetAttribute(stop_, 0x08);
        }

        stop_->OutputString(stop_, u"[");
        stop_->OutputString(stop_, source);
        stop_->OutputString(stop_, u"] ");
        vasprintf(buf, message, args);
        stop_->OutputString(stop_, buf);
        stop_->OutputString(stop_, u"\r\n");

        stop_->SetAttribute(stop_, 0x0F);

        kfree(buf);

        return *this;
    }
}
