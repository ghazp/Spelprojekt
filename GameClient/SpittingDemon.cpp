#include "SpittingDemon.h"
#include "PoisonStrike.h"

SpittingDemon::SpittingDemon(FLOAT3 _pos, Path _path) : Enemy(_pos, _path)
{
	m_modelId        = 83;
	
	m_strength       = 0;
	m_agility        = 7;
	m_wits           = 4;
	m_fortitude      = 1;

	m_lowResource    = 40;
	m_highRescource  = 50;
	

	m_health = 100*m_fortitude; 
	m_physicalDamage = m_strength*5;
	m_mentalDamage = m_wits*5;
	m_baseMovementSpeed = 2.0 + m_agility*0.1f;
	m_movementSpeed = m_baseMovementSpeed;
	m_baseAttackSpeed = 2.0 - m_agility* 0.05f;
	m_attackSpeed = m_baseAttackSpeed;

	m_basePhysicalResistance = m_strength*2;
	m_physicalResistance = m_basePhysicalResistance ; 

	m_baseMentalResistance = m_fortitude*2;
	m_mentalResistance = m_baseMentalResistance;

	m_skills.push_back(new PoisonStrike());

}

void SpittingDemon::attackHero(int heroIndex)
{
	this->dealDamage(EntityHandler::getAllHeroes()[heroIndex], this->getPhysicalDamage(), this->getMentalDamage());
	this->m_attackCooldown = m_attackSpeed;

	//Use Poison Strike, please!
}


SpittingDemon::~SpittingDemon(void)
{
}
