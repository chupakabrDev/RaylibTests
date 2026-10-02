#include "TextHelper.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using nlohmann::json;

bool Localization::load(const std::string& lang) {
    std::ifstream stream("assets/text" + lang + ".json");

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

std::string Localization::get(std::string &key) const {
    return data.contains(key) ? data.at(key).get<std::string>() : key;
}

