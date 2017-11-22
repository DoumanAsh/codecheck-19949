#include "config.hpp"

#include <sstream>
#include <system_error>
#include <filesystem>

namespace fs = std::experimental::filesystem;

using namespace config;

Config::Config(cli::Args&& args) noexcept {
    //TODO: Consider whether should we use fs paths or not.

    //JFYI: string_view is trivial to copy, so we don't really need to move it.
    this->ai.first = args.ai.first;
    this->ai.second = args.ai.second;

    this->word.first = args.word.first;
    this->word.available = std::move(args.word.available);
}

ParseResult config::create(cli::Args&& args) noexcept {
    std::error_code fs_error;
    std::stringstream error;

    if (!fs::exists(args.ai.first.data())) {
        error << args.ai.first << ": No such file.";
        return error.str();
    }
    if (!fs::exists(args.ai.second.data())) {
        error << args.ai.second << ": No such file.";
        return error.str();
    }

    return Config(std::move(args));
}
