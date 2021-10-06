#include "KinematicBody.h"

// static Definition
std::vector<KinematicBody*> KinematicBody::physicsBodies;


KinematicBody::KinematicBody(std::string name, Texture2D sprite, float radius, Vector2 position, float rotation, float scale)
{
	this->sprite = sprite;
	this->position = position;
	this->radius = radius;
	this->rotation = rotation;
	this->scale = scale;
	this->name = name;
	this->flag_for_deletion = false;
}

void KinematicBody::draw_debug()
{
	DrawCircleV(this->position, this->radius, RED);

}



void KinematicBody::draw(int screenWidth, int screenHeight)
{
	//DrawTextureEx(this->sprite, this->position - Vector2{(float)(this->sprite.width/2.0),(float)(this->sprite.height/2.0)}, this->rotation, this->scale, WHITE);
	DrawTexturePro(this->sprite,
		Rectangle {0, 0, (float)this->sprite.width, (float)this->sprite.height},
		Rectangle{ (float)this->position.x, (float)this->position.y, (float)(this->sprite.width), (float)(this->sprite.height) },
		Vector2{ (float)(this->sprite.width / 2), (float)(this->sprite.height / 2) }, this->rotation, WHITE);
}

void KinematicBody::move(Vector2 pos)
{
	this->position = pos + this->position;

}

bool KinematicBody::is_colliding(KinematicBody* body)
{
	float dist = Vector2Distance(this->position, body->position);
	if (dist < this->radius + body->radius) {
		return true;
	}
	
	return false;
}

/*bool kinematicBodyColision(KinematicBody k1, KinematicBody k2) {
	float dist = Vector2Distance(k1.position, k2.position);
	if (dist < k1.radius + k2.radius) {
		return true;
	}
	return false;
}*/

void KinematicBody::resolveCollisions()
{
	for (auto& body : KinematicBody::physicsBodies)
	{
		for (auto& body2 : KinematicBody::physicsBodies)
		{
			
			if (body != body2  &&  body->is_colliding(body2)) {
				body->flag_for_deletion = true;
				std::cout << body->name << " is_colliding with "<< body2->name;
			}
		}
	}
	std::cout << "--- collision resolved\n";
}

void KinematicBody::registerPhysicsBody(KinematicBody* body)
{
	KinematicBody::physicsBodies.push_back(body);
}

void KinematicBody::deletePhysicsBody(int id)
{
	KinematicBody::physicsBodies.erase(KinematicBody::physicsBodies.begin()+id);
}

void KinematicBody::updateAll(float delta, int screenWidth, int screenHeight)
{
	for (auto& body : KinematicBody::physicsBodies)
	{
		body->update(delta, screenWidth, screenHeight);
	}
}

void KinematicBody::drawAll(int screenWidth, int screenHeight)
{
	for (auto& body : KinematicBody::physicsBodies) {
		body->draw( screenWidth, screenHeight);
	}
}

void KinematicBody::deleteFlagedPhysicsBodies()
{
	int id = 0;
	for (auto& body : KinematicBody::physicsBodies) {

		if (body->flag_for_deletion) {
			KinematicBody::deletePhysicsBody(id);
		}
		id++;
	}
}
