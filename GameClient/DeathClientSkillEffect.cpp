#include "DeathClientSkillEffect.h"
#include "MyAlgorithms.h"
#include "SpeechManager.h"
#include "SoundWrapper.h"
#include "Hero.h"
#include "Enemy.h"

DeathClientSkillEffect::DeathClientSkillEffect(unsigned int _masterId, FLOAT3 _position)
{
	this->m_masterId = _masterId;
	this->m_lifetime = 5.0f;
	this->m_sink = false;

	Entity *e = ClientEntityHandler::getEntity(this->m_masterId);

	if(e->m_type == ServerEntity::EnemyType)
	{
		this->m_sink = true;
	}

	if(e != NULL)
	{
		this->m_model = g_graphicsEngine->createModel(e->m_model, false);
		this->m_model->setPosition(_position);
		this->m_model->getAnimation()->Play("death", true);
		this->m_model->SetHat(e->m_model->getHat());
		this->m_model->SetLeftHand(e->m_model->getLeftHand());
		this->m_model->SetRightHand(e->m_model->getRightHand());
	}

	// Play death sound.
	int sound;
	switch(e->m_type)
	{
	case ServerEntity::HeroType:
		switch(e->m_subtype)
		{
		case Hero::RED_KNIGHT:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("red_knight/RedKnight_Death_0.wav", false, true, e->m_startPos);
				break;
			case 1:
				sound = createSoundHandle("red_knight/RedKnight_Death_1.wav", false, true, e->m_startPos);
				break;
			case 2:
				sound = createSoundHandle("red_knight/RedKnight_Death_2.wav", false, true, e->m_startPos);
				break;
			}
			break;
		case Hero::ENGINEER:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("engineer/Engineer_Death_0.wav", false, true, e->m_startPos);
				break;
			case 1:
				sound = createSoundHandle("engineer/Engineer_Death_1.wav", false, true, e->m_startPos);
				break;
			case 2:
				sound = createSoundHandle("engineer/Engineer_Death_2.wav", false, true, e->m_startPos);
				break;
			}
			break;
		case Hero::THE_MENTALIST:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("mentalist/Mentalist_Death_0.wav", false, true, e->m_startPos);
				break;
			case 1:
				sound = createSoundHandle("mentalist/Mentalist_Death_1.wav", false, true, e->m_startPos);
				break;
			case 2:
				sound = createSoundHandle("mentalist/Mentalist_Death_2.wav", false, true, e->m_startPos);
				break;
			}
			break;
		case Hero::OFFICER:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("officer/Officer_Death_0.wav", false, true, e->m_startPos);
				break;
			case 1:
				sound = createSoundHandle("officer/Officer_Death_1.wav", false, true, e->m_startPos);
				break;
			case 2:
				sound = createSoundHandle("officer/Officer_Death_2.wav", false, true, e->m_startPos);
				break;
			}
			break;
		case Hero::DOCTOR:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("doctor/Doctor_Death_0.wav", false, true, e->m_startPos);
				break;
			case 1:
				sound = createSoundHandle("doctor/Doctor_Death_1.wav", false, true, e->m_startPos);
				break;
			case 2:
				sound = createSoundHandle("doctor/Doctor_Death_2.wav", false, true, e->m_startPos);
				break;
			}
			break;
		}
		break;

	case ServerEntity::EnemyType:
		switch(e->m_subtype)
		{
		case Enemy::IMP:
			sound = createSoundHandle("enemy/Monster_Imp_Death_0.wav", false, true, e->m_startPos);
			break;
		case Enemy::SHADE:
			sound = createSoundHandle("enemy/Monster_Shade_Death_0.wav", false, true, e->m_startPos);
			break;
		case Enemy::FROST_DEMON:
			sound = createSoundHandle("enemy/Monster_Frost_Death_0.wav", false, true, e->m_startPos);
			break;
		case Enemy::SPITTING_DEMON:
			sound = createSoundHandle("enemy/Monster_Spitting_Death_0.wav", false, true, e->m_startPos);
			break;
		case Enemy::HELLFIRE_STEED:
			sound = createSoundHandle("enemy/Beast_Dying_0.wav", false, true, e->m_startPos);
			break;
		case Enemy::SOUL_EATER_STEED:
			sound = createSoundHandle("enemy/Beast_Dying_0.wav", false, true, e->m_startPos);
			break;
		case Enemy::THUNDERSTEED:
			sound = createSoundHandle("enemy/Beast_Dying_0.wav", false, true, e->m_startPos);
			break;
		case Enemy::BRUTE_STEED:
			sound = createSoundHandle("enemy/Beast_Dying_0.wav", false, true, e->m_startPos);
			break;
		}
		break;
	}

	SpeechManager::speakUltimate(_masterId, sound);
	deactivateSound(sound);
}

DeathClientSkillEffect::~DeathClientSkillEffect()
{

}

void DeathClientSkillEffect::update(float dt)
{
	this->m_lifetime = this->m_lifetime - dt;

	if(this->m_lifetime < 1.5f)
	{
		if(this->m_sink == true)
		{
			FLOAT3 pos = this->m_model->getPosition();
			pos.y = pos.y - dt;
			this->m_model->setPosition(pos);
		}
	}
}

bool DeathClientSkillEffect::getActive()
{
	if(this->m_lifetime <= 0.0f)
	{
		g_graphicsEngine->removeModel(this->m_model);
		return false;
	}
	else
	{
		return true;
	}
}