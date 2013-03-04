#pragma once

#include "ClientSkillEffect.h"
#include "Model.h"
#include "PointLight.h"
#include "ClientEntityHandler.h"

class ChainStrikeClientSkillEffect : public ClientSkillEffect
{
private:
	Model* m_graphicalEffects[3];
	PointLight* m_light;
	int m_sound;
	FLOAT3 m_position;
	float m_lifetime;
public:
	ChainStrikeClientSkillEffect(unsigned int _masterId, FLOAT3 _position);
	~ChainStrikeClientSkillEffect();

	void update(float _dt);
	bool getActive();
};