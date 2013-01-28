#pragma once

#include "skill.h"
#include "EntityHandler.h"

class DeadlyStrike : public Skill
{
private:
	unsigned int m_senderId;
public:
	DeadlyStrike();
	~DeadlyStrike();

	bool activate(unsigned int _senderId);
	void updateSpecificSkill(float dt);
};

