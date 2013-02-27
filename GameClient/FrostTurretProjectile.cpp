#include "FrostTurretProjectile.h"
#include "EntityHandler.h"
#include "DelayedDamage.h"
#include "Graphics.h"
#include "MyAlgorithms.h"

const float FrostTurretProjectile::SLOW_EFFECT = -1.5f;

FrostTurretProjectile::FrostTurretProjectile(unsigned int _master, unsigned int _target)
{
	m_master = _master;
	m_target = _target;
	m_visible = false;
	this->m_type = OtherType;
	ServerEntity* master = EntityHandler::getServerEntity(m_master);
	ServerEntity* target = EntityHandler::getServerEntity(m_target);
	float timeToImpact = (target->getPosition() - master->getPosition()).length()/FrostTurretProjectile::VELOCITY;
	EntityHandler::addEntity(new DelayedDamage(m_master, m_target, timeToImpact, random(1,5), 0.0f, Skill::FROST_TURRET_PROJECTILE));
}

FrostTurretProjectile::~FrostTurretProjectile()
{

}

void FrostTurretProjectile::update(float _dt)
{
	m_timeToImpact = max(m_timeToImpact-_dt, 0.0f);

	if(m_timeToImpact == 0.0f)
	{
		ServerEntity* target = EntityHandler::getServerEntity(m_target);
		if(target)
		{
			this->dealDamage(target, random(1, 5), 0);
			((UnitEntity*)target)->applyFrostTurretSlowEffect(SLOW_EFFECT);
		}
	}
}