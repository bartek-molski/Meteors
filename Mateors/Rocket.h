#pragma once
#include "KinematicBody.h"
class Rocket :
    public KinematicBody
{
public:
    float current_rotation;
    float speed;
    float time;
    Vector2 velocity;
    Vector2 direction;
    Rocket(std::string name, float radius, Vector2 position, float rotation = 0, float scale = 1);

    //Rocket(std::string name, Texture2D sprite, float radius, Vector2 position, float rotation = 0, float scale = 1);
    Rocket() {}
    void update(float delta, int screenWidth, int screenHeight);
    static Texture2D tex;
    
};

