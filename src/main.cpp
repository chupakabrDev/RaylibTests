#include "raylib-cpp.hpp"
#include "Game.hpp"
#include "InputMap.hpp"
#include "../include/helper/TextHelper.hpp"
#include "helper/TextureHelper.hpp"

void renderMainMenu(TextureManager& textureManager, InputMap inputMap) {
    // background
    // start btn
    // options btn

    // std::string text = "Congrats! You created your first window!";
    // int fontSize = 20;
    //
    // int textWidth = MeasureText(text.c_str(), fontSize);
    // int x = (GetScreenWidth() - textWidth) / 2;
    // int y = (GetScreenHeight() - fontSize) / 2;

    // DrawText(text.c_str(), x, y, fontSize, LIGHTGRAY);

    if (auto background = textureManager.get(texture::menu::main::BACKGROUND).lock()) {
        Rectangle source = { .x = 0, .y = 0, .width = static_cast<float>(background->width), .height = static_cast<float>(background->height) };
        Rectangle dest   = { .x = 0, .y = 0, .width = static_cast<float>(GetScreenWidth()), .height = static_cast<float>(GetScreenHeight()) };
        background->Draw(source, dest, {.x = 0, .y = 0}, 0.0f, WHITE);
    }
}

void renderGame(InputMap inputMap) {
}

int main() {
    int screenWidth = 800;
    int screenHeight = 450;
    Localization locale;
    locale.load("ru_ru");
    TextureManager textureManager;
    ScreenPhase screenPhase = ScreenPhase::MAIN_MENU;
    InputMap inputMap {
        {Action::TOGGLE_FULLSCREEN, {KEY_F11, false}}
        };

    raylib::Window window(screenWidth, screenHeight, locale.get(text::window::TITLE),
        FLAG_WINDOW_RESIZABLE
        );

    SetTargetFPS(60);

    while (!window.ShouldClose())
    {
        // general keys
        if (inputMap.IsActionPressed(Action::TOGGLE_FULLSCREEN)) {
            ToggleBorderlessWindowed();
        }

        while (window.Drawing()) {
            window.ClearBackground(RAYWHITE);

            if (screenPhase == ScreenPhase::MAIN_MENU) {
                renderMainMenu(textureManager, inputMap);
            } else if (screenPhase == ScreenPhase::GAME) {
                renderGame(inputMap);
            }
        }

    }

    return 0;
}
