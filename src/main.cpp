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


    Vector2 playerPosition = { Game::ScreenWidth / 2, Game::ScreenHeight / 2 };

#ifdef GAME_START_FULLSCREEN //ToggleFullscreen(); not working @todo when press K it changes from fullscreen to windowed mode
    /*ToggleFullscreen();
    if (IsKeyPressed(KEY_K)) {
        ToggleFullscreen();
    }*/
    

#endif 

#ifdef HIDE_CURSOR   
    RLAPI void HideCursor(void);  //HideCursor; not working @todo 
#endif


    // *** Your own initialization code here ***

    Texture2D Map = LoadTexture("assets/graphics/wintermap.png");

    Texture2D NemoFr = LoadTexture("assets/graphics/NemoFrontwalk-Sheet.png");
    Texture2D NemoBk = LoadTexture("assets/graphics/NemoHintenWalk-Sheet.png");
    Texture2D NemoR = LoadTexture("assets/graphics/NemoRechtsWalk-Sheet.png");
    Texture2D NemoL = LoadTexture("assets/graphics/NemoLinksWalk-Sheet.png");

    Texture2D StandStil = LoadTexture("assets/graphics/Charakter_Vorschlag_vorne_laufen1.png");
    Game::Sprite spr(playerPosition.x, playerPosition.y, NemoFr);

    //Camera settings 
    Camera2D camera = { 0 };
    camera.target = Vector2{ spr.pos_x + 20.0f, spr.pos_y + 20.0f };
    camera.offset = Vector2{ Game::ScreenWidth / 2.0f, Game::ScreenHeight / 2.0f };
    camera.zoom = 2.0f;

    //devide spritesheet into frames 
    Vector2 position = { Game::ScreenWidth / 2, Game::ScreenHeight / 2 };
    Rectangle frameRec = { 0.0f, 0.0f, (float)NemoFr.width / 3, (float)NemoFr.height }; // NemoFr -> nemo in the future
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;            // animtation fps 


    // *** Main game loop ***

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        if (IsKeyDown(KEY_D)) {                     //run right
            spr.pos_x += 1.0f;

            framesCounter++;

            if (framesCounter >= (60 / framesSpeed))
            {
                framesCounter = 0;
                currentFrame++;

                if (currentFrame > 2) currentFrame = 0;

                frameRec.x = (float)currentFrame * (float)NemoR.width / 3;
            }
        }

        if (IsKeyDown(KEY_A)) {                     //run left
            spr.pos_x -= 1.0f;

            framesCounter++;

            if (framesCounter >= (60 / framesSpeed))
            {
                framesCounter = 0;
                currentFrame++;

                if (currentFrame > 2) currentFrame = 0;

                frameRec.x = (float)currentFrame * (float)NemoL.width / 3;
            }
        }

        if (IsKeyDown(KEY_W)) {                     //run forwards
            spr.pos_y -= 1.0f;

            framesCounter++;

            if (framesCounter >= (60 / framesSpeed))
            {
                framesCounter = 0;
                currentFrame++;

                if (currentFrame > 2) currentFrame = 0;

                frameRec.x = (float)currentFrame * (float)NemoFr.width / 3;
            }
        }

        if (IsKeyDown(KEY_S)) {                     //run backwards
            spr.pos_y += 1.0f;

            framesCounter++;

            if (framesCounter >= (60 / framesSpeed))
            {
                framesCounter = 0;
                currentFrame++;

                if (currentFrame > 2) currentFrame = 0;

                frameRec.x = (float)currentFrame * (float)NemoBk.width / 3;
            }
        }

        camera.target = Vector2{ spr.pos_x + 20.0f, spr.pos_y + 20.0f };


        BeginDrawing();

        ClearBackground(WHITE);

        BeginMode2D(camera);
        DrawTexture(Map, 0, 0, WHITE);
        EndMode2D();

        //@todo when WASD not pressed display nemo standing, when WASD pressed delete nemo standing and draw animation

        //if ((!IsKeyDown(KEY_W)) || (!IsKeyDown(KEY_S)) || (!IsKeyDown(KEY_D)) || (!IsKeyDown(KEY_A))) { 

        

        
            if (IsKeyDown(KEY_W));          
            {                
                DrawTextureRec(NemoBk, frameRec, position, WHITE);    // Draw nemo animation backwards               
            }
            

            if (IsKeyDown(KEY_S)) {
                DrawTextureRec(NemoFr, frameRec, position, WHITE);    // Draw nemo animation forwards               
            }

            
            if (IsKeyDown(KEY_D)) {               
                DrawTextureRec(NemoR, frameRec, position, WHITE);      // Draw nemo animation right                
            }
           

            if (IsKeyDown(KEY_A)) {
                DrawTextureRec(NemoL, frameRec, position, WHITE);      // Draw nemo animation left                
            }
            


        // controlls description
        DrawText("***********************Controlls**************************", 10, 0, 10, BLACK);
        DrawText("*-> Move with W,A,S,D", 10, 10, 10, BLACK);  // x, y , size of text       
        DrawText("*-> Exit game with ESC", 10, 20, 10, BLACK);
        DrawText("*-> toggle between windowed mode and fullscreen mode press K", 10, 30, 10, BLACK);
        DrawText("*********************************************************", 10, 40, 10, BLACK);

        EndDrawing();
    } // Main game loop end



    // *** De-initialization here ***     

    UnloadTexture(NemoFr);
    UnloadTexture(NemoBk);
    UnloadTexture(NemoR);
    UnloadTexture(NemoL);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
