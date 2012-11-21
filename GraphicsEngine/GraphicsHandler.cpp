#include "GraphicsHandler.h"

GraphicsHandler::GraphicsHandler()
{

}

GraphicsHandler::GraphicsHandler(HWND _hWnd)
{
	this->m_deviceHandler = new DeviceHandler(_hWnd);
	this->m_world = new World(this->m_deviceHandler);
	this->m_resourceHolder = new ResourceHolder(this->m_deviceHandler->getDevice());
	this->m_configFile = ConfigFile();
}

GraphicsHandler::~GraphicsHandler()
{
	delete this->m_world;
	delete this->m_resourceHolder;
	delete this->m_deviceHandler;
}

Model* GraphicsHandler::createModel(string _filename)
{
	Model* model = NULL;
	Mesh* mesh = this->m_resourceHolder->getMesh(_filename);

	if(mesh != NULL)
	{
		model = new Model(mesh);
		this->m_world->addModel(model);
	}
	int asdfasd;
	return model;
}

bool GraphicsHandler::removeModel(Model* _model)
{
	return this->m_world->removeModel(_model);
}

void GraphicsHandler::render()
{
	this->m_world->render();
}

void update(float dt)
{
	//Uppdatera animationer?
}