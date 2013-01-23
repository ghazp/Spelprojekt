#include "JoinGameMenu.h"


JoinGameMenu::JoinGameMenu(void)
{
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-JoinGameMenu.png", FLOAT2(0,0),  FLOAT2(2,2),0));

	this->m_Buttons.resize(2);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(0.140625f,  -0.933333333f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-CharacterMenu-StartGame.png","",0,0,2);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(-0.140625f,  -0.933333333f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-MainMenu.png","",0,0,2);
}
void JoinGameMenu::Update()
{
	for(int i=0; i < this->m_Buttons.size(); i++)
	{
		this->m_Buttons[i]->Update();
	}
}
bool JoinGameMenu::StartGameIsDown()
{
	if(this->m_Buttons[0]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool JoinGameMenu::MainMenuGameIsDone()
{
	if(this->m_Buttons[1]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
JoinGameMenu::~JoinGameMenu(void)
{
}
