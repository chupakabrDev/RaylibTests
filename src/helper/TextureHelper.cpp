#include "helper/TextureHelper.hpp"

#include <iostream>
#include <ranges>

std::weak_ptr<raylib::Texture2D> TextureManager::get(std::string_view path) {
    std::string key(path);

    auto it = cache.find(key);
    if (it != cache.end())
        return it->second;

    auto tex = std::make_shared<raylib::Texture2D>(std::string(ASSETS_PATH) + key); // raylib::RaylibException}

    auto [inserted, _] = cache.emplace(std::move(key), std::move(tex));
    return inserted->second;
}

void TextureManager::unload(std::string_view path) {
    cache.erase(std::string(path));
}

void TextureManager::clear() {
    cache.clear();
}

