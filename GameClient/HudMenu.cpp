#include "HudMenu.h"


HudMenu::HudMenu(Client *_network, Hero::HERO_TYPE _heroType)
{
	this->m_network = _network;
	m_Chat = false;
	m_SkillHud = -1.0f;
	m_NumberOfSkills = 0;
	int TmpPos = m_NumberOfSkills * 98;
	m_DontChange = false;
	m_Buy = false;
	m_Menu= false;
	m_Locked = true;
	m_DontChange = false;
	m_Resources = 200000;
	m_Chat = false;
	this->m_skillWaitingForTarget = -1;
	this->m_nrOfAttributesBought = 0;
	
	switch(_heroType)
	{
	case Hero::OFFICER:
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-1.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f),6));
		break;
	case Hero::DOCTOR:
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-4.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f),6));
		break;
	case Hero::ENGINEER:
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-3.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f),6));
		break;
	case Hero::THE_MENTALIST:
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-0.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f),6));
		break;
	case Hero::RED_KNIGHT:
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-2.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f),6));
		break;
	}
	
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Main_Buttons_SkillBar.png", FLOAT2(-1+(0.102083333f*(m_NumberOfSkills-1)),  -0.814814815f),  FLOAT2(1.03125f, 0.344444444f),2));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\GUI-Map.png",FLOAT2(0.79f,  0.6f),FLOAT2(0.421875f, 0.796296296f),5));

	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\LowerHud-Bar.png", FLOAT2(-0.5f,-0.88f),  FLOAT2(1.030208333f,0.272222222f),0));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\GUI-HealtbarHud.png", FLOAT2(-0.876f,-0.3293f),  FLOAT2(0.245833333f,1.344f),5));

	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Tower.png", FLOAT2(-0.56f,1.8f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Strength.png", FLOAT2(-0.28f,1.8f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Agility.png", FLOAT2(-0.0f,1.8f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Wits.png", FLOAT2(0.28f,1.8f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Fortitude.png", FLOAT2(0.56f,1.8f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\GUI-HealtbarHud.png", FLOAT2(-0.876f,-0.3293f),  FLOAT2(0.245833333f,1.344f),5));

	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Chain_Lower.png",FLOAT2(0.0f,  -1.0f),FLOAT2(2.0f, 0.092592593f),6));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Chain_Side.png",FLOAT2(-1.0f,  0.0f),FLOAT2(0.052083333f, 3.555555556f),6));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Resourcehud.png",FLOAT2(0.0f,  -0.85f),FLOAT2(0.260416667f,  0.42962963f),5));	

	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\ChatWindow-Hud.png",FLOAT2(0.5f,  -0.91f),FLOAT2(0.973958333f,  0.32962963f),1));	
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Gear.png",FLOAT2(-0.15f,  -1.0f),FLOAT2(0.375f/3,  0.666666667f/3),1));	
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Gear.png",FLOAT2(-0.43f,  -0.98f),FLOAT2(0.375f/2, 0.666666667f/2),1));	
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Gear.png",FLOAT2(-0.0f,  -0.855f),FLOAT2(0.375f/1.3f,  0.666666667f/1.3f),1));	
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Gear.png",FLOAT2(-0.265f,  -0.90f),FLOAT2(0.375f/2,  0.666666667f/2),1));	
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Gear.png",FLOAT2(-0.85f,  -0.79f),FLOAT2(0.375f/1.2f,  0.666666667f/1.2f),1));	
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Gear.png",FLOAT2(-0.6f,  -0.90f),FLOAT2(0.375f/2,  0.666666667f/2),1));	
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Gear.png",FLOAT2(-0.6f,  -0.90f),FLOAT2(0.375f/1.4f,  0.666666667f/1.4f),1));
	
	m_enemyIcons[Enemy::EnemyType::IMP] = g_graphicsEngine->createSprite("menu_textures/Imp-2.png", FLOAT2(-0.95f,  -0.65f), FLOAT2(0.1f,  0.15625f), 9);
	m_enemyIcons[Enemy::EnemyType::IMP]->setVisible(false);
	m_enemyIcons[Enemy::EnemyType::SHADE] = g_graphicsEngine->createSprite("menu_textures/Imp-3.png", FLOAT2(-0.95f,  -0.65f), FLOAT2(0.1f,  0.15625f), 9);
	m_enemyIcons[Enemy::EnemyType::SHADE]->setVisible(false);
	m_enemyIcons[Enemy::EnemyType::FROST_DEMON] = g_graphicsEngine->createSprite("menu_textures/Imp-0.png", FLOAT2(-0.95f,  -0.65f), FLOAT2(0.1f,  0.15625f), 9);
	m_enemyIcons[Enemy::EnemyType::FROST_DEMON]->setVisible(false);
	m_enemyIcons[Enemy::EnemyType::SPITTING_DEMON] = g_graphicsEngine->createSprite("menu_textures/Imp-1.png", FLOAT2(-0.95f,  -0.65f), FLOAT2(0.1f,  0.15625f), 9);
	m_enemyIcons[Enemy::EnemyType::SPITTING_DEMON]->setVisible(false);
	m_enemyIcons[Enemy::EnemyType::BRUTE_STEED] = g_graphicsEngine->createSprite("menu_textures/Beast-2.png", FLOAT2(-0.95f,  -0.65f), FLOAT2(0.1f,  0.15625f), 9);
	m_enemyIcons[Enemy::EnemyType::BRUTE_STEED]->setVisible(false);
	m_enemyIcons[Enemy::EnemyType::HELLFIRE_STEED] = g_graphicsEngine->createSprite("menu_textures/Beast-3.png", FLOAT2(-0.95f,  -0.65f), FLOAT2(0.1f,  0.15625f), 9);
	m_enemyIcons[Enemy::EnemyType::HELLFIRE_STEED]->setVisible(false);
	m_enemyIcons[Enemy::EnemyType::SOUL_EATER_STEED] = g_graphicsEngine->createSprite("menu_textures/Beast-0.png", FLOAT2(-0.95f,  -0.65f), FLOAT2(0.1f,  0.15625f), 9);
	m_enemyIcons[Enemy::EnemyType::SOUL_EATER_STEED]->setVisible(false);
	m_enemyIcons[Enemy::EnemyType::THUNDERSTEED] = g_graphicsEngine->createSprite("menu_textures/Beast-1.png", FLOAT2(-0.95f,  -0.65f), FLOAT2(0.1f,  0.15625f), 9);
	m_enemyIcons[Enemy::EnemyType::THUNDERSTEED]->setVisible(false);
	m_currentTargetEnemy = Enemy::NONE;
	
	this->m_Buttons.resize(2);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(-0.95f,-0.50f),FLOAT2(0.033333333f,0.059259259f),"menu_textures\\Button-Unlock.png","",0,0,1,11,300);
	
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(-0.94f,0.94f),FLOAT2(0.061458333f,0.111111111f),"menu_textures\\Upgradebar_Buy_All.png","",0,0,1,11,100);

	this->m_SkillButtons.resize(6);
	this->m_SkillButtons[0] = new Skill_Buttons();
	this->m_SkillButtons[0]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*1)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE,0,0,1,4,100,false);
	this->m_SkillButtons[0]->ChangAbleBind(false);
	this->m_SkillButtons[1] = new Skill_Buttons();
	this->m_SkillButtons[1]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*2)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE,0,0,1,4,100,false);
	this->m_SkillButtons[2] = new Skill_Buttons();
	this->m_SkillButtons[2]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*3)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE,0,0,1,4,100,false);
	this->m_SkillButtons[3] = new Skill_Buttons();
	this->m_SkillButtons[3]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*4)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE, 0,0,1,4,100,false);
	this->m_SkillButtons[4] = new Skill_Buttons();
	this->m_SkillButtons[4]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*5)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE,0,0,1,4,100,false);
	this->m_SkillButtons[5] = new Skill_Buttons();
	this->m_SkillButtons[5]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*6)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE,0,0,1,4,100,false);
	this->m_SkillButtons[0]->ChangAbleBind(false);
	this->m_SkillButtons[1]->ChangAbleBind(false);
	m_DontChange = false;

	this->m_LabelInput = new TextInput("text4.png",INT2(1100,1150),55);
	this->m_ResourceLabel = new TextLabel("","text3.png",INT2(925,1100),100);
	string m_TempString = this->m_ResourceLabel->IntToString(m_Resources);
	this->m_ResourceLabel->setText(m_TempString);
	this->m_Chattext.resize(4);
	this->m_Chattext[0] = new TextLabel("","text2.png",INT2(1100,1120),55);
	this->m_Chattext[1] = new TextLabel("","text2.png",INT2(1100,1090),55);
	this->m_Chattext[2] = new TextLabel("","text2.png",INT2(1100,1060),55);
	this->m_Chattext[3] = new TextLabel("","text2.png",INT2(1100,1030),55);

	//Shop buttons
	for(int i = 0; i < 20; i++)
	{
		this->m_shopButtons.push_back(new Button());
	}

	this->m_shopButtons[0]->Init(FLOAT2(-0.62f, 0.8f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::TURRET_CONSTRUCTION),"100",0,0,1,12,100,0,INT2(422,80), false, Skill::TURRET_CONSTRUCTION,"menu_textures\\Skill_0.png");
	this->m_shopButtons[1]->Init(FLOAT2(-0.62f, 0.6f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::TURRET_LIFE),"3500",0,0,1,12,100,3500,INT2(422,200), false, Skill::TURRET_LIFE,"menu_textures\\Skill_1.png");
	this->m_shopButtons[2]->Init(FLOAT2(-0.34f, 0.8f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::STRENGTH),"100",0,0,1,12,100,0,INT2(692,80), false, Skill::STRENGTH, "menu_textures\\Skill_2.png");
	this->m_shopButtons[3]->Init(FLOAT2(-0.34f, 0.6f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::PHYSICAL_RESISTANCE),"900",0,0,1,12,100,900,INT2(692,200), false, Skill::PHYSICAL_RESISTANCE,"menu_textures\\Skill_3.png");
	this->m_shopButtons[4]->Init(FLOAT2(-0.34f, 0.4f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::LIFESTEALING_STRIKE),"2200",0,0,1,12,100,2200,INT2(692,324), false, Skill::LIFESTEALING_STRIKE,"menu_textures\\Skill_4.png");
	this->m_shopButtons[5]->Init(FLOAT2(-0.34f, 0.2f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::STUNNING_STRIKE),"2400",0,0,1,12,100,2400,INT2(692,440), false, Skill::STUNNING_STRIKE,"menu_textures\\Skill_5.png");
	this->m_shopButtons[6]->Init(FLOAT2(-0.34f, 0.0f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::DEMONIC_PRESENCE),"4000",0,0,1,12,100,4000, INT2(692,560), false, Skill::DEMONIC_PRESENCE,"menu_textures\\Skill_6.png");
	this->m_shopButtons[7]->Init(FLOAT2(-0.06f, 0.8f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::AGILITY),"100",0,0,1,12,100,0,INT2(1920/2,80), false, Skill::AGILITY,"menu_textures\\Skill_7.png");
	this->m_shopButtons[8]->Init(FLOAT2(-0.06f, 0.6f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::TELEPORT),"500",0,0,1,12,100,500,INT2(1920/2,200), false, Skill::TELEPORT,"menu_textures\\Skill_8.png");
	this->m_shopButtons[9]->Init(FLOAT2(-0.06f, 0.4f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::AIM),"1100",0,0,1,12,100,1100,INT2(1920/2,324), false, Skill::AIM,"menu_textures\\Skill_9.png");
	this->m_shopButtons[10]->Init(FLOAT2(-0.06f, 0.2f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::DEADLY_STRIKE),"2000",0,0,1,12,100,2000,INT2(1920/2,440), false, Skill::DEADLY_STRIKE,"menu_textures\\Skill_10.png");
	this->m_shopButtons[11]->Init(FLOAT2(0.22f, 0.8f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::WITS),"100",0,0,1,12,100,0,INT2(1228,80), false, Skill::WITS,"menu_textures\\Skill_11.png");
	this->m_shopButtons[12]->Init(FLOAT2(0.22f, 0.6f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::POISON_STRIKE),"1700",0,0,1,12,100,1700,INT2(1228,200), false, Skill::POISON_STRIKE,"menu_textures\\Skill_12.png");
	this->m_shopButtons[15]->Init(FLOAT2(0.22f, 0.4f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::HEALING_TOUCH),"1700",0,0,1,12,100,1700,INT2(1228,324), false, Skill::HEALING_TOUCH,"menu_textures\\Skill_15.png");
	this->m_shopButtons[13]->Init(FLOAT2(0.22f, 0.2f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::CHAIN_STRIKE),"2500",0,0,1,12,100,2500,INT2(1228,440), false, Skill::CHAIN_STRIKE,"menu_textures\\Skill_13.png");
	this->m_shopButtons[14]->Init(FLOAT2(0.22f, 0.0f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::CLOUD_OF_DARKNESS),"3500",0,0,1,12,100,3500,INT2(1228,560), false, Skill::CLOUD_OF_DARKNESS,"menu_textures\\Skill_14.png");
	this->m_shopButtons[16]->Init(FLOAT2(0.49f, 0.8f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::FORTITUDE),"100",0,0,1,12,100,0,INT2(1498,80), false, Skill::FORTITUDE,"menu_textures\\Skill_16.png");
	this->m_shopButtons[17]->Init(FLOAT2(0.49f, 0.6f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::GREED),"700",0,0,1,12,100,700,INT2(1498,200), false, Skill::GREED,"menu_textures\\Skill_17.png");
	this->m_shopButtons[18]->Init(FLOAT2(0.49f, 0.4f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::MENTAL_RESISTANCE),"900",0,0,1,12,100,900,INT2(1498,324), false, Skill::MENTAL_RESISTANCE,"menu_textures\\Skill_18.png");
	this->m_shopButtons[19]->Init(FLOAT2(0.49f, 0.2f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::WALL),"3000",0,0,1,12,100,3000,INT2(1498,440), false, Skill::WALL,"menu_textures\\Skill_19.png");

	for(int i = 0; i < this->m_shopButtons.size(); i++)
	{
		this->m_disabledShopButtons.push_back(new Button());
		this->m_disabledShopButtons[i]->Init(this->m_shopButtons[i]->getPos(),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png",this->m_shopButtons[i]->getText(),0,0,1,12,100, 0, this->m_shopButtons[i]->getTextPos());
		this->m_disabledShopButtons[i]->setVisible(false);

		this->m_resourceImages.push_back(new Button());
		this->m_resourceImages[i]->Init(FLOAT2(this->m_shopButtons[i]->getPos().x + 0.12f, this->m_shopButtons[i]->getPos().y) ,FLOAT2(0.079166667f,0.140740741f), "menu_textures\\Button-Skill-Resource.png", "", 0,0,1,12,100,0,INT2(422,200));
		this->m_canAfford[i] = true;
	}

	this->m_shopBackground.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Tower.png", FLOAT2(-0.56f,0.3f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_shopBackground.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Strength.png", FLOAT2(-0.28f,0.3f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_shopBackground.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Agility.png", FLOAT2(-0.0f,0.3f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_shopBackground.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Wits.png", FLOAT2(0.28f,0.3f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_shopBackground.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Fortitude.png", FLOAT2(0.56f,0.3f),  FLOAT2(0.260416667f,1.451851852f),10));

	this->m_shopVisible = false;
	this->displayShop(false);

	//Healthbar
	this->m_fullHealthPos = FLOAT2(-0.9375f, -0.240740741f);
	this->m_healthBar = g_graphicsEngine->createSpriteSheet("menu_textures\\HealthBar.dds", this->m_fullHealthPos, FLOAT2(0.079166667f, 0.755555556f), INT2(10,1),2);
	this->m_healthBar->playAnimation(INT2(0,0),INT2(9,0),true,10);

	//Towers
	int nrOfTowers = 4;

	for(int i = 0; i < nrOfTowers; i++)
	{
		this->m_towerButtons.push_back(new Button());
	}

	this->m_towerButtons[0]->Init(FLOAT2(-0.12f, -0.85f-0.004f), FLOAT2(0.079166667f/1.5f,0.140740741f/1.5f), this->m_skillHolder.getSkill(Skill::TESLA_CHAIN_TURRET), "", 0.0f, 0.0f, 1.0f, 7, 100, 0, INT2(0,0), false, Skill::TESLA_CHAIN_TURRET,"menu_textures\\Turret_Text_Tesla.png");
	this->m_towerButtons[1]->Init(FLOAT2(-0.06f, -0.67f-0.004f), FLOAT2(0.079166667f/1.5f,0.140740741f/1.5f), this->m_skillHolder.getSkill(Skill::FROST_TURRET), "", 0.0f, 0.0f, 1.0f, 7, 100, 0, INT2(0,0), false, Skill::FROST_TURRET,"menu_textures\\Turret_Text_Frost.png");
	this->m_towerButtons[2]->Init(FLOAT2(0.06f, -0.67f-0.004f), FLOAT2(0.079166667f/1.5f,0.140740741f/1.5f), this->m_skillHolder.getSkill(Skill::POISON_TURRET), "", 0.0f, 0.0f, 1.0f, 7, 100, 0, INT2(0,0), false, Skill::POISON_TURRET,"menu_textures\\Turret_Text_Poison.png");
	this->m_towerButtons[3]->Init(FLOAT2(0.12f, -0.85f-0.004f), FLOAT2(0.079166667f/1.5f,0.140740741f/1.5f), this->m_skillHolder.getSkill(Skill::DEATH_PULSE_TURRET), "", 0.0f, 0.0f, 1.0f, 7, 100, 0, INT2(0,0), false, Skill::DEATH_PULSE_TURRET,"menu_textures\\Turret_Text_Death.png");
}
void HudMenu::Update(float _dt, const vector<Entity*>& _entities, unsigned int _heroId)
{
	if(this->m_placingTower == true)
	{
		D3DXVECTOR3 pickDir;
		D3DXVECTOR3 pickOrig;
		g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());

		float k = (-pickOrig.y)/pickDir.y;
		D3DXVECTOR3 terrainPos = pickOrig + pickDir*k;

		this->m_towerModel->setPosition(FLOAT3(terrainPos.x, terrainPos.y, terrainPos.z));

		if(g_mouse->isLButtonPressed() == true)
		{
			g_graphicsEngine->removeModel(this->m_towerModel);

			this->m_network->sendMessage(NetworkUseActionPositionMessage(this->m_towerId, FLOAT3(terrainPos.x, terrainPos.y, terrainPos.z), 0));	
			this->m_placingTower = false;
		}
		else if(g_mouse->isRButtonPressed() == true)
		{
			g_graphicsEngine->removeModel(this->m_towerModel);
			this->m_placingTower = false;
		}
	}
	else if(m_Chat == false)
	{
		// YOU MUST ADD ALL WAITING FOR TARGET SKILLS HERE TO NOT EQUAL IF YOU DONT WANT MULTIPLE ACTIONS TO HAPPEN AT THE SAME TIME.
		if(m_skillWaitingForTarget != Skill::HEALING_TOUCH && g_mouse->isLButtonPressed() && m_Images[0]->intersects(FLOAT2(
			g_mouse->getPos().x/float(g_graphicsEngine->getRealScreenSize().x)*2.0f-1.0f, g_mouse->getPos().y/float(g_graphicsEngine->getRealScreenSize().y)*2.0f-1.0f)))
		{
			// Find yourself in the entity vector
			for(int entityIndex = 0; entityIndex < _entities.size(); entityIndex++)
			{
				if(_entities[entityIndex]->m_id == _heroId)
				{
					g_graphicsEngine->getCamera()->set(_entities[entityIndex]->m_model->getPosition2DAsFloat2() - FLOAT2(0.0f, g_graphicsEngine->getCamera()->getZOffset()));

					entityIndex = _entities.size();
				}
			}
		}

		float max = -0.897916667f+0.001041667f+(0.102083333f*6)+0.025f;

		//Move the skill buttons
		if(m_DontChange == false)
		{
			if (m_SkillHud <= m_NumberOfSkills-1)
			{
				m_SkillHud += _dt*2;
			}

			this->m_Images[1]->setPosition(FLOAT2(-1.0f +((0.102083333f*(float)m_SkillHud)), -0.814814815f));
			for(int i=0 ; i < m_SkillButtons.size(); i++)
			{
				this->m_SkillButtons[i]->setPosition(FLOAT2(-1.1782f +(0.102083333f*(((m_SkillHud+((m_NumberOfSkills-1)-i-(m_NumberOfSkills-5)))))),  -0.883333333f-0.004f));
			}

			if (m_SkillHud >= m_NumberOfSkills-1)
			{
				m_SkillHud = m_NumberOfSkills-1;

				//Set all skill buttons to the correct position in the end
				this->m_Images[1]->setPosition(FLOAT2(-1.0f +((0.102083333f*(float)m_SkillHud)), -0.814814815f));
				for(int i=0 ; i < m_SkillButtons.size(); i++)
				{
					this->m_SkillButtons[i]->setPosition(FLOAT2(-1.1782f +(0.102083333f*(((m_SkillHud+((m_NumberOfSkills-1)-i-(m_NumberOfSkills-5)))))),  -0.883333333f-0.004f));
				}

				m_DontChange = true;
			}
		}

		if(g_mouse->isLButtonPressed() == true && this->m_skillWaitingForTarget > -1)
		{
			if(this->m_skillWaitingForTarget == Skill::CLOUD_OF_DARKNESS || this->m_skillWaitingForTarget == Skill::TELEPORT || this->m_skillWaitingForTarget == Skill::WALL || this->m_skillWaitingForTarget == Skill::TARGET_ACQUIRED_PERMISSION_TO_FIRE)
			{
				D3DXVECTOR3 pickDir;
				D3DXVECTOR3 pickOrig;
				g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());

				float k = (-pickOrig.y)/pickDir.y;
				D3DXVECTOR3 terrainPos = pickOrig + pickDir*k;
				this->m_network->sendMessage(NetworkUseActionPositionMessage(this->m_skillWaitingForTarget, FLOAT3(terrainPos.x, terrainPos.y, terrainPos.z), this->m_buttonIndex));		
			}
			else if(m_skillWaitingForTarget == Skill::HYPNOTIC_STARE || m_skillWaitingForTarget == Skill::CHAIN_STRIKE)
			{
				D3DXVECTOR3 pickDir;
				D3DXVECTOR3 pickOrig;
				g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());
						
				float dist;
				for(int entityIndex = 0; entityIndex < _entities.size(); entityIndex++)
				{
					if(_entities[entityIndex]->m_type == ServerEntity::EnemyType && _entities[entityIndex]->m_model->intersects(dist, pickOrig, pickDir))
					{
						this->m_network->sendMessage(NetworkUseActionTargetMessage(m_skillWaitingForTarget, _entities[entityIndex]->m_id, this->m_buttonIndex));
						entityIndex = _entities.size();
					}
				}
			}
			else if(m_skillWaitingForTarget == Skill::HEALING_TOUCH)
			{
				// Check if the target is the pic of yourself down in the corner
				if(m_Images[0]->intersects(FLOAT2(
					g_mouse->getPos().x/float(g_graphicsEngine->getRealScreenSize().x)*2.0f-1.0f, g_mouse->getPos().y/float(g_graphicsEngine->getRealScreenSize().y)*2.0f-1.0f)))
				{
					// Find yourself in the entity vector
					for(int entityIndex = 0; entityIndex < _entities.size(); entityIndex++)
					{
						if(_entities[entityIndex]->m_id == _heroId)
						{
							this->m_network->sendMessage(NetworkUseActionTargetMessage(m_skillWaitingForTarget, _entities[entityIndex]->m_id, this->m_buttonIndex));
							entityIndex = _entities.size();
						}
					}
				}
				// Else the pick ray is out on the battlefield
				else
				{
					D3DXVECTOR3 pickDir;
					D3DXVECTOR3 pickOrig;
					g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());
						
					float dist;
					for(int entityIndex = 0; entityIndex < _entities.size(); entityIndex++)
					{
						if(_entities[entityIndex]->m_type == ServerEntity::HeroType && _entities[entityIndex]->m_model->intersects(dist, pickOrig, pickDir))
						{
							this->m_network->sendMessage(NetworkUseActionTargetMessage(m_skillWaitingForTarget, _entities[entityIndex]->m_id, this->m_buttonIndex));
							entityIndex = _entities.size();
						}
					}
				}
			}
			this->m_skillWaitingForTarget = -1;
			g_mouse->getCursor()->setPriority(1);
		}

		for(int i = 1; i < m_NumberOfSkills; i++)
		{
			this->m_SkillButtons[i]->Update(_dt);
			
			if(g_keyboard->getKeyState('0' + i) == Keyboard::KEY_PRESSED || this->m_SkillButtons[i]->Clicked() > 0)
			{
				if(m_SkillButtons[i]->getSkillId() == Skill::CLOUD_OF_DARKNESS || m_SkillButtons[i]->getSkillId() == Skill::HEALING_TOUCH || m_SkillButtons[i]->getSkillId() == Skill::TELEPORT || m_SkillButtons[i]->getSkillId() == Skill::HYPNOTIC_STARE
						|| m_SkillButtons[i]->getSkillId() == Skill::CHAIN_STRIKE || m_SkillButtons[i]->getSkillId() == Skill::WALL || m_SkillButtons[i]->getSkillId() == Skill::TARGET_ACQUIRED_PERMISSION_TO_FIRE)
				{
					this->m_skillWaitingForTarget = this->m_SkillButtons[i]->getSkillId();
					this->m_buttonIndex = i;

					switch(this->m_skillWaitingForTarget)
					{
					case Skill::CLOUD_OF_DARKNESS:
						g_mouse->getCursor()->setFrame(Cursor::CLOUD_OF_DARKNESS, 3);
						break;
					case Skill::HEALING_TOUCH:
						g_mouse->getCursor()->setFrame(Cursor::HEALING_TOUCH, 3);
						break;
					case Skill::TELEPORT:
						g_mouse->getCursor()->setFrame(Cursor::TELEPORT, 3);
						break;
					case Skill::CHAIN_STRIKE:
						g_mouse->getCursor()->setFrame(Cursor::CHAIN_STRIKE, 3);
						break;
					case Skill::HYPNOTIC_STARE:
						g_mouse->getCursor()->setFrame(Cursor::HYPNOTIC_STARE, 3);
						break;
					case Skill::WALL:
						g_mouse->getCursor()->setFrame(Cursor::WALL, 3);
						break;
					case Skill::TARGET_ACQUIRED_PERMISSION_TO_FIRE:
						g_mouse->getCursor()->setFrame(Cursor::TARGET_ACQUIRED, 3);
						break;
					}
				}
				else if(m_SkillButtons[i]->getSkillId() == Skill::STUNNING_STRIKE || m_SkillButtons[i]->getSkillId() == Skill::DEMONIC_PRESENCE || m_SkillButtons[i]->getSkillId() == Skill::SIMONS_EVIL ||
						m_SkillButtons[i]->getSkillId() == Skill::SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR || m_SkillButtons[i]->getSkillId() == Skill::TIME_IS_MONEY)
				{
					this->m_network->sendMessage(NetworkUseActionMessage(m_SkillButtons[i]->getSkillId(), i));
				}
			}
		}

		// Do the E skill
		this->m_SkillButtons[0]->Update(_dt);

		if(this->m_SkillButtons.size() > 0 && (g_keyboard->getKeyState('E') == Keyboard::KEY_PRESSED || this->m_SkillButtons[0]->Clicked() > 0))
		{
			if(m_SkillButtons[0]->getSkillId() == Skill::CLOUD_OF_DARKNESS || m_SkillButtons[0]->getSkillId() == Skill::HEALING_TOUCH || m_SkillButtons[0]->getSkillId() == Skill::TELEPORT || m_SkillButtons[0]->getSkillId() == Skill::HYPNOTIC_STARE
					|| m_SkillButtons[0]->getSkillId() == Skill::CHAIN_STRIKE || m_SkillButtons[0]->getSkillId() == Skill::WALL || m_SkillButtons[0]->getSkillId() == Skill::TARGET_ACQUIRED_PERMISSION_TO_FIRE)
			{
				this->m_skillWaitingForTarget = this->m_SkillButtons[0]->getSkillId();
				this->m_buttonIndex = 0;

				switch(this->m_skillWaitingForTarget)
				{
				case Skill::CLOUD_OF_DARKNESS:
					g_mouse->getCursor()->setFrame(Cursor::CLOUD_OF_DARKNESS, 3);
					break;
				case Skill::HEALING_TOUCH:
					g_mouse->getCursor()->setFrame(Cursor::HEALING_TOUCH, 3);
					break;
				case Skill::TELEPORT:
					g_mouse->getCursor()->setFrame(Cursor::TELEPORT, 3);
					break;
				case Skill::CHAIN_STRIKE:
					g_mouse->getCursor()->setFrame(Cursor::CHAIN_STRIKE, 3);
					break;
				case Skill::HYPNOTIC_STARE:
					g_mouse->getCursor()->setFrame(Cursor::HYPNOTIC_STARE, 3);
					break;
				case Skill::WALL:
					g_mouse->getCursor()->setFrame(Cursor::WALL, 3);
					break;
				case Skill::TARGET_ACQUIRED_PERMISSION_TO_FIRE:
					g_mouse->getCursor()->setFrame(Cursor::TARGET_ACQUIRED, 3);
					break;
				}
			}
			else if(m_SkillButtons[0]->getSkillId() == Skill::STUNNING_STRIKE || m_SkillButtons[0]->getSkillId() == Skill::DEMONIC_PRESENCE || m_SkillButtons[0]->getSkillId() == Skill::SIMONS_EVIL ||
					m_SkillButtons[0]->getSkillId() == Skill::SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR || m_SkillButtons[0]->getSkillId() == Skill::TIME_IS_MONEY)
			{
				this->m_network->sendMessage(NetworkUseActionMessage(m_SkillButtons[0]->getSkillId(), 0));
			}
		}

		for(int i = 0; i < this->m_towerButtons.size(); i++)
		{
			this->m_towerButtons[i]->Update();

			if(this->m_towerButtons[i]->Clicked() == 1)
			{
				//Go into tower placing mode
				this->m_placingTower = true;
				this->m_towerId = this->m_towerButtons[i]->GetID();

				ModelIdHolder m;

				switch(this->m_towerId)
				{
				case Skill::DEATH_PULSE_TURRET:
					this->m_towerModel = g_graphicsEngine->createModel(m.getModel(4), FLOAT3(0.0f, 0.0f, 0.0f));
					break;
				case Skill::TESLA_CHAIN_TURRET:
					this->m_towerModel = g_graphicsEngine->createModel(m.getModel(3), FLOAT3(0.0f, 0.0f, 0.0f));
					break;
				case Skill::FROST_TURRET:
					this->m_towerModel = g_graphicsEngine->createModel(m.getModel(5), FLOAT3(0.0f, 0.0f, 0.0f));
					break;
				case Skill::POISON_TURRET:
					this->m_towerModel = g_graphicsEngine->createModel(m.getModel(2), FLOAT3(0.0f, 0.0f, 0.0f));
					break;
				}

				this->m_towerModel->setAlpha(0.5f);
			}
		}

		for(int i = 0; i < m_Buttons.size(); i++)


		{
			this->m_Buttons[i]->Update();
		}
		if (m_Buy == true)
		{
			UpdateShop();

			if (BuyAllSkillIsDown())
			{
				this->displayShop(false);
				m_Buy = false;
			}
		}
		else if(m_Buy == false)
		{				
			if (BuyAllSkillIsDown())
			{
				this->displayShop(true);
				m_Buy = true;
			}
		}

		if (g_keyboard->getKeyState(VK_RETURN) == Keyboard::KEY_PRESSED && m_Chat == false)
		{
			m_Chat = true;
		}
	}
	else
	{
		this->m_LabelInput->update(_dt);

		if(g_keyboard->getKeyState(VK_RETURN) == Keyboard::KEY_PRESSED)
		{
			string m_String = "";
			m_String.erase(m_String.begin());
			for(int i = m_Chattext.size()-1; i > 0;i--)
			{
				m_Chattext[i]->setText(m_Chattext[i-1]->getText());
			}
			m_String = this->m_LabelInput->getText();
			m_String.erase(m_String.end());
			this->m_Chattext[0]->setText(m_String);
			this->m_LabelInput->setText(""); 
			this->m_Chattext[3]->setText("");
			m_Chat = false;
		}
	}

	LockIsDown();
}
void HudMenu::UnInit(int _Type)
{

}
bool HudMenu::LockIsDown()
{
	if(this->m_Buttons[0]->Clicked() == 1)
	{
		m_NumberOfSkills = 2;
		m_SkillHud = 0;
		this->m_SkillButtons[5]->ChangeButton("30", false, 0);
		this->m_SkillButtons[4]->ChangeButton("30", false, 0);
		this->m_SkillButtons[3]->ChangeButton("30", false, 0);
		this->m_SkillButtons[2]->ChangeButton("30", false, 0);
		m_DontChange = false;
		return true;
	}
	else
	{
		return false;
	}
}

bool HudMenu::BuyAllSkillIsDown()
{
	if(this->m_Buttons[1]->Clicked() == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool HudMenu::MenuIsDown()
{
	if(this->m_Buttons[1]->Clicked() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

HudMenu::~HudMenu(void)
{
	for(int i = 0; i < this->m_shopButtons.size(); i++)
	{
		delete this->m_shopButtons[i];
		delete this->m_resourceImages[i];
		delete this->m_disabledShopButtons[i];
	}

	for(map<Enemy::EnemyType, Sprite*>::iterator iter = m_enemyIcons.begin(); iter != m_enemyIcons.end(); iter++)
		g_graphicsEngine->removeSprite(iter->second);

	for(int i = 0; i < this->m_shopBackground.size(); i++)
	{
		g_graphicsEngine->removeSprite(this->m_shopBackground[i]);
	}

	delete this->m_LabelInput;
	for(int i=0 ; i < this->m_Chattext.size();i++)
	{
		delete this->m_Chattext[i];
		this->m_Chattext[i] = NULL;
	}

	for(int i = 0; i < this->m_towerButtons.size(); i++)
	{
		delete this->m_towerButtons[i];
	}

	delete this->m_ResourceLabel;
	this->m_ResourceLabel = NULL;

	g_graphicsEngine->removeSpriteSheet(this->m_healthBar);
}

void  HudMenu::UpdateShop()
{
	for(int i = 0; i < this->m_shopButtons.size(); i++)
	{
		this->m_shopButtons[i]->Update();
		this->m_resourceImages[i]->Update();

		if(this->m_shopButtons[i]->Clicked() == 1)
		{
			this->m_network->sendMessage(NetworkBuySkillMessage(this->m_shopButtons[i]->GetID()));
		}
	}
}

void HudMenu::displayShop(bool _visible)
{
	this->m_shopVisible = _visible;

	for(int i = 0; i < this->m_shopButtons.size(); i++)
	{
		if(this->m_canAfford[i] == true)
		{
			this->m_shopButtons[i]->setVisible(_visible);
		}
		else
		{
			this->m_disabledShopButtons[i]->setVisible(_visible);
		}

		this->m_resourceImages[i]->setVisible(_visible);
	}

	for(int i = 0; i < this->m_shopBackground.size(); i++)
	{
		this->m_shopBackground[i]->setVisible(_visible);
	}
}

void HudMenu::addSkill(unsigned int _skillId)
{
	if(this->m_skillHolder.getSkill(_skillId) != "")
	{
		if(_skillId == Skill::STRENGTH || _skillId == Skill::AGILITY || _skillId == Skill::WITS || _skillId == Skill::FORTITUDE || _skillId == Skill::TURRET_CONSTRUCTION)
		{
			this->m_nrOfAttributesBought++;
			int cost = 100 * (pow(1.5f, this->m_nrOfAttributesBought));

			stringstream ss;
			ss << cost;
			this->m_shopButtons[0]->setText(ss.str());
			this->m_shopButtons[2]->setText(ss.str());
			this->m_shopButtons[7]->setText(ss.str());
			this->m_shopButtons[11]->setText(ss.str());
			this->m_shopButtons[16]->setText(ss.str());

			this->m_disabledShopButtons[0]->setText(ss.str());
			this->m_disabledShopButtons[2]->setText(ss.str());
			this->m_disabledShopButtons[7]->setText(ss.str());
			this->m_disabledShopButtons[11]->setText(ss.str());
			this->m_disabledShopButtons[16]->setText(ss.str());
		}
		else
		{
			this->m_SkillButtons[this->m_NumberOfSkills]->ChangeButton(this->m_skillHolder.getSkill(_skillId), this->m_skillHolder.getActive(_skillId), _skillId);
			this->m_NumberOfSkills++;
			this->m_DontChange = false;
		}
	}
}

void HudMenu::setResources(unsigned int _resources)
{
	stringstream ss;
	ss<<_resources;

	this->m_Resources = _resources;
	this->m_ResourceLabel->setText(ss.str());

	//Update the buttons in the shop
	for(int i = 0; i < this->m_shopButtons.size(); i++)
	{
		if(this->m_shopButtons[i]->getCost() > this->m_Resources)
		{
			this->m_canAfford[i] = false;
			this->m_shopButtons[i]->setVisible(false);
		}
		else
		{
			this->m_canAfford[i] = true;
			this->m_disabledShopButtons[i]->setVisible(false);
		}
	}

	if(this->m_shopVisible == true)
	{
		this->displayShop(true);
	}
}

void HudMenu::skillUsed(unsigned int index, unsigned int actionId, float cooldown)
{
	if(this->m_SkillButtons[index]->getSkillId() == actionId)
	{
		this->m_SkillButtons[index]->setCooldown(cooldown);
	}
}

void HudMenu::setHealth(float health)
{
	this->m_healthBar->setPosition(FLOAT2(this->m_fullHealthPos.x, this->m_fullHealthPos.y - (1000.0f - health) / 1000.0f * 0.565555556f));
}

void HudMenu::setTargetEnemy(Enemy::EnemyType _enemyType)
{
	if(m_currentTargetEnemy != Enemy::NONE)
		m_enemyIcons[m_currentTargetEnemy]->setVisible(false);

	if(_enemyType != Enemy::NONE)
		m_enemyIcons[_enemyType]->setVisible(true);

	m_currentTargetEnemy = _enemyType;
}

void HudMenu::setLivesLeft(int livesLeft)
{
	//Update some text
}