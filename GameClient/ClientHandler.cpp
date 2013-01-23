#include "ClientHandler.h"
#include "Input.h"
#include "Graphics.h"
#include "SoundWrapper.h"

ClientHandler::ClientHandler(HWND _hWnd)
{
	// Init globals for the people
	g_graphicsEngine = new GraphicsHandler(_hWnd, g_configFile);
	g_mouse = new Mouse(500, 500, _hWnd);
	g_keyboard = new Keyboard();

	g_graphicsEngine->getCamera()->set(FLOAT3(50.0f, 30.0f, 50.0f), FLOAT3(0.0f, -1.0f, 0.0f), FLOAT3(0.0f, 0.0f, 1.0f), FLOAT3(1.0f, 0.0f, 0.0f));
	g_graphicsEngine->getCamera()->rotate(0.0f, 0.4f, 0.0f);

	this->m_serverThread = new ServerThread();
}

ClientHandler::~ClientHandler()
{
	delete this->m_serverThread;
	delete this->m_state;
	delete g_graphicsEngine;
	delete g_mouse;
	delete g_keyboard;
	delete g_configFile;
}

HRESULT ClientHandler::run()
{
	this->m_serverThread->Launch();
	this->m_state = new MainMenuState();

	__int64 cntsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSec);
	float secsPerCnt = 1.0f / (float)cntsPerSec;

	__int64 prevTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&prevTimeStamp);

	MSG msg = {0};
	while(WM_QUIT != msg.message)
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );

			this->m_messages.push_back(msg);
		}
		else
		{
			__int64 currTimeStamp = 0;
			QueryPerformanceCounter((LARGE_INTEGER*)&currTimeStamp);
			float dt = (currTimeStamp - prevTimeStamp) * secsPerCnt;

			this->update(dt);
			g_graphicsEngine->update(dt);
			g_graphicsEngine->render();

			prevTimeStamp = currTimeStamp;
		}
	}

	return msg.wParam;
}

void ClientHandler::update(float _dt)
{
	// Update controls
	for(int i = 0; i < this->m_messages.size(); i++)
	{
		switch(this->m_messages[i].message)
		{
			case WM_KEYDOWN: // Key gets pressed
				g_keyboard->keyDown(this->m_messages[i].wParam);
				break;
			case WM_KEYUP: // Key gets released
				g_keyboard->keyUp(this->m_messages[i].wParam);
				break;
			case WM_LBUTTONDOWN: // Left mouse button down
				g_mouse->lButtonDown();
				break;
			case WM_RBUTTONDOWN: // Right mouse button down
				g_mouse->rButtonDown();
				break;
			case WM_LBUTTONUP: // Left mouse button up
				g_mouse->lButtonUp();
				break;
			case WM_RBUTTONUP: // Right mouse button up
				g_mouse->rButtonUp();
				break;
		}
	}
	this->m_messages.clear();

	this->m_state->update(_dt);

	if(this->m_state->isDone())
	{
		State* tempState = this->m_state;
		
		switch(this->m_state->nextState())
		{
		case State::MAIN_MENU:
			this->m_state = new MainMenuState();
			break;
		case State::CREATE_GAME:
			this->m_state = new CreateGameState();
			break;
		case State::LOBBY:
			this->m_state = new LobbyState();
			break;
		case State::GAME:
			this->m_state = new GameState();
			break;
		case State::EXIT:
			PostQuitMessage(0);
			break;
		}

		delete tempState;
	}

	updateSoundEngine();

	g_mouse->update(); // Must be last!
	g_keyboard->update();
}