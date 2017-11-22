#include "word.hpp"

#include <iostream>

std::optional<std::string_view> word::choose(std::string_view current, const std::vector<std::string_view>& available) noexcept {
    for (const auto& word : available) {
        if (current.back() == word.front()) {
            return word;
        }
    }

    return std::nullopt;
}

