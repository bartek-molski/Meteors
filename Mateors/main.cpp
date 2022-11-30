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


//void startGame(){}
int main(void)
{

    // Window Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const float deleteScale = 3;

    InitWindow(screenWidth, screenHeight, "Meteors");
    SetTargetFPS(60); 
    srand(time(NULL));
    const Vector2 center = Vector2{ screenWidth / 2, screenHeight / 2 };
    
    //--------------------------------------------------------------------------------------
    // Initialization
    int score = 0;
    float meteor_timer = 1;
    bool paused = true;
    Texture2D meteor = LoadTexture("assets/meteor01.png"); // Load texture from file into GPU memory (VRAM)
    Texture2D spaceship = LoadTexture("assets/spaceship.png"); // Load texture from file into GPU memory (VRAM)
    Texture2D stars = LoadTexture("assets/stars.png"); // Load texture from file into GPU memory (VRAM)
    Rocket::tex = LoadTexture("assets/rocket.png");
    
    Player player = Player("player", spaceship, 50, center);

    //KinematicBody::registerPhysicsBody(&k1);
    //KinematicBody::registerPhysicsBody(&player);


    float size = 700;
    int count = 6;
    std::list<Meteor >  meteors;
    for (int a = 0; a < count; a++) {
        float alfa = (a/(float)count)*2.0*PI;
        meteors.push_back(Meteor("meteor" + std::to_string(a), meteor, 50, Vector2{cos(alfa)*size, sin(alfa)*size}+center));
        
    }
    for (auto& m : meteors) {
        KinematicBody::registerPhysicsBody(&(m));
    }
    /*for (int a = 1; a <= 3; a++) {
        KinematicBody::deletePhysicsBody(a);
    }*/




    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here

        if (player.flag_for_deletion) {
            paused = true;
        }

        if (paused == false) {
            meteor_timer = meteor_timer - GetFrameTime();
            if (meteor_timer < 0) {
                count = 10000;
                int random_count = rand() % count;
                float random_beta = (rand() % 10000 / 10000 * 0.25 * PI) - (1.0 / 8.0 * PI);
                float alfa = (random_count / (float)count) * 2.0 * PI;
                meteors.push_back(Meteor("meteor", meteor, 50, Vector2{ cos(alfa) * size, sin(alfa) * size } + center));
                meteors.back().direction = Vector2{ -cos(alfa + random_beta), -sin(alfa + random_beta) };
                KinematicBody::registerPhysicsBody(&meteors.back());

                meteor_timer = 1;

            }
            KinematicBody::updateAll(GetFrameTime(), screenWidth, screenHeight);

            for (auto& m : meteors) {
                if (m.flag_for_deletion) {
                    score = score + 1;
                }
            }
            meteors.remove_if([](KinematicBody body) {return body.flag_for_deletion; });
            for (auto& m : meteors) {
                if (m.position.x > screenWidth * deleteScale ||
                    m.position.y > screenHeight * deleteScale ||
                    m.position.x < screenWidth * (deleteScale - 1) * -1 ||
                    m.position.y < screenHeight * (deleteScale - 1) * -1) {

                    m.flag_for_deletion = true;
                }
            }
            KinematicBody::resolveCollisions();
            KinematicBody::deleteFlagedPhysicsBodies();
        }
        else {
            if (IsKeyPressed(KEY_SPACE)) {
                

                player.flag_for_deletion = false;
                player.position = center;
                KinematicBody::registerPhysicsBody(&player);
                for (auto& m : meteors) {
                    m.flag_for_deletion = true;

                }
                KinematicBody::deleteFlagedPhysicsBodies();
                meteors.remove_if([](KinematicBody body) {return body.flag_for_deletion; });
                paused = false;
                score = 0;
            }

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
        if (paused) {
            DrawText("Aby zaczac kliknij spacje", 120, screenHeight - 100, 80, GREEN);
        }
        DrawText(std::to_string(score).c_str(), 20, 80, 60, WHITE);
       

        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

