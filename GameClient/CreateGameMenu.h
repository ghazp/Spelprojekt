#pragma once
#include "menu.h"
class CreateGameMenu :
	public Menu
{
public:
	CreateGameMenu(void);
	~CreateGameMenu(void);

	void Update();
	bool StartGameIsDown();
	bool MainMenuGameIsDone();
};

