#include <cstdlib>
#include "raylib.h"
#include "config.h"
#include "Sprite.h"
#include <memory>

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

    Vector2 playerPosition = { Game::ScreenWidth / 2, Game::ScreenHeight / 2 };

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Your own initialization code here
    // ...
    // ...
    Texture2D Map = LoadTexture("assets/graphics/testmap.png");
    Texture2D myTexture = LoadTexture("assets/graphics/Charakter_Vorschlag_vorne_laufen1.png");

    Game::Sprite spr(playerPosition.x, playerPosition.y, myTexture);
    Game::Sprite spr2(100, 100, "assets/graphics/Charakter_Vorschlag_vorne_laufen1.png");

    //Kamera Einstellung
    Camera2D camera = { 0 };
    camera.target = Vector2{ spr.pos_x + 20.0f, spr.pos_y + 20.0f };
    camera.offset = Vector2{ Game::ScreenWidth / 2.0f, Game::ScreenHeight / 2.0f };
    camera.zoom = 2.0f;


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        // Updates that are made by frame are coded here
        // ...
        // ...
        //Steuerung
        if (IsKeyDown(KEY_D)) spr.pos_x += 2.0f;
        if (IsKeyDown(KEY_A)) spr.pos_x -= 2.0f;
        if (IsKeyDown(KEY_W)) spr.pos_y -= 2.0f;
        if (IsKeyDown(KEY_S)) spr.pos_y += 2.0f;

        camera.target = Vector2{ spr.pos_x + 20.0f, spr.pos_y + 20.0f };

        BeginDrawing();

        // You can draw on the screen between BeginDrawing() and EndDrawing()
        // ...
        // ...
        ClearBackground(WHITE);

        BeginMode2D(camera);
        DrawTexture(Map, 0, 0, WHITE);
        DrawTexture(spr.texture_, spr.pos_x, spr.pos_y, WHITE);
        DrawTexture(spr2.texture_, spr2.pos_x, spr2.pos_y, WHITE);
        EndMode2D();

        DrawText("KILL GOD!!!!!!!", 10, 10, 30, LIGHTGRAY);


        EndDrawing();
    } // Main game loop end

    // De-initialization here
    // ...
    // ...
    UnloadTexture(myTexture);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
