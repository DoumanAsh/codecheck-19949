#include "cli.hpp"

using namespace cli;

constexpr const char* HELP = R"STR(USAGE:
    fw <launch1> <launch2> <first word> [word ...]

ARGS:
    launch1 - First AI program to run;
    launch2 - Second AI program to run;
    first word - First word in the game;
    word - Available words for game.
)STR";

ParseResult cli::parse(int argc, char *argv[]) noexcept {
    Args result;
    std::vector<std::string_view> args(argv + 1, argv + argc);

    if (args.size() < 3) {
        return std::string(HELP);
    }

    result.ai.first = args[0];
    result.ai.second = args[1];
    result.word.first = args[2];
    result.word.available.insert(result.word.available.end(), args.cbegin() + 3, args.cend());

    return result;
}
