#pragma once

#include <string_view>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

namespace text {
    namespace window {
        inline constexpr std::string_view TITLE = "title";
    }
    namespace test {

    }
}

class Localization {
    nlohmann::json data;
public:
    bool load(const std::string& lang);

    std::string get(std::string &k) const;
};

