#include "Doctor.h"

Doctor::Doctor(int _playerId, WEAPON_TYPE _weaponType) : Hero(Hero::DOCTOR, _playerId)
{
	m_modelId = 98;
	this->increaseStrength(1);
	this->increaseAgility(3);
	this->increaseWits(5);
	this->increaseFortitude(3);
	
	this->m_skills.push_back(new SimonsEvil());
	this->m_skills.push_back(new LifeRegen());

	switch(_weaponType)
	{
	case WEAPON_TYPE::MELEE:
		this->m_regularAttack = new MeleeAttack();
		break;

	case WEAPON_TYPE::RANGED:
		this->m_regularAttack = new RangedAttack();
		break;
	}
}

Doctor::~Doctor()
{

}
