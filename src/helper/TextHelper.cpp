#include "../../include/helper/TextHelper.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using nlohmann::json;
namespace fs = std::filesystem;

bool Localization::load(const std::string& lang) {
    fs::path path = fs::path(ASSETS_PATH) / "text" / (lang + ".json");
    std::ifstream stream(path);

    if (!stream) {
        std::cerr << "Couldn't open the lang file for " + lang << std::endl;
        return false;
    }

    try {
        data = json::parse(stream);
    } catch (const std::exception& e) {
        std::cerr << "error on parsing lang file for " + lang << "\n"
            << e.what() << std::endl;
        return false;
    }

    return true;
}

std::string Localization::get(std::string_view key) const {
    const std::string k(key);
    return data.contains(k) ? data.at(k).get<std::string>() : k;
}

