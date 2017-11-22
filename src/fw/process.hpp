#pragma once

#include <optional>
#include <string>
#include <string_view>

namespace process {
    /**
     * Command result representation.
     */
    struct Result {
        ///Return code of spawned command.
        int code = 255;
        ///Output of spawned command.
        std::string output;
    };

    /**
     * Synchronously executes command.
     */
    Result run(const char* cmd, const char* args) noexcept;
    Result run(const char* cmd, std::string_view first, const std::vector<std::string_view>& words) noexcept;
}
