#pragma once

#include "DataStructures.h"
#include <string>

struct Message
{
	enum Type{Start, Ready, Collision, Attack, RemoveEntity, CreateAction, CreateActionPosition, CreateActionTarget};

	Type type;
	int senderId;
	int reciverId;

	Message()
	{

	}

	Message(Type _type, int _senderId, int _reciverId)
	{
		this->type = _type;
		this->senderId = _senderId;
		this->reciverId = _reciverId;
	}
};

struct ReadyMessage : Message
{
	bool ready;
};

struct StartMessage : Message
{

};

struct CollisionMessage : Message
{
	int affectedDudeId;
};

struct DamageMessage : Message
{
	int damage;
};

struct RemoveServerEntityMessage : Message
{
	int removedId;

	RemoveServerEntityMessage(int _senderId, int _reciverId, int _removedId)
	{
		this->type = Type::RemoveEntity;
		this->senderId = _senderId;
		this->reciverId = _reciverId;
		this->removedId = _removedId;
	}
};

struct CreateActionMessage : Message
{
	unsigned int actionId;
	unsigned int senderId;

	CreateActionMessage(unsigned int _actionId, unsigned int _senderId)
	{
		this->type = Type::CreateAction;
		this->reciverId = 1;
		this->actionId = _actionId;
		this->senderId = _senderId;
	}
};

struct CreateActionPositionMessage : Message
{
	unsigned int actionId;
	unsigned int senderId;
	FLOAT3 position;

	CreateActionPositionMessage(unsigned int _actionId, unsigned int _senderId, FLOAT3 _position)
	{
		this->type = Type::CreateActionPosition;
		this->reciverId = 1;
		this->actionId = _actionId;
		this->senderId = _senderId;
		this->position = _position;
	}
};

struct CreateActionTargetMessage : Message
{
	unsigned int actionId;
	unsigned int senderId;
	unsigned int targetId;

	CreateActionTargetMessage(unsigned int _actionId, unsigned int _senderId, unsigned int _targetId)
	{
		this->type = Type::CreateActionTarget;
		this->reciverId = 1;
		this->actionId = _actionId;
		this->senderId = _senderId;
		this->targetId = _targetId;
	}
};