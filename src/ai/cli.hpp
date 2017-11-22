#pragma once

#include <string_view>
#include <string>
#include <vector>
#include <variant>

namespace cli {
    ///CLI Arguments.
    struct Args {
        ///Word information.
        struct {
            ///Word to start game with.
            std::string_view first;
            ///Words to use in game.
            std::vector<std::string_view> available;
        } word;
    };

    using ParseResult = std::variant<Args, std::string>;

    /**
     * Parses CLI arguments.
     *
     * @param[in] argc Number of arguments passed to main.
     * @param[in] argv Argument array passed to main.
     *
     * @returns @ref Args struct on success.
     *          Error description as string otherwise.
     */
    ParseResult parse(int argc, char *argv[]) noexcept;
}
