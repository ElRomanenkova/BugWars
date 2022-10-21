#pragma once
#include "GameBase/BugBase.h"

struct Bug : public BugBase
{
	DEFINE_RTTI;

	virtual void OnUpdate(float dt) override;
	virtual BugBase* FindBugToEat() const override;
	virtual void OnEat(BugBase& bug, BugBase& target) override;
};