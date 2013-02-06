#include "CloudOfDarknessClientSkillEffect.h"
#include "SoundWrapper.h"
#include "CloudOfDarknessEffect.h"
#include "Graphics.h"

CloudOfDarknessClientSkillEffect::CloudOfDarknessClientSkillEffect(FLOAT3 _position)
{
	m_position = _position;
	m_graphicalEffects[0] = g_graphicsEngine->createModel("Char1_5", _position);
	m_graphicalEffects[0] = g_graphicsEngine->createModel("Char1_5", _position);
	m_graphicalEffects[0] = g_graphicsEngine->createModel("Char1_5", _position);
	m_lifetime = 0.0f;
	m_sound = createSoundHandle("rain.wav", false);
	playSound(m_sound);
}

CloudOfDarknessClientSkillEffect::~CloudOfDarknessClientSkillEffect()
{
	g_graphicsEngine->removeModel(m_graphicalEffects[0]);
	g_graphicsEngine->removeModel(m_graphicalEffects[1]);
	g_graphicsEngine->removeModel(m_graphicalEffects[2]);
	stopSound(m_sound);
	deactivateSound(m_sound);
}

void CloudOfDarknessClientSkillEffect::update(float _dt)
{
	m_lifetime += _dt;
}

bool CloudOfDarknessClientSkillEffect::getActive()
{
	if(m_lifetime >= CloudOfDarknessEffect::LIFETIME)
		return false;
	else
		return true;
}