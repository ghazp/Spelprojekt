#include "MeleeAOEClientSkillEffect.h"
#include "SoundWrapper.h"
#include "MyAlgorithms.h"
#include "SpeechManager.h"

float MeleeAOEClientSkillEffect::timeToNextDamageSound = 0.0f;

MeleeAOEClientSkillEffect::MeleeAOEClientSkillEffect(unsigned int _masterId, unsigned int _targetId, PLAYER_INFO _playerInfo)
{
	this->m_lifetime = 1.0f;
	Entity* master = ClientEntityHandler::getEntity(_masterId);
	
	if(master != NULL)
	{
		master->m_model->getAnimation()->PlayLoop("2Hattack");
	}

	Entity* target = ClientEntityHandler::getEntity(_targetId);

	if(target)
	{
		if(target->m_type == UnitEntity::EnemyType)
		{
			int sound;

			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("enemy/Monster_Imp_Damage_0.wav", false, false);
				break;
			case 1:
				sound = createSoundHandle("enemy/Monster_Imp_Damage_1.wav", false, false);
				break;
			case 2:
				sound = createSoundHandle("enemy/Monster_Imp_Damage_2.wav", false, false);
				break;
			}
					
			SpeechManager::speak(_targetId, sound); // The unit must be killed on the client before on the server for this sound solution to actually work.
			deactivateSound(sound);
		}
		else if(target->m_type == UnitEntity::HeroType)
		{
			if(_targetId == _playerInfo.id)
			{
				int sound;

				switch(_playerInfo.heroType)
				{
				case Hero::RED_KNIGHT:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("red_knight/RedKnight_Damage_0.wav", false, false);
						break;
					case 1:
						sound = createSoundHandle("red_knight/RedKnight_Damage_1.wav", false, false);
						break;
					case 2:
						sound = createSoundHandle("red_knight/RedKnight_Damage_2.wav", false, false);
						break;
					}
					break;
				case Hero::ENGINEER:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("engineer/Engineer_Damage_0.wav", false, false);
						break;
					case 1:
						sound = createSoundHandle("engineer/Engineer_Damage_1.wav", false, false);
						break;
					case 2:
						sound = createSoundHandle("engineer/Engineer_Damage_2.wav", false, false);
						break;
					}
					break;
				case Hero::THE_MENTALIST:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("mentalist/Mentalist_Damage_0.wav", false, false);
						break;
					case 1:
						sound = createSoundHandle("mentalist/Mentalist_Damage_1.wav", false, false);
						break;
					case 2:
						sound = createSoundHandle("mentalist/Mentalist_Damage_2.wav", false, false);
						break;
					}
					break;
				case Hero::OFFICER:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("officer/Officer_Damage_0.wav", false, false);
						break;
					case 1:
						sound = createSoundHandle("officer/Officer_Damage_1.wav", false, false);
						break;
					case 2:
						sound = createSoundHandle("officer/Officer_Damage_2.wav", false, false);
						break;
					}
					break;
				case Hero::DOCTOR:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("doctor/Doctor_Damage_0.wav", false, false);
						break;
					case 1:
						sound = createSoundHandle("doctor/Doctor_Damage_1.wav", false, false);
						break;
					case 2:
						sound = createSoundHandle("doctor/Doctor_Damage_2.wav", false, false);
						break;
					}
					break;
				}
				
				SpeechManager::speak(_targetId, sound);
				deactivateSound(sound);
			}
		}
	}
}

MeleeAOEClientSkillEffect::~MeleeAOEClientSkillEffect()
{

}

void MeleeAOEClientSkillEffect::decreaseTimeBetweenDamageSounds(float _dt)
{
	MeleeAOEClientSkillEffect::timeToNextDamageSound = max(MeleeAOEClientSkillEffect::timeToNextDamageSound-_dt, 0.0f);
}

void MeleeAOEClientSkillEffect::update(float dt)
{
	this->m_lifetime -= dt;
}

bool MeleeAOEClientSkillEffect::getActive()
{
	if(this->m_lifetime <= 0.0f)
	{
		return false;
	}
	else
	{
		return true;
	}
}