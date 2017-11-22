#pragma once

#include "cli.hpp"

namespace config {
    ///Configuration to launch game
    struct Config {
        ///Path to launch players.
        struct {
            std::string_view first;
            std::string_view second;
        } ai;
        ///Word information.
        struct {
            ///Word to start game with.
            std::string_view first;
            ///Words to use in game.
            std::vector<std::string_view> available;
        } word;

        Config() noexcept = default;
        explicit Config(cli::Args&& args) noexcept;
    };

    using ParseResult = std::variant<Config, std::string>;

    /**
     * Creates configuration.
     *
     * @param[in] args Parsed CLI arguments @ref Args.
     *
     * @returns @ref Config on success.
     *          Error description as string otherwise.
     */
    ParseResult create(cli::Args&& args) noexcept;
}
