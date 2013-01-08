#ifndef ENTITY_HANDLER_H
#define ENTITY_HANDLER_H

#include <vector>
#include <SFML\System.hpp>
#include "ServerEntity.h"
#include "MessageHandler.h"

using namespace std;

class EntityHandler
{
private:
	static sf::Mutex m_mutex;
	static vector<ServerEntity*> m_entities;
	static unsigned int m_nextId;

	static MessageQueue *m_messageQueue;
	static MessageHandler *m_messageHandler;
public:
	EntityHandler();
	EntityHandler(MessageHandler* _messageHandler);
	~EntityHandler();

	void update(float dt);
	void removeAllEntities();

	static void addEntity(ServerEntity *_entity);
	static bool removeEntity(ServerEntity *_entity);

	static vector<ServerEntity*> getEntities();

	static ServerEntity* getClosestEntity(ServerEntity *entity);
	static ServerEntity* getServerEntity(unsigned int id);

	static unsigned int getId();
};

#endif