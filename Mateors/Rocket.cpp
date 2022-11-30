#include "Rocket.h"


// static Definition
Texture2D Rocket::tex;

Rocket::Rocket(std::string name, float radius, Vector2 position, float rotation, float scale)
{
	this->sprite = Rocket::tex;
	this->position = position;
	this->radius = radius;
	this->rotation = rotation;
	this->scale = scale;
	this->velocity = Vector2Zero();
	this->direction = Vector2{0, -1};
	this->speed = 350;
	this->current_rotation = 0;
	this->name = name;
	this->flag_for_deletion = false;
	this->time = 1.5;
}

/*Rocket::Rocket(std::string name, Texture2D sprite, float radius, Vector2 position, float rotation, float scale)
{
	this->sprite = sprite;
	this->position = position;
	this->radius = radius;
	this->rotation = rotation;
	this->scale = scale;
	this->velocity = Vector2Zero();
	this->direction = Vector2Zero();
	this->speed = 0;
	this->current_rotation = 0;
	this->name = name;
	this->flag_for_deletion = false;

}*/

void Rocket::update(float delta, int screenWidth, int screenHeight)
{

	this->velocity = this->direction * speed;
	this->move(this->velocity * delta);
	this->rotation = atan2(this->direction.y, this->direction.x) * (180.0 / PI) + 90;
	this->time = this->time - delta;
	
}
