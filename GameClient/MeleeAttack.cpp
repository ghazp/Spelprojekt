#include "MeleeAttack.h"

const float MeleeAttack::RANGE = 1.0f;

MeleeAttack::MeleeAttack()
{
	this->setRange(MeleeAttack::RANGE);
}

MeleeAttack::~MeleeAttack()
{

}

bool MeleeAttack::activate(unsigned int _targetId, unsigned int _senderId)
{
	UnitEntity* caster = (UnitEntity*)EntityHandler::getServerEntity(_senderId);

	if(caster != NULL)
	{
		EntityHandler::addEntity(new DelayedDamage(_senderId, _targetId, 0.5f, caster->getPhysicalDamage(), caster->getMentalDamage(), Skill::MELEE_ATTACK));
	}

	return true;
}

void MeleeAttack::updateSpecificSkill(float dt)
{

}