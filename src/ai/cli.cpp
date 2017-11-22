#include "cli.hpp"

using namespace cli;

constexpr const char* HELP = R"STR(USAGE:
    ai <first word> [word ...]

ARGS:
    first word - First word in the game;
    word - Available words for game.
)STR";

ParseResult cli::parse(int argc, char *argv[]) noexcept {
    Args result;
    std::vector<std::string_view> args(argv + 1, argv + argc);

    if (args.empty()) {
        return std::string(HELP);
    }

    result.word.first = args[0];
    result.word.available.insert(result.word.available.end(), args.cbegin() + 1, args.cend());

    return result;
}
