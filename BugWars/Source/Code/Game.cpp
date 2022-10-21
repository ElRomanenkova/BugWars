#include "pch.h"
#include "Game.h"
#include "GameBase/Log.h"
#include "Tank.h"
#include "Bug.h"
#include "Bullet.h"
#include "GameBase/Framework.h"

Game* g_Game;

Game::Game()
	: GameBase({ [] {auto tank = new Tank; 
						tank->angle = 0; tank->visible = true; tank->disabled = false; 
						return tank; },
				 [] {auto bug = new Bug; 
						bug->angle = 0; bug->visible = false; bug->disabled = false; 
						return bug; },
				 [] {auto bullet = new Bullet; 
						bullet->angle = 0; bullet->visible = false; bullet->disabled = false; 
						return bullet; } })
{
	g_Game = this;
}

Game::~Game()
{
	g_Game = nullptr;
	for (int i = 0; i < this->objects.size(); i++)
		delete objects[i];
	objects.clear();
}

void Game::OnUpdate(float dt)
{
	PIXScopedEvent(PIX_COLOR_INDEX(5), __FUNCTION__);

	for (int i = objects.size() - 1; i >= 0; i--)
	{
		auto obj = objects[i];

		obj->visible = IsOnScreen(tank->position, obj->position);

		if (!obj->disabled)
		{
			obj->Update(dt);
		}
		else
		{
			delete obj;
			objects.erase(objects.begin() + i);
		}
	}
}

bool Game::IsOnScreen(const Point& center, const Point& object)
{
	auto dist = center - object;

	return fabs(dist.y) < framework->screenSize.y / 2 && fabs(dist.x) < framework->screenSize.x / 2;
}

void Game::OnRender() const
{
	for (auto& obj : objects)
		if (obj->visible)
			DoRender(obj);
}

void Game::AddObject(GameObject* object)
{		
	if (object->GetRTTI() == Bug::s_RTTI)
	{
		object->visible = false;
		object->disabled = false;
	}
	objects.push_back(object);

	//if (object->GetRTTI() == Bug::s_RTTI)
		//Log("I'm a bug");
}

void Game::OnBugsSpawned()
{
}
