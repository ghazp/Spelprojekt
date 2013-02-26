#pragma once

#include "EntityHandler.h"
#include <SFML\System.hpp>
#include "Server.h"
#include "MessageHandler.h"
#include "Player.h"
#include "Enemy.h"
#include "ServerEntity.h"
#include "MapHandler.h"
#include "CollisionHandler.h"
#include "GraphicsHandler.h"
#include <sstream>

class ServerThread : public sf::Thread
{
private:
	enum State { LOBBY, GAME, VICTORY, DEFEAT, EXIT };

	Server *m_network;
	MessageHandler *m_messageHandler;
	EntityHandler *m_entityHandler;
	MapHandler* m_mapHandler;

	MessageQueue *m_messageQueue;
	State m_state;
	int m_port;

	void Run();
	void update(float dt);
public:
	 ServerThread(int _port);
	 ~ServerThread();
};