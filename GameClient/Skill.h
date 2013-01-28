#pragma once

#include "ServerEntity.h"

class Skill
{
private:
	int m_id;
	float m_cooldown;
public:
	static enum SKILLS {MOVE, ATTACK, CHAIN_STRIKE, CLOUD_OF_DARKNESS, STUNNING_STRIKE};

	Skill();
	Skill(int _id, float _cooldown);
	virtual ~Skill();
	
	virtual void activate(unsigned int _senderId);
	virtual void activate(unsigned int _targetId, unsigned int _senderId);
	virtual void activate(FLOAT3 position, unsigned int _senderId);
	float getCooldown()const { return m_cooldown; }
	int getId()const { return m_id; }
	void setCooldown(int _cooldown) { m_cooldown = _cooldown; }
	void update(float _dt);
	virtual void updateSpecificSkill(float _dt) = 0;
};