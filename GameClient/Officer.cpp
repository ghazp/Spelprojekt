#include "Officer.h"

Officer::Officer(int _playerId) : Hero(Hero::OFFICER, _playerId)
{
	m_modelId = 95;
	this->increaseStrength(3);
	this->increaseAgility(5);
	this->increaseWits(1);
	this->increaseFortitude(3);

	this->m_regularAttack = new MeleeAttack();
}

Officer::~Officer()
{

}
