#include <iostream>
#include "raylib.h"
#include "KinematicBody.h"
#include "Player.h"
#include "Meteor.h"
#include <time.h>
#include <random>
#include <string>
#include <list>
#include "Rocket.h"



int main(void)
{

    // Window Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Meteors");
    SetTargetFPS(60); 
    srand(time(NULL));
    const Vector2 center = Vector2{ screenWidth / 2, screenHeight / 2 };
    //--------------------------------------------------------------------------------------
    // Initialization
    Texture2D meteor = LoadTexture("assets/meteor01.png"); // Load texture from file into GPU memory (VRAM)
    Texture2D spaceship = LoadTexture("assets/spaceship.png"); // Load texture from file into GPU memory (VRAM)
    Texture2D stars = LoadTexture("assets/stars.png"); // Load texture from file into GPU memory (VRAM)
    Rocket::tex = LoadTexture("assets/rocket.png");
    
    Player player = Player("player", spaceship, 50, Vector2{ 200, 200 });

    //KinematicBody::registerPhysicsBody(&k1);
    KinematicBody::registerPhysicsBody(&player);


    float size = 410;
    int count = 6;
    std::list<Meteor >  meteors;
    for (int a = 0; a < count; a++) {
        float alfa = (a/(float)count)*2.0*PI;
        meteors.push_back(Meteor("meteor" + std::to_string(a), meteor, 50, Vector2{cos(alfa)*size, sin(alfa)*size}+center));
        
    }
    for (auto& m : meteors) {
        KinematicBody::registerPhysicsBody(&(m));
    }
    for (int a = 1; a <= 3; a++) {
        KinematicBody::deletePhysicsBody(a);
    }




    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        
        if (player.flag_for_deletion == false) {
            KinematicBody::updateAll(GetFrameTime(), screenWidth, screenHeight);

            KinematicBody::resolveCollisions();
            KinematicBody::deleteFlagedPhysicsBodies();
        }

        
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTextureV(stars, Vector2Zero(), WHITE);
        
        KinematicBody::drawAll(screenWidth, screenHeight);
        if (player.flag_for_deletion == true) {
            DrawText("GAME OVER!", 120, 100, 160, RED);
        }
       

        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

