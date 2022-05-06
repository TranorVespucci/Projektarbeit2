#include <iostream>
#include <memory>
#include <cstdlib>

#include "raylib.h"
#include "config.h"
#include "Sprite.h"



int main() {
    // Raylib initialization
    // Project name = Custodia, 16:9, 640p : 360p res (screen size), fullscreen mode -> etc. can be specified in the config.h.in file
    

    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);    
    SetTargetFPS(60);


    Vector2 playerPosition = { Game::ScreenWidth / 2, Game::ScreenHeight / 2 };   //Starting point 

#ifdef GAME_START_FULLSCREEN 
    ToggleFullscreen();
    if (IsKeyPressed(KEY_K)) ToggleFullscreen();
    //ToggleFullscreen(); not working @todo when press K it changes from fullscreen to windowed mode
    
#endif 

#ifdef HIDE_CURSOR   
    void HideCursor(void); //HideCursor; not working @todo 
#endif

   
    // *** Your own initialization code here ***
   
    Texture2D Map = LoadTexture("assets/graphics/testmap.png");                 //Map.png
    Texture2D Nemo = LoadTexture("assets/graphics/NemoFrontwalk-Sheet.png");    //Texture2D Nemo = LoadTexture("assets/graphics/ReCharakter_Main-Sheet.png");
    Game::Sprite spr(playerPosition.x, playerPosition.y, Nemo);    

    // Camera lock, moves with player 
    Camera2D camera = { 0 };    
    camera.target = Vector2{ spr.pos_x + 20.0f, spr.pos_y + 20.0f };
    camera.offset = Vector2{ Game::ScreenWidth / 2.0f, Game::ScreenHeight / 2.0f };
    camera.zoom = 2.0f;

    /*
    *
    */

    //Vector2 position = { 350.0f, 280.0f };
    Vector2 position = { Game::ScreenWidth / 2, Game::ScreenHeight / 2 };
    Rectangle frameRec = { 0.0f, 0.0f, (float)Nemo.width / 3, (float)Nemo.height }; //(float)Nemo.width / x x=frames for it to be cut into 
    int currentFrame = 0;

    int framesCounter = 0;
    int framesSpeed = 8;            // animtation fps 


    // *** Main game loop ***

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // Updates that are made by frame are coded here
       
        if (IsKeyDown(KEY_D)) spr.pos_x += 2.0f;    //run right
        if (IsKeyDown(KEY_A)) spr.pos_x -= 2.0f;    //run left
        if (IsKeyDown(KEY_W)) spr.pos_y -= 2.0f;    //run forwards
        if (IsKeyDown(KEY_S)) spr.pos_y += 2.0f;    //run backwards       

        camera.target = Vector2{ spr.pos_x + 20.0f, spr.pos_y + 20.0f };

        //Main Character animation (raylib)
        framesCounter++;

        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 2) currentFrame = 0;

            frameRec.x = (float)currentFrame * (float)Nemo.width / 3;
        }               

        BeginDrawing();

        // You can draw on the screen between BeginDrawing() and EndDrawing()
        
        ClearBackground(WHITE);

        BeginMode2D(camera);
        DrawTexture(Map, 0, 0, WHITE);       
        EndMode2D();

        /*
        *
        *
        */

        DrawTextureRec(Nemo, frameRec, position, WHITE);  // Draw part of the texture
        
         /*
          *
          *             
          */       

        // controlls description

        DrawText("Move the Player with W,A,S,D", 10, 10, 20, LIGHTGRAY);  // x, y , size of text       
        DrawText("To exit the game press ESC", 10, 40, 20, LIGHTGRAY);  
        DrawText("To change to windowed mode/ fullscreen mode press K", 10, 70, 15, LIGHTGRAY);        

        EndDrawing();
    } // Main game loop end



    // *** De-initialization here ***     

    UnloadTexture(Nemo);

    // Close window and OpenGL context
    CloseWindow();    

    return EXIT_SUCCESS;
}
