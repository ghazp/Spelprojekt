#ifndef SERVER_H
#define SERVER_H

#include "Msg.h"
#include "EntityMessage.h"
#include "AttackMessage.h"
#include "RemoveEntityMessage.h"
#include "AttackEntityMessage.h"
#include "UseSkillMessage.h"

#include "NetworkMessage.h"
#include "NetworkEntityMessage.h"
#include "NetworkDisconnectMessage.h"
#include "NetworkRemoveEntityMessage.h"
#include "NetworkUseActionMessage.h"
#include "NetworkUseActionPositionMessage.h"

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <queue>
#include <vector>
#include "MessageHandler.h"
#include "Player.h"

using namespace std;
class Server : private sf::Thread
{
private:
	MessageHandler *m_messageHandler;
	MessageQueue *m_messageQueue;

	sf::Mutex m_mutex;

	queue<Msg> msgQueue;
	queue<EntityMessage> entityQueue;
	queue<AttackMessage> attackMessageQueue;
	queue<AttackEntityMessage> attackEntityMessageQueue;

	vector<Player*> m_players;

	sf::SelectorTCP selector;
	sf::SocketTCP listener;
	sf::SocketTCP clients[4];
	int clientArrPos;
	virtual void Run();
	void goThroughSelector();
	void handleMessages();
	bool handleClientInData(int socketIndex, sf::Packet packet, NetworkMessage::MESSAGE_TYPE type);
public:
	Server(MessageHandler *_messageHandler);
	~Server();
	bool start(int port);
	void shutDown();
	void broadcast(NetworkEntityMessage networkMessage);
	void broadcast(NetworkRemoveEntityMessage networkMessage);

	bool isRunning();

	Msg msgQueueFront();
	EntityMessage entityQueueFront();
	bool msgQueueEmpty();
	bool entityQueueEmpty();

	vector<Player*> getPlayers();
};

#endif // SERVER_H
