#pragma once

#include "ServerEntity.h"

class StunningStrikeEffect : public ServerEntity
{
private:
	float m_timer;
	
	static const int AOE = 10;
public:
	static const int LIFETIME = 3;

	StunningStrikeEffect(FLOAT3 _position);
	~StunningStrikeEffect();

	void update(float _dt);
};