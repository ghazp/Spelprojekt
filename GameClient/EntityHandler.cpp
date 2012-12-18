#include "EntityHandler.h"

vector<ServerEntity*> EntityHandler::m_entities;	

EntityHandler::EntityHandler()
{
	//this->m_messageQueue = new MessageQueue();
}

//EntityHandler::EntityHandler(/*MessageHandler* _messageHandler*/)
//{
//	//this->m_messageQueue = new MessageQueue();
//	//this->m_messageHandler = _messageHandler;
//}

EntityHandler::~EntityHandler()
{
	for(int i = 0; i < this->m_entities.size(); i++)
	{
		delete this->m_entities[i];
	}

	//delete this->m_messageQueue;
}

void EntityHandler::update()
{
	for(int i = 0; i < EntityHandler::m_entities.size(); i++)
	{
		EntityHandler::m_entities[i]->update();
	}
}

void EntityHandler::addEntity(ServerEntity *_entity)
{
	EntityHandler::m_entities.push_back(_entity);
	//this->m_messageHandler->addQueue(_entity->getMessageQueue());
}

bool EntityHandler::removeEntity(ServerEntity *_entity)
{
	bool found = false;

	for(int i = 0; i < EntityHandler::m_entities.size(); i++)
	{
		if(EntityHandler::m_entities[i] == _entity)
		{
			delete this->m_entities[i];
			EntityHandler::m_entities.erase(EntityHandler::m_entities.begin() + i);
			found = true;
			i = EntityHandler::m_entities.size();
		}
	}

	return found;
}

vector<ServerEntity*> EntityHandler::getEntities()
{
	return EntityHandler::m_entities;
}