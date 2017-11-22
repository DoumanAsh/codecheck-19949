#pragma once

#include <vector>
#include <optional>
#include <string_view>

namespace word {
    /**
     * Choose word among available that starts with last char of current.
     *
     * @param[in] current Current word in word chain game.
     * @param[in] available Array of words to choose from.
     *
     * @return Word if there is one.
     *         Otherwise returns std::nullopt
     */
    std::optional<std::string_view> choose(std::string_view current, const std::vector<std::string_view>& available) noexcept;
}
