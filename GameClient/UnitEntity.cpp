#include "UnitEntity.h"

UnitEntity::UnitEntity() : ServerEntity()
{
	this->m_health = 100;
	this->m_maxHealth = 100;

	this->m_strength = 1;
	this->m_agility = 1;
	this->m_wits = 1;
	this->m_fortitude = 1;
	
	this->m_movementSpeed = 1.0f;
	this->m_attackSpeed = 1.0f;
	this->m_physicalDamage = 1.0f;
	this->m_mentalDamage = 1.0f;
	this->m_physicalResistance = 0.0f;
	this->m_mentalResistance = 0.0f;
	this->m_lifeStealChance = 0.0f;
	this->m_poisonChance = 0.0f;
	this->m_deadlyStrikeChance = 0.0f;
	this->m_poisonCounter = 0;
	this->m_stunned = false;
}

UnitEntity::UnitEntity(FLOAT3 pos) : ServerEntity(pos)
{
	this->m_health = 100;
	this->m_maxHealth = 100;

	this->m_strength = 1;
	this->m_agility = 1;
	this->m_wits = 1;
	this->m_fortitude = 1;

	this->m_movementSpeed = 1.0f;
	this->m_attackSpeed = 1.0f;
	this->m_physicalDamage = 1.0f;
	this->m_mentalDamage = 1.0f;
	this->m_physicalResistance = 0.0f;
	this->m_mentalResistance = 0.0f;
	this->m_lifeStealChance = 0.0f;
	this->m_poisonChance = 0.0f;
	this->m_deadlyStrikeChance = 0.0f;
	this->m_poisonCounter = 0;
}

UnitEntity::~UnitEntity()
{

}

void UnitEntity::update(float dt)
{

}

void UnitEntity::increaseStrength(int _strength)
{
	this->m_strength = this->m_strength + _strength;

	if(this->m_strength > UnitEntity::MAX_STRENGTH)
	{
		_strength = UnitEntity::MAX_STRENGTH - this->m_strength;
		this->m_strength = UnitEntity::MAX_STRENGTH;
	}

	this->m_physicalDamage = this->m_physicalDamage + _strength * 5;
	this->m_physicalResistance = this->m_physicalResistance + _strength * 0.02f;
}

void UnitEntity::increaseAgility(int _agility)
{
	this->m_agility = this->m_agility + _agility;

	if(this->m_agility > UnitEntity::MAX_AGILITY)
	{
		_agility = UnitEntity::MAX_AGILITY - this->m_agility;
		this->m_agility = UnitEntity::MAX_AGILITY;
	}

	this->m_movementSpeed = this->m_movementSpeed + _agility * 0.1f;
	this->m_attackSpeed = this->m_attackSpeed + _agility * 0.05f;
}

void UnitEntity::increaseWits(int _wits)
{
	this->m_wits = _wits;

	if(this->m_wits > UnitEntity::MAX_WITS)
	{
		_wits = UnitEntity::MAX_WITS - this->m_wits;
		this->m_wits = UnitEntity::MAX_WITS;
	}

	this->m_mentalDamage = this->m_mentalDamage + _wits * 5;
	this->m_turretlife = this->m_turretlife + _wits * 0.5f;
}

void UnitEntity::increaseFortitude(int _fortitude)
{
	this->m_fortitude = _fortitude;

	if(this->m_fortitude + _fortitude > UnitEntity::MAX_FORTITUDE)
	{
		_fortitude = UnitEntity::MAX_FORTITUDE - this->m_fortitude;
		this->m_fortitude = UnitEntity::MAX_FORTITUDE;
	}
}

void UnitEntity::setMaxHealth(int _maxHealth)
{
	this->m_maxHealth = _maxHealth;
}

void UnitEntity::setMovementSpeed(float _movementSpeed)
{
	this->m_movementSpeed = _movementSpeed;
}

void UnitEntity::setAttackSpeed(float _attackSpeed)
{
	this->m_attackSpeed = _attackSpeed;
}

void UnitEntity::setPhysicalDamage(float _physicalDamage)
{
	this->m_physicalDamage = _physicalDamage;
}

void UnitEntity::setMentalDamage(float _mentalDamage)
{
	this->m_mentalDamage = _mentalDamage;
}

void UnitEntity::setPhysicalResistance(float _physicalResistance)
{
	this->m_physicalResistance = _physicalResistance;
}

void UnitEntity::setMentalResistance(float _mentalResistance)
{
	this->m_mentalResistance = _mentalResistance;
}
void UnitEntity::setLifeStealChance(float _lifeStealChance)
{
	this->m_lifeStealChance = _lifeStealChance;
}

void UnitEntity::setPoisonChance(float _poisonChance)
{
	this->m_poisonChance = _poisonChance;
}

void UnitEntity::setDeadlyStrikeChance(float _deadlyStrikeChance)
{
	this->m_deadlyStrikeChance = _deadlyStrikeChance;
}

int UnitEntity::getStrength()
{
	return this->m_strength;
}

int UnitEntity::getAgility()
{
	return this->m_agility;
}

int UnitEntity::getWits()
{
	return this->m_wits;
}

int UnitEntity::getFortitude()
{
	return this->m_fortitude;
}

int UnitEntity::getHealth()
{
	return this->m_health;
}

int UnitEntity::getMaxHealth()
{
	return this->m_maxHealth;
}

float UnitEntity::getMovementSpeed()
{
	return this->m_movementSpeed;
}

float UnitEntity::getAttackSpeed()
{
	return this->m_attackSpeed;
}

float UnitEntity::getPhysicalDamage()
{
	return this->m_physicalDamage;
}

float UnitEntity::getMentalDamage()
{
	return this->m_mentalDamage;
}

float UnitEntity::getPhysicalResistance()
{
	return this->m_physicalResistance;
}

float UnitEntity::getMentalResistance()
{
	return this->m_mentalResistance;
}

float UnitEntity::getLifeStealChance()
{
	return this->m_lifeStealChance;
}

float UnitEntity::getPoisonChance()
{
	return this->m_poisonChance;
}

float UnitEntity::getDeadlyStrikeChance()
{
	return this->m_deadlyStrikeChance;
}

void UnitEntity::takeDamage(int physicalDamage, int mentalDamage)
{
	this->m_health = this->m_health - physicalDamage * (1 - this->m_physicalResistance);
	this->m_health = this->m_health - mentalDamage * (1 - this->m_mentalResistance);
}

void UnitEntity::dealDamage(ServerEntity* target, int physicalDamage, int mentalDamage)
{
	int lifesteal = rand() % 100 + 1;
	int poison = rand() % 100 + 1;

	if(lifesteal > this->m_lifeStealChance)
	{
		this->heal(physicalDamage * 0.5f);
	}

	if(poison > this->m_poisonChance)
	{
		if(this->m_poisonCounter < 4)
		{
			this->m_poisonCounter++;
			target->takeDamage(100 + this->m_poisonCounter * 5, false);
		}
	}

	target->takeDamage(physicalDamage, mentalDamage);
}

void UnitEntity::heal(int health)
{
	if(this->m_health + health > this->m_maxHealth)
	{
		this->m_health = this->m_maxHealth;
	}
	else
	{
		this->m_maxHealth = this->m_maxHealth + health;
	}
}

void UnitEntity::stun(float _time)
{
	m_stunTimer = max(m_stunTimer, _time);
}

void UnitEntity::update(float dt)
{
	if(m_stunTimer <= 0.0f)
	{
		this->updateSpecificUnitEntity(dt);
	}
	else
	{
		this->m_stunTimer -= dt;
	}
}