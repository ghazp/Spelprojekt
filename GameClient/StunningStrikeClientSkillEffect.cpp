#include "StunningStrikeClientSkillEffect.h"
#include "SoundWrapper.h"
#include "StunningStrikeEffect.h"

StunningStrikeClientSkillEffect::StunningStrikeClientSkillEffect(FLOAT3 _position)
{
	m_position = _position;
	m_lifetime = 0.0f;
	m_sound = createSoundHandle("orb.wav", false);
	playSound(m_sound);
}

StunningStrikeClientSkillEffect::~StunningStrikeClientSkillEffect()
{
	stopSound(m_sound);
	deactivateSound(m_sound);
}

void StunningStrikeClientSkillEffect::update(float _dt)
{
	m_lifetime += _dt;
}

bool StunningStrikeClientSkillEffect::getActive()
{
	if(m_lifetime >= StunningStrikeEffect::LIFETIME)
		return false;
	else
		return true;
}