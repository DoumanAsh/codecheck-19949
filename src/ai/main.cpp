#include <iostream>

#include "cli.hpp"
#include "word.hpp"

inline static cli::Args initialize(int argc, char *argv[]) {
    auto parse_result = cli::parse(argc, argv);
    if (auto error = std::get_if<std::string>(&parse_result)) {
        std::cout << *error << "\n";
        exit(1);
    }
    return std::get<cli::Args>(parse_result);
}

int main(int argc, char *argv[]) {
    const auto args = initialize(argc, argv);
    const auto word = word::choose(args.word.first, args.word.available);

    if (word) {
        std::cout << *word;
    }

    return 0;
}
