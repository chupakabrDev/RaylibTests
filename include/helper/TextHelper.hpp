#pragma once

#include <string_view>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

namespace text::window {
    inline constexpr std::string_view TITLE = "window.title";
}

class Localization {
    nlohmann::json data;
public:
    bool load(const std::string& lang);

    [[nodiscard]] std::string get(std::string_view key) const;
};

