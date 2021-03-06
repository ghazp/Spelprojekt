#pragma once
#include "networkmessage.h"
#include "DataStructures.h"

class NetworkCreateActionMessage : public NetworkMessage
{
private:
	unsigned int m_actionId;
	unsigned int m_senderId;
	FLOAT3 m_position;
public:
	NetworkCreateActionMessage();
	NetworkCreateActionMessage(unsigned int _actionId, unsigned int _senderId, FLOAT3 _position);
	~NetworkCreateActionMessage();

	unsigned int getActionId();
	unsigned int getSenderId();
	FLOAT3 getPosition();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkCreateActionMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkCreateActionMessage& e);
};

