#pragma once
#include "menu.h"
#include "TextLabel.h"
#include "TextInput.h"
#include "Input.h"
#include "client.h"
#include "Skill.h"
#include <sstream>
#include "Entity.h"
#include "SkillIdHolder.h"
#include "Sprite.h"

class HudMenu :
	public Menu
{
public:
	HudMenu(Client *_network, Hero::HERO_TYPE _heroType);
	~HudMenu(void);

	void Update(float _dt, const vector<Entity*>& _entities);

	void addSkill(unsigned int _skillId);
	void setResources(unsigned int resources);
	void skillUsed(unsigned int index, unsigned int actionId, float cooldown);
	void setHealth(float health);
private:
	SkillIdHolder m_skillHolder;
	Client *m_network;
	int	m_NumberOfSkills;
	int m_Resources;

	float	m_SkillHud;

	bool	m_DontChange,
			m_Buy,
			m_Menu,
			m_Locked,
			m_Chat;

	TextInput* m_LabelInput;
	vector<TextLabel*> m_Chattext;	
	TextLabel* m_ResourceLabel;	

	SpriteSheet *m_healthBar;
	FLOAT2 m_fullHealthPos;

	bool m_canAfford[20];
	bool m_shopVisible;
	vector<Button*> m_shopButtons;
	vector<Button*> m_disabledShopButtons;
	vector<Button*> m_resourceImages;
	vector<Sprite*> m_shopBackground;

	int m_skillWaitingForTarget;
	int m_buttonIndex;

	//vector<Button*> m_towerButtons;
	//Button m_towerShopButton;

	bool LockIsDown();
	bool MenuIsDown();

	bool BuyAllSkillIsDown();

	void BuyHud();
	void UpdateShop();
	void UnInit(int _Type);

	void displayShop(bool _visible);
};

