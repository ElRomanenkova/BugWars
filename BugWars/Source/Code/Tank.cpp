#include "pch.h"
#include "Tank.h"
#include "Globals.h"
#include "Game.h"
#include "Bullet.h"
#include "Bug.h"

IMPLEMENT_RTTI(Tank);

void Tank::OnUpdate(float dt)
{
}

BugBase* Tank::GetBugToShoot() const
{
	BugBase* target = nullptr;
	float min_dist = std::numeric_limits<float>::max();

	for (auto obj : g_Game->objects)
	{
		if (obj->GetRTTI() == Bug::s_RTTI)
		{
			if (!obj->visible)
				continue;

			float dist = position.Distance2(obj->position);
			if (dist < min_dist)
			{
				min_dist = dist;
				target = static_cast<BugBase*>(obj);
			}
		}
	}

	return target;
}

Point Tank::CalcShootDirection(Point target_pos, Point target_dir, float target_vel, float bullet_vel) const
{
	//idea was taken from stackoverflow.com 
	auto vel = target_dir * target_vel;
	auto a = vel.Length2() - bullet_vel * bullet_vel;

	auto dist = target_pos - position;
	auto b = 2 * (vel.x * dist.x + vel.y * dist.y);
	auto c = dist.Length2();

	auto disc = b * b - 4 * a * c;
	if (disc == 0) 
		return dist;

	auto t1 = (-b + sqrt(disc)) / (2 * a);
	auto t2 = (-b - sqrt(disc)) / (2 * a);
	auto t = std::max(t1, t2);

	return vel * t + dist;
}
