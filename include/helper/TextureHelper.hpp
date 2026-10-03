#pragma once

#include <memory>
#include <string_view>
#include <unordered_map>

#include "raylib-cpp.hpp"

namespace texture::menu::main {
    inline constexpr std::string_view BACKGROUND = "texture/menu/main/background.png";
}


class TextureManager {
public:
    TextureManager() = default;
    ~TextureManager() = default;

    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
    TextureManager(TextureManager&&) = delete;
    TextureManager& operator=(TextureManager&&) = delete;

    std::weak_ptr<raylib::Texture2D> get(std::string_view path);

    void unload(std::string_view path);
    void clear();

private:
    std::unordered_map<std::string, std::shared_ptr<raylib::Texture2D>> cache;
};