#pragma once

#include "Skill.h"

class HealingTouch : public Skill
{
private:
	static const float COOLDOWN;
	static const int RANGE = 10;
public:
	static const int COST = 1700;

	HealingTouch();
	~HealingTouch();

	virtual bool activate(unsigned int _senderId, unsigned int _targetId);
	void updateSpecificSkill(float _dt);
};