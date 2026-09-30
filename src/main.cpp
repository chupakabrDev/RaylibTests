#include "raylib-cpp.hpp"

#define MAX_BUILDINGS   100

int main()
{
    const int screenWidth  = 800;
    const int screenHeight = 450;

    raylib::Window window(screenWidth, screenHeight,
                          "raylib-cpp [core] example - 2d camera");

    raylib::Rectangle player(400, 280, 40, 40);

    raylib::Rectangle buildings[MAX_BUILDINGS];
    raylib::Color     buildColors[MAX_BUILDINGS];

    int spacing = 0;

    for (int i = 0; i < MAX_BUILDINGS; i++)
    {
        buildings[i].width  = (float)GetRandomValue(50, 200);
        buildings[i].height = (float)GetRandomValue(100, 800);
        buildings[i].y      = screenHeight - 130.0f - buildings[i].height;
        buildings[i].x      = -6000.0f + spacing;

        spacing += (int)buildings[i].width;

        buildColors[i] = raylib::Color(
            (unsigned char)GetRandomValue(200, 240),
            (unsigned char)GetRandomValue(200, 240),
            (unsigned char)GetRandomValue(200, 250),
            255);
    }

    // Камера
    raylib::Camera2D camera;
    camera.target   = { player.x + 20.0f, player.y + 20.0f };
    camera.offset   = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom     = 1.0f;

    SetTargetFPS(60);

    while (!window.ShouldClose())
    {
        // Update ------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT))      player.x += 2;
        else if (IsKeyDown(KEY_LEFT))  player.x -= 2;

        camera.target = { player.x + 20, player.y + 20 };

        if (IsKeyDown(KEY_A))      camera.rotation--;
        else if (IsKeyDown(KEY_S)) camera.rotation++;

        if (camera.rotation > 40)       camera.rotation = 40;
        else if (camera.rotation < -40) camera.rotation = -40;

        // Логарифмический зум — стабильная скорость при любом масштабе
        camera.zoom = expf(logf(camera.zoom) +
                           ((float)GetMouseWheelMove() * 0.1f));

        if (camera.zoom > 3.0f)      camera.zoom = 3.0f;
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

        if (IsKeyPressed(KEY_R))
        {
            camera.zoom     = 1.0f;
            camera.rotation = 0.0f;
        }

        // Draw --------------------------------------------------------------
        BeginDrawing();
        window.ClearBackground(raylib::Color::RayWhite());

        camera.BeginMode();
            raylib::Rectangle(-6000, 320, 13000, 8000)
                .Draw(raylib::Color::DarkGray());

            for (int i = 0; i < MAX_BUILDINGS; i++)
                buildings[i].Draw(buildColors[i]);

            player.Draw(raylib::Color::Red());

            DrawLine((int)camera.target.x, -screenHeight * 10,
                     (int)camera.target.x,  screenHeight * 10, GREEN);
            DrawLine(-screenWidth * 10, (int)camera.target.y,
                      screenWidth * 10, (int)camera.target.y, GREEN);
        camera.EndMode();

        DrawText("SCREEN AREA", 640, 10, 20, RED);

        DrawRectangle(0, 0, screenWidth, 5, RED);
        DrawRectangle(0, 5, 5, screenHeight - 10, RED);
        DrawRectangle(screenWidth - 5, 5, 5, screenHeight - 10, RED);
        DrawRectangle(0, screenHeight - 5, screenWidth, 5, RED);

        DrawRectangle(10, 10, 250, 113, raylib::Color::SkyBlue().Fade(0.5f));
        DrawRectangleLines(10, 10, 250, 113, BLUE);

        DrawText("Free 2D camera controls:", 20, 20, 10, BLACK);
        DrawText("- Right/Left to move player",       40,  40, 10, DARKGRAY);
        DrawText("- Mouse Wheel to Zoom in-out",      40,  60, 10, DARKGRAY);
        DrawText("- A / S to Rotate",                 40,  80, 10, DARKGRAY);
        DrawText("- R to reset Zoom and Rotation",    40, 100, 10, DARKGRAY);

        EndDrawing();
    }

    // CloseWindow() вызывается автоматически деструктором raylib::Window
    return 0;
}