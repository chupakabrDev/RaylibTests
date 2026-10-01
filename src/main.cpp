#include "raylib-cpp.hpp"
#include "Game.hpp"
#include "InputMap.hpp"

void renderMainMenu(InputMap inputMap) {
    // background
    // start btn
    // options btn

    std::string text = "Congrats! You created your first window!";
    int fontSize = 20;

    int textWidth = MeasureText(text.c_str(), fontSize);
    int x = (GetScreenWidth() - textWidth) / 2;
    int y = (GetScreenHeight() - fontSize) / 2;

    DrawText(text.c_str(), x, y, fontSize, LIGHTGRAY);
}

void renderGame(InputMap inputMap) {
}

int main() {
    int screenWidth = 800;
    int screenHeight = 450;
    ScreenPhase screenPhase = ScreenPhase::MAIN_MENU;
    InputMap inputMap {
        {Action::TOGGLE_FULLSCREEN, {KEY_F11, false}}
        };

    raylib::Window window(screenWidth, screenHeight, "RaylibTests",
        FLAG_WINDOW_RESIZABLE
        );

    SetTargetFPS(60);

    while (!window.ShouldClose())
    {
        BeginDrawing();

        window.ClearBackground(raylib::Color::RayWhite());

        // general keys
        if (inputMap.IsActionPressed(Action::TOGGLE_FULLSCREEN)) {
            ToggleBorderlessWindowed();
        }

        if (screenPhase == ScreenPhase::MAIN_MENU) {
            renderMainMenu(inputMap);
        } else if (screenPhase == ScreenPhase::GAME) {
            renderGame(inputMap);
        }

        EndDrawing();
    }

    return 0;
}
