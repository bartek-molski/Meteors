#pragma once
#include "raylib.h"
#include "raymathext.h"
#include <list>
class KinematicBody
{ 
public:
	Vector2 position;
	float radius;
	float rotation;
	float scale;
	Texture2D sprite;
	std::string name;
	bool flag_for_deletion;

	KinematicBody(){}
	KinematicBody(std::string name, Texture2D sprite, float radius, Vector2 position, float rotation = 0, float scale = 1);
	void draw_debug();
	virtual void update(float delta, int screenWidth, int screenHeight) {};
	virtual void draw(int screenWidth, int screenHeight);
	void move(Vector2 pos);
	bool is_colliding(KinematicBody* body);


	static std::list<KinematicBody*> physicsBodies;
	static void resolveCollisions();
	static void registerPhysicsBody(KinematicBody* body);
	static void deletePhysicsBody(KinematicBody* body);
	static void updateAll(float delta, int screenWidth, int screenHeight);
	static void drawAll( int screenWidth, int screenHeight);
	static void deleteFlagedPhysicsBodies();
};





