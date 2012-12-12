#include "EntityMessage.h"

EntityMessage::EntityMessage()
{
	this->pos.x=1.0f;
	this->pos.y=2.0f;
	this->pos.z=3.0f;

	this->rot.x=5.3;
	this->rot.y=7.8;
	this->rot.z=9.23;
}

EntityMessage::~EntityMessage()
{
}

void EntityMessage::setPosition(FLOAT3 pos)
{
	this->pos=pos;
}

void EntityMessage::setRotation(FLOAT3 rot)
{
	this->rot=rot;
}

sf::Packet& operator<<(sf::Packet& packet,const EntityMessage& e)
{
	return packet<<"ENT"<<e.pos.x<<e.pos.y<<e.pos.z<<e.rot.x<<e.rot.y<<e.rot.z;
}
sf::Packet& operator>>(sf::Packet& packet, EntityMessage& e)
{
	return packet >> e.pos.x>>e.pos.y>>e.pos.z>>e.rot.x>>e.rot.y>>e.rot.z;
}

FLOAT3 EntityMessage::getPos()
{
	return this->pos;
}