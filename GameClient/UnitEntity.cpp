#include "UnitEntity.h"
#include "MyAlgorithms.h"

UnitEntity::UnitEntity() : ServerEntity()
{
	this->m_health = 100;
	this->m_maxHealth = 100;

	this->m_strength = 1;
	this->m_agility = 1;
	this->m_wits = 1;
	this->m_fortitude = 1;
	
	this->m_movementSpeedChange = 0.0f;
	this->m_movementSpeed = 2.0f;
	this->m_attackSpeedChange = 0.0f;
	this->m_attackSpeed = 1.0f;
	this->m_physicalDamage = 1.0f;
	this->m_mentalDamage = 1.0f;
	this->m_physicalResistance = 1.0f;
	this->m_mentalResistance = 1.0f;
	this->m_lifeStealChance = 0.0f;
	this->m_poisonChance = 0.0f;
	this->m_deadlyStrikeChance = 0.0f;
	this->m_poisonCounter = 0;
	this->m_stunTimer = 0.0f;
	this->m_greed = 1.0f;
	this->m_turretDuration = 10.0f;
	this->m_attackCooldown = 0.0f;
	this->m_attackRange = 5.0f;
	m_swiftAsACatPowerfulAsABear = false;
}

UnitEntity::UnitEntity(FLOAT3 pos) : ServerEntity(pos)
{
	this->m_health = 100;
	this->m_maxHealth = 100;

	this->m_strength = 1;
	this->m_agility = 1;
	this->m_wits = 1;
	this->m_fortitude = 1;
	
	this->m_baseAttackSpeed = 2.0f;
	this->m_baseMovementSpeed = 2.0f;
	this->m_movementSpeedChange = 0.0f;
	this->m_movementSpeed = 2.0f;
	this->m_attackSpeedChange = 0.0f;
	this->m_attackSpeed = 2.0f;
	this->m_physicalDamage = 1.0f;
	this->m_mentalDamage = 1.0f;
	this->m_physicalResistance = 1.0f;
	this->m_mentalResistance = 1.0f;
	this->m_lifeStealChance = 0;
	this->m_poisonChance = 0;
	this->m_deadlyStrikeChance = 0;
	this->m_poisonCounter = 0;
	this->m_greed = 1.0f;
	this->m_turretDuration = 10.0f;
	this->m_attackCooldown = 0.0f;
	this->m_attackRange = 5.0f;
	m_swiftAsACatPowerfulAsABear = false;
}

UnitEntity::~UnitEntity()
{
	for(int i = 0; i < this->m_skills.size(); i++)
	{
		delete this->m_skills[i];
	}
}

void UnitEntity::addSkill(Skill *_skill)
{
	this->m_skills.push_back(_skill);
}

vector<Skill*> UnitEntity::getSkills()
{
	return this->m_skills;
}

Skill *UnitEntity::getSkill(unsigned int _id)
{
	Skill *result = NULL;

	for(int i = 0; i < this->m_skills.size(); i++)
	{
		if(this->m_skills[i]->getId() == _id && this->m_skills[i]->getCurrentCooldown() == 0.0f)
		{
			result = this->m_skills[i];
			i = this->m_skills.size();		
		}
	}

	return result;
}

int UnitEntity::getNrOfSkills()
{
	return this->m_skills.size();
}

int UnitEntity::getSkillIndex(Skill* _skill)
{
	int index = -1;
	
	for(int i = 0; i < this->m_skills.size(); i++)
	{
		if(this->m_skills[i] == _skill)
		{
			index = i;
			i = this->m_skills.size();		
		}
	}

	return index;
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
	this->m_turretDuration = this->m_turretDuration + _wits * 0.5f;
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

void UnitEntity::alterAttackSpeed(float _value)
{
	m_attackSpeedChange += _value;
	m_attackSpeed = m_baseAttackSpeed + m_attackSpeedChange;

	if(this->m_attackCooldown > this->m_attackSpeed)
	{
		this->m_attackCooldown = this->m_attackSpeed;
	}
}

void UnitEntity::alterMovementSpeed(float _value)
{
	m_movementSpeedChange += _value;
	m_movementSpeed = m_baseMovementSpeed + m_movementSpeedChange;
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
void UnitEntity::setLifeStealChance(unsigned int _lifeStealChance)
{
	this->m_lifeStealChance = _lifeStealChance;
}

void UnitEntity::setPoisonChance(unsigned int _poisonChance)
{
	this->m_poisonChance = _poisonChance;
}

void UnitEntity::setDeadlyStrikeChance(unsigned int _deadlyStrikeChance)
{
	this->m_deadlyStrikeChance = _deadlyStrikeChance;
}

void UnitEntity::setGreed(float _greed)
{
	this->m_greed = _greed;
}

void UnitEntity::setTurretDuration(float _turretDuration)
{
	this->m_turretDuration = _turretDuration;
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

unsigned int UnitEntity::getLifeStealChance()
{
	return this->m_lifeStealChance;
}

unsigned int UnitEntity::getPoisonChance()
{
	return this->m_poisonChance;
}

unsigned int UnitEntity::getDeadlyStrikeChance()
{
	return this->m_deadlyStrikeChance;
}

float UnitEntity::getGreed()
{
	return this->m_greed;
}

float UnitEntity::getTurretDuration()
{
	return this->m_turretDuration;
}

unsigned int UnitEntity::getLastDamageDealer()
{
	return this->m_lastDamageDealer;
}

void UnitEntity::takeDamage(unsigned int damageDealerId, int physicalDamage, int mentalDamage)
{
	this->m_health = this->m_health - physicalDamage * this->m_physicalResistance;
	this->m_health = this->m_health - mentalDamage * this->m_mentalResistance;
	this->m_lastDamageDealer = damageDealerId;
}

void UnitEntity::dealDamage(ServerEntity* target, int physicalDamage, int mentalDamage)
{
	int lifesteal = rand() % 100 + 1;
	int poison = rand() % 100 + 1;
	int deadlyStrike = rand() % 100 + 1;

	if(lifesteal < this->m_lifeStealChance)
	{
		this->heal(physicalDamage * 0.5f);
	}

	if(poison < this->m_poisonChance)
	{
		if(this->m_poisonCounter < 4)
		{
			this->m_poisonCounter++;
		}
		
		target->takeDamage(this->m_id, 100 + this->m_poisonCounter * 5, false);
	}

	if(deadlyStrike < this->m_deadlyStrikeChance && target->getType() == Type::EnemyType)
	{
		target->takeDamage(this->m_id, INT_MAX, INT_MAX);
	}

	if(m_swiftAsACatPowerfulAsABear)
	{
		//G�r saacpaab saker
		if(random(1, 10) == 1)
			target->takeDamage(this->m_id, INT_MAX, INT_MAX);
		else
			physicalDamage*=3;

		m_swiftAsACatPowerfulAsABear = false;
	}

	target->takeDamage(this->m_id, physicalDamage, mentalDamage);
}

void UnitEntity::heal(int health)
{
	this->m_health = min(m_health+health, m_maxHealth);
}

void UnitEntity::stun(float _time)
{
	m_stunTimer = max(m_stunTimer, _time);
}

void UnitEntity::update(float dt)
{
	for(int i = 0; i < this->m_skills.size(); i++)
	{
		this->m_skills[i]->update(dt);
	}

	if(this->m_attackCooldown > 0.0f)
	{
		this->m_attackCooldown = this->m_attackCooldown - dt;
	}

	if(m_stunTimer <= 0.0f)
	{
		this->updateSpecificUnitEntity(dt);
	}
	else
	{
		this->m_stunTimer -= dt;
	}
}

NetworkEntityMessage UnitEntity::getUpdate()
{
	float xdir=this->getDirection().x*this->getMovementSpeed();
	float zdir=this->getDirection().z*this->getMovementSpeed();
	/*
	if(this->getPosition().x==this->getDirection().x&&this->getPosition().z==this->getDirection().z)
	{
		xdir=0;
		zdir=0;
	}*/

	
	NetworkEntityMessage e = NetworkEntityMessage(this->m_id, this->m_position.x, this->m_position.z,this->m_rotation.x,this->m_position.x,this->m_position.z,this->getEndPos().x,this->getEndPos().z,this->getMovementSpeed());


	return e;
}