#pragma once

#include "Skill.h"

class Teleport : public Skill
{
private:
	static const float COOLDOWN;
	static const int RANGE = 50;
public:
	Teleport();
	~Teleport();

	virtual void activate(FLOAT3 _position, unsigned int _senderId);
	void updateSpecificSkill(float _dt);
};