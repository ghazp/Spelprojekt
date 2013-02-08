#pragma once

#include "ServerEntity.h"

class SimonsEvilEffect : public ServerEntity
{
private:
	float m_timer;
	int m_ticks;
	unsigned int m_caster;
	int m_heal;

	void tick();
public:
	static const int LIFETIME = 3;
	static const int AOE = 10;
	static const int DPS = 50;

	SimonsEvilEffect(unsigned int _caster);
	~SimonsEvilEffect();

	void update(float _dt);
};