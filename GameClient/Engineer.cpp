#include "Engineer.h"

Engineer::Engineer(int _playerId) : Hero(Hero::ENGINEER, _playerId)
{
	m_modelId = 97;
	this->increaseStrength(3);
	this->increaseAgility(3);
	this->increaseWits(5);
	this->increaseFortitude(1);

	this->m_regularAttack = new RangedAttack();
}

Engineer::~Engineer()
{

}
