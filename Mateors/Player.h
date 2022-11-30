#pragma once
#include "KinematicBody.h"
#include "raylib.h"
#include "Rocket.h"
#include "list"
class Player :
    public KinematicBody
{
public:
    float shoot_timer;
    Vector2 velocity;
    Vector2 direction;
    std::list<Rocket> rockets;
    Player(std::string name, Texture2D sprite, float radius, Vector2 position, float rotation = 0, float scale = 1);
    void update(float delta, int screenWidth, int screenHeight);
    void draw(int screenWidth, int screenHeight);
    void shoot();
    
};


