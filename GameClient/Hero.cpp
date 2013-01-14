#include "Hero.h"

Hero::Hero() : ServerEntity()
{
	this->m_type = Type::HeroType;
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_positon.x, this->m_positon.y, this->m_positon.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	this->m_nextPosition = this->m_positon;
	this->m_reachedPosition = true;
	this->m_movementSpeed = 5.0f;
}

Hero::~Hero()
{

}

void Hero::update(float dt)
{
	//Handle incoming messages
	Message *m;

	while(this->m_messageQueue->incomingQueueEmpty() == false)
	{
		m = this->m_messageQueue->pullIncomingMessage();

		if(m->type == Message::Collision)
		{
			//this->m_positon = FLOAT3(0.0f, 0.0f, 0.0f);
		}

		delete m;
	}

	if(this->m_reachedPosition == false)
	{
		FLOAT3 distance = this->m_nextPosition - this->m_positon;
		if(distance.length() > this->m_movementSpeed * dt)
		{
			distance = distance / distance.length();
			this->m_positon = this->m_positon + (distance * this->m_movementSpeed * dt);
		}
		else
		{
			this->m_positon = this->m_nextPosition;
			this->m_reachedPosition = true;
		}

		this->m_obb->Center = XMFLOAT3(this->m_positon.x, this->m_positon.y, this->m_positon.z);
		this->m_rotation.x = atan2(-distance.x, -distance.z);
	}

	if(this->m_health <= 0)
	{
		this->m_positon = FLOAT3(0.0f, 0.0f, 0.0f);
		this->m_health = 100;
	}
}

void Hero::setNextPosition(FLOAT3 _nextPosition)
{
	this->m_nextPosition = _nextPosition;
	this->m_reachedPosition = false;
}

FLOAT3 Hero::getDirection()
{
	if( (m_nextPosition - m_positon).length() > 0)
	{
		return m_nextPosition-m_positon;
		
	}
	else
		return m_positon;
}

void Hero::takeDamage(int damage)
{
	this->m_health = this->m_health - damage;
}

