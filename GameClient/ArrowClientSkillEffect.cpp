#include "ArrowClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"
#include "Arrow.h"

ArrowClientSkillEffect::ArrowClientSkillEffect(FLOAT3 _position, unsigned int _targetId)
{
	m_active = true;
	m_unitTookDamage = false;
	m_targetId = _targetId;
	m_graphicalEffect = g_graphicsEngine->createModel("Arrow", _position);
	m_graphicalEffect->setAlpha(0.999f);
	m_sound = createSoundHandle("click_button.wav", false, true, _position);
	playSound(m_sound);
}

ArrowClientSkillEffect::~ArrowClientSkillEffect()
{
	g_graphicsEngine->removeModel(m_graphicalEffect);
	deactivateSound(m_sound);
}

unsigned int ArrowClientSkillEffect::getTargetId()const
{
	return m_targetId;
}

bool ArrowClientSkillEffect::unitTookDamage()const
{
	return m_unitTookDamage;
}

void ArrowClientSkillEffect::update(float _dt)
{
	Entity* target = ClientEntityHandler::getEntity(m_targetId);
	if(target)
	{
		FLOAT3 dist = target->m_model->getPosition()-m_graphicalEffect->getPosition();
		FLOAT3 movement = dist/dist.length()*Arrow::VELOCITY*_dt;

		if(dist.length() > movement.length())
		{
			m_graphicalEffect->move(movement);
			m_graphicalEffect->setRotation(FLOAT3(atan2(-movement.x, -movement.z), 0.0f, 0.0f));
		}
		else
		{
			m_active = false;
			m_unitTookDamage = true; // The unit must be killed on the client before on the server for this sound solution to actually work.
		}
	}
	else
	{
		m_active = false;
	}
}

bool ArrowClientSkillEffect::getActive()
{
	return m_active;
}