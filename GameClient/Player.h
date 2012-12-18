#ifndef PLAYER_H
#define PLAYER_H

#include "DataStructures.h"
#include "EntityMessage.h"
#include "MessageQueue.h"
#include "EntityHandler.h"
#include "Hero.h"

class Player
{
private:
	unsigned int m_id;

	MessageQueue *m_messageQueue;
	Hero *m_hero;
public:
	Player(unsigned int id);
	~Player();

	void handleEntityMessage(EntityMessage e);
	void update();
	MessageQueue *getMessageQueue();
};

#endif