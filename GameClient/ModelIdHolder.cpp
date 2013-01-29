#include "ModelIdHolder.h"

ModelIdHolder::ModelIdHolder()
{
	this->m_modelId[0] = "Char1_5";
	this->m_modelId[1] = "Beast1_5";
	this->m_modelId[2] = "Church";
	this->m_modelId[3] = "PoisonTurret";
	this->m_modelId[4] = "LightningTurret";
	this->m_modelId[5] = "DeathTurret";
	this->m_modelId[6] = "FrostTurret";
}

std::string ModelIdHolder::getModel(unsigned int id)
{
	if(id < 100)
	{
		return this->m_modelId[id];
	}
	else
	{
		return "";
	}
}

unsigned int ModelIdHolder::getNrOfIds()
{
	return 100;
}