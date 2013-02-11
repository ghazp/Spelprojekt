#pragma once

#include "ServerEntity.h"

class Skill
{
private:
	int m_id;
	float m_cooldown;
	float m_currentCooldown;
public:
	static enum SKILLS {
		MOVE, 
		ATTACK, 
		TOWER,
		STRENGTH,
		AGILITY,
		WITS,
		FORTITUDE,
		AIM,
		DEADLY_STRIKE, 
		GREED, 
		LIFESTEALING_STRIKE, 
		MENTAL_RESISTANCE, 
		PHYSICAL_RESISTANCE, 
		POISON_STRIKE, 
		TURRET_LIFE,
		DEATH_TOWER,
		CHAIN_STRIKE, 
		STUNNING_STRIKE, 
		CLOUD_OF_DARKNESS, 
		HEALING_TOUCH,
		DEMONIC_PRESENCE,
		TELEPORT,
		WALL,
		ENIGMATIC_PRESENCE,
		SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR,
		COURAGE_HONOR_VALOR,
		READY_AIM_FIRE,
		TIME_IS_MONEY,
		ENHANCED_DEVELOPMENT,
		LIFE_REGAIN,
		SIMONS_EVIL
		};

	Skill();
	Skill(int _id, float _cooldown);
	virtual ~Skill();
	
	virtual bool activate(unsigned int _senderId);
	virtual bool activate(unsigned int _targetId, unsigned int _senderId);
	virtual bool activate(FLOAT3 position, unsigned int _senderId);
	float getCurrentCooldown()const { return m_currentCooldown; }
	int getId()const { return m_id; }
	void resetCooldown();
	void update(float _dt);
	virtual void updateSpecificSkill(float _dt) = 0;
};